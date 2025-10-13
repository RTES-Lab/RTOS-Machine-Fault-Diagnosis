# main_ST_prun_train_from_scratch.py
import os
import argparse
import numpy as np
import torch

import funs
import funs.model as model

from torch.optim import Adam
from torch.optim.lr_scheduler import MultiStepLR
from torch.nn import CrossEntropyLoss
from torchvision import transforms
from sklearn.model_selection import train_test_split


# ========= 유틸 =========
def ensure_dirs(*dirs):
    for d in dirs:
        os.makedirs(d, exist_ok=True)

def test_loss_to_scalar(test_loss):
    if isinstance(test_loss, (list, tuple)):
        return float(np.mean(test_loss))
    if hasattr(test_loss, "shape"):
        if isinstance(test_loss, torch.Tensor):
            return float(test_loss.detach().mean().item())
        return float(np.mean(test_loss))
    return float(test_loss)

def compute_actual_prune_ratio(model) -> float:
    """프루닝 마스크(Structured) 기준 실제 제거 비율 추정 (요소 기준)."""
    total_elems, kept_elems = 0, 0
    for _, m in model.named_modules():
        mask = getattr(m, "weight_mask", None)
        if mask is not None:
            total_elems += mask.numel()
            kept_elems  += int(mask.sum().item())
    if total_elems == 0:
        return 0.0
    kept_ratio = kept_elems / total_elems
    return 1.0 - kept_ratio

def evaluate_and_plot(df, test_loader, fault_label_list, predicted_label_list,
                      log_root, pic_root, log_file, cm_name):
    funs.log_class_acc(log_root, fault_label_list, predicted_label_list, log_file)
    funs.plot_confusion_matrix(pic_root, fault_label_list, predicted_label_list, cm_name)


# ========= 메인 =========
def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--prune", type=float, default=0.5, help="희망 pruning ratio (예: 0.8)")
    parser.add_argument("--epochs", type=int, default=1000, help="고정 학습 에폭 수")
    # 필요하면 마일스톤을 직접 지정할 수 있게 옵션 추가 (쉼표로 구분)
    parser.add_argument("--milestones", type=str, default="", help="러닝레이트 감소 에폭(쉼표구분). 예: 500,750,900")
    args = parser.parse_args()

    PRUNE_RATIO = float(args.prune)
    assert 0.0 <= PRUNE_RATIO < 1.0, "prune ratio는 [0,1) 범위여야 합니다."
    EPOCHS = int(args.epochs)

    # ---- 공통 설정 ----
    config = funs.load_yaml('./config.yaml')
    funs.set_seed(config.seed)

    device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
    print('device =', device)

    ensure_dirs(config.model_root_st, config.log_root_st, config.pic_root_st)

    # ---- 데이터 준비 ----
    data_root_dirs = os.path.join(config.dataset_root_st)
    print("Making dataframes...")
    df = funs.STmake_dataframe(config, data_root_dirs)

    # ---- Split ----
    train_df, temp_df = train_test_split(
        df, test_size=0.4, stratify=df['label'], random_state=config.seed
    )
    val_df, test_df = train_test_split(
        temp_df, test_size=0.5, stratify=temp_df['label'], random_state=config.seed
    )
    train_df = train_df.reset_index(drop=True)
    val_df   = val_df.reset_index(drop=True)
    test_df  = test_df.reset_index(drop=True)

    # ---- 샘플 빌드 ----
    train_data, train_label = funs.STbuild_from_dataframe(train_df, config.sample_size, config.overlap, False)
    val_data,   val_label   = funs.STbuild_from_dataframe(val_df,   config.sample_size, config.overlap, False)
    test_data,  test_label  = funs.STbuild_from_dataframe(test_df,  config.sample_size, config.overlap, False)

    # ---- Transform/Dataloader ----
    tf_data  = transforms.Compose([funs.processing.NpToTensor(), funs.processing.ToSignal()])
    tf_label = transforms.Compose([funs.processing.NpToTensor()])

    train_dataset = funs.NumpyDataset(train_data, train_label, transform=tf_data, target_transform=tf_label)
    val_dataset   = funs.NumpyDataset(val_data,   val_label,   transform=tf_data, target_transform=tf_label)
    test_dataset  = funs.NumpyDataset(test_data,  test_label,  transform=tf_data, target_transform=tf_label)

    train_loader = funs.get_dataloader(train_dataset, config.batch_size, True)
    val_loader   = funs.get_dataloader(val_dataset,   config.batch_size, False)
    test_loader  = funs.get_dataloader(test_dataset,  config.batch_size, False)

    # ---- 랜덤 초기화 모델 생성 ----
    n_classes = df["label"].max() - df["label"].min() + 1
    net = model.Mynet2(n_classes=n_classes).to(device)

    # ---- (선택) 프루닝 적용 ----
    if PRUNE_RATIO > 0.0:
        print(f'\n====== Structured Pruning: requested ratio={int(PRUNE_RATIO*100)}% ======')
        try:
            funs.apply_structured_pruning(net, prune_ratio=PRUNE_RATIO)
        except TypeError:
            funs.apply_structured_pruning(net, PRUNE_RATIO)

        actual_ratio = compute_actual_prune_ratio(net)
        print(f"[Prune] requested={PRUNE_RATIO:.4f}  | actual≈{actual_ratio:.4f}  (elements-level)")
    else:
        print("[Info] 0% pruning → skip pruning; 랜덤 초기 가중치로 그대로 학습합니다.")
        actual_ratio = 0.0

    # ---- 고정 에폭 학습 + LR 스케줄 (1/10씩 감소) ----
    optimizer = Adam(net.parameters(), lr=float(config.learning_rate))
    loss_fn   = CrossEntropyLoss()
    trainer   = funs.Trainer(net, loss_fn, optimizer, device, train_loader, val_loader)

    # milestones 설정: 명시가 없으면 50%, 75%, 90% 지점에서 /10
    if args.milestones.strip():
        try:
            milestones = [int(x) for x in args.milestones.split(",") if x.strip()]
        except Exception:
            raise ValueError("--milestones 형식이 잘못되었습니다. 예: --milestones 500,750,900")
    else:
        milestones = [EPOCHS // 2, int(EPOCHS * 0.75), int(EPOCHS * 0.9)]
        # 중복/0/초과 방지
        milestones = sorted(set([m for m in milestones if 0 < m < EPOCHS]))

    scheduler = MultiStepLR(optimizer, milestones=milestones, gamma=0.1)

    print("Starting Training with LR decay by x0.1 at milestones:", milestones)
    for ep in range(1, EPOCHS + 1):
        _best, _last = trainer.train(epoch=1)   # 에폭당 1회 호출
        scheduler.step()

        # 초반/마일스톤/주기적 출력
        if ep <= 5 or ep in milestones or (ep % 50 == 0) or ep == EPOCHS:
            cur_lr = optimizer.param_groups[0]["lr"]
            print(f"[LR] epoch {ep:4d}/{EPOCHS} -> lr={cur_lr:.6g}")

    # ---- 저장 ----
    model_tag = f'ST_FRFconv-TDS_structured_{int(PRUNE_RATIO*100)}'
    save_path = os.path.join(config.model_root_st, f'{model_tag}.pt')

    if PRUNE_RATIO > 0.0:
        try:
            funs.remove_pruning_and_save_structured(
                save_dir=config.model_root_st, model=trainer.model, tag=model_tag
            )
        except Exception:
            trainer.save(config.model_root_st, model_tag)
    else:
        trainer.save(config.model_root_st, model_tag)

    # ---- 재로딩 & 테스트 & 로그/CM ----
    try:
        state = torch.load(save_path, weights_only=True)
    except TypeError:
        state = torch.load(save_path)
    trainer.model.load_state_dict(state)

    fault_label_list, test_loss, predicted_label_list = trainer.test(test_loader)
    test_loss_scalar = test_loss_to_scalar(test_loss)

    log_file = f'ST_log_per_acc_structured_{int(PRUNE_RATIO*100)}.txt'
    cm_name  = f'ST_confusion_matrix_structured_{int(PRUNE_RATIO*100)}.png'
    evaluate_and_plot(
        df, test_loader, fault_label_list, predicted_label_list,
        config.log_root_st, config.pic_root_st, log_file, cm_name
    )

    print(f"[Done] requested_prune={PRUNE_RATIO:.4f} | actual≈{actual_ratio:.4f} | "
          f"test_loss={test_loss_scalar:.4f} | saved: {save_path} | CM: {cm_name}")


if __name__ == '__main__':
    main()

"""
# 기본(마일스톤: 500, 750, 900)에서 1000에폭 학습, 프루닝 50%
python main_ST_prun_train_from_scratch.py --prune 0.5 --epochs 1000

# 마일스톤 직접 지정(예: 300, 600, 800에서 각각 /10)
python main_ST_prun_train_from_scratch.py --prune 0.6 --epochs 1000 --milestones 300,600,800

"""