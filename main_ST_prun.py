import os
import numpy as np
import torch

import funs
import funs.model as model

from copy import deepcopy
from torch.optim import Adam
from torch.nn import CrossEntropyLoss
from torchvision import transforms
from sklearn.model_selection import train_test_split


# ====== 유틸 ======
def train_one(trainer, epochs: int):
    """Trainer.train 반환 형식(best_val, last_val)을 그대로 유지"""
    return trainer.train(epoch=epochs)

def evaluate_and_plot(df, test_loader, fault_label_list, predicted_label_list,
                      log_root, pic_root, log_file, cm_name):
    funs.log_class_acc(log_root, fault_label_list, predicted_label_list, log_file)
    funs.plot_confusion_matrix(pic_root, fault_label_list, predicted_label_list, cm_name)

def _extract_state_dict(loaded_obj):
    """
    로드한 객체가 state_dict 자체인지, 체크포인트(dict)인지 상황별로 안전하게 state_dict 반환
    예상 키들: 'state_dict', 'model_state_dict', 'net', 'model'
    """
    if isinstance(loaded_obj, dict):
        for k in ['state_dict', 'model_state_dict', 'net', 'model']:
            if k in loaded_obj and isinstance(loaded_obj[k], dict):
                return loaded_obj[k]
        # 만약 dict이지만 weight 텐서들로 보이면 그대로 반환
        if all(isinstance(v, torch.Tensor) for v in loaded_obj.values()):
            return loaded_obj
    # 그 외에는 그대로 사용 (일반적으로 state_dict일 가능성)
    return loaded_obj


def main(config, args):
    # ===== 공통 설정 =====
    funs.set_seed(config.seed)
    device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
    print('device =', device)

    # ===== 에폭 고정 =====
    aEp = 1000  # 요청: pruning ratio별 1000 epoch

    # ===== 데이터 준비 =====
    data_root_dirs = os.path.join(config.dataset_root_st)
    print("Making dataframes...")
    df = funs.STmake_dataframe(config, data_root_dirs)

    # Split
    train_df, temp_df = train_test_split(
        df,
        test_size=0.4,
        stratify=df['label'],
        random_state=config.seed
    )
    val_df, test_df = train_test_split(
        temp_df,
        test_size=0.5,
        stratify=temp_df['label'],
        random_state=config.seed
    )
    train_df = train_df.reset_index(drop=True)
    val_df   = val_df.reset_index(drop=True)
    test_df  = test_df.reset_index(drop=True)

    # 샘플 빌드
    train_data, train_label = funs.STbuild_from_dataframe(train_df, config.sample_size, config.overlap, False)
    val_data,   val_label   = funs.STbuild_from_dataframe(val_df,   config.sample_size, config.overlap, False)
    test_data,  test_label  = funs.STbuild_from_dataframe(test_df,  config.sample_size, config.overlap, False)

    # Transform
    tf_data  = transforms.Compose([funs.processing.NpToTensor(), funs.processing.ToSignal()])
    tf_label = transforms.Compose([funs.processing.NpToTensor()])

    # Dataset & Dataloader
    train_dataset = funs.NumpyDataset(train_data, train_label, transform=tf_data, target_transform=tf_label)
    val_dataset   = funs.NumpyDataset(val_data,   val_label,   transform=tf_data, target_transform=tf_label)
    test_dataset  = funs.NumpyDataset(test_data,  test_label,  transform=tf_data, target_transform=tf_label)

    train_loader = funs.get_dataloader(train_dataset, config.batch_size, True)
    val_loader   = funs.get_dataloader(val_dataset,   config.batch_size, False)
    test_loader  = funs.get_dataloader(test_dataset,  config.batch_size, False)

    # ===== 모델 구성 및 외부 체크포인트 로드 =====
    n_classes = df["label"].max() - df["label"].min() + 1
    ckpt_path = "/home/kseorang/Github/RTOS-Machine-Fault-Diagnosis/models_st/ST_FRFconv-TDS_1000.pt"

    print(f"[Info] Loading external baseline checkpoint: {ckpt_path}")
    try:
        # torch 2.0+ 에서 weights_only 인자가 있을 수도 있으므로 안전 분기
        if 'weights_only' in torch.load.__code__.co_varnames:
            loaded_obj = torch.load(ckpt_path, map_location="cpu", weights_only=True)
        else:
            loaded_obj = torch.load(ckpt_path, map_location="cpu")
    except Exception as e:
        raise RuntimeError(f"Failed to load checkpoint from {ckpt_path}: {e}")

    state_dict = _extract_state_dict(loaded_obj)

    # ===== 프루닝 루프 (베이스라인 학습 없음) =====
    prune_ratios = [0.2, 0.4, 0.6, 0.8]
    loss_fn = CrossEntropyLoss()

    for pr in prune_ratios:
        print(f"\n====== Structured Pruning: ratio={int(pr*100)}% ======")

        # 1) 모델 생성 및 외부 가중치 로드
        pruned_model = model.Mynet2(n_classes=n_classes).to(device)
        missing, unexpected = pruned_model.load_state_dict(state_dict, strict=False)
        if missing:
            print(f"[Warn] Missing keys while loading: {missing[:5]}{'...' if len(missing)>5 else ''}")
        if unexpected:
            print(f"[Warn] Unexpected keys while loading: {unexpected[:5]}{'...' if len(unexpected)>5 else ''}")

        # 2) 구조적 프루닝 적용
        try:
            funs.apply_structured_pruning(pruned_model, prune_ratio=pr)
        except TypeError:
            funs.apply_structured_pruning(pruned_model, pr)

        # 3) 프루닝 후 파인튜닝 (1000 epoch)
        optimizer = Adam(pruned_model.parameters(), lr=float(config.learning_rate))
        trainer_ft = funs.Trainer(pruned_model, loss_fn, optimizer, device, train_loader, val_loader)
        _best_ft, _last_ft = train_one(trainer_ft, epochs=aEp)

        # 4) 마스크 제거 및 저장 (함수 유무에 따라 분기)
        model_tag = f"ST_FRFconv-TDS_structured_{int(pr*100)}"
        save_path = os.path.join(config.model_root_st, f"{model_tag}.pt")

        try:
            funs.remove_pruning_and_save_structured(
                save_dir=config.model_root_st,
                model=trainer_ft.model,
                tag=model_tag
            )
            print(f"[Info] Saved (with mask removal) -> {save_path}")
        except Exception:
            trainer_ft.save(config.model_root_st, model_tag)
            print(f"[Info] Saved (raw state_dict) -> {save_path}")

        # 5) 저장본 로드 후 테스트 & CM
        try:
            if 'weights_only' in torch.load.__code__.co_varnames:
                state_after = torch.load(save_path, map_location="cpu", weights_only=True)
            else:
                state_after = torch.load(save_path, map_location="cpu")
        except Exception:
            state_after = torch.load(save_path, map_location="cpu")

        state_after = _extract_state_dict(state_after)
        trainer_ft.model.load_state_dict(state_after, strict=False)

        fault_label_list, test_loss, predicted_label_list = trainer_ft.test(test_loader)

        # test_loss 스칼라화
        if isinstance(test_loss, (list, tuple)):
            test_loss_scalar = float(np.mean(test_loss))
        elif hasattr(test_loss, "shape"):
            try:
                if isinstance(test_loss, torch.Tensor):
                    test_loss_scalar = float(test_loss.detach().mean().item())
                else:
                    test_loss_scalar = float(np.mean(test_loss))
            except Exception:
                test_loss_scalar = float(np.mean(test_loss))
        else:
            test_loss_scalar = float(test_loss)

        # 로그/CM
        log_file = f"ST_log_per_acc_structured_{int(pr*100)}.txt"
        cm_name  = f"ST_confusion_matrix_structured_{int(pr*100)}.png"
        evaluate_and_plot(
            df, test_loader, fault_label_list, predicted_label_list,
            config.log_root_st, config.pic_root_st,
            log_file, cm_name
        )

        print(f"[Done] ratio={int(pr*100)}% | test_loss={test_loss_scalar:.4f} | saved: {save_path} | CM: {cm_name}")


if __name__ == "__main__":
    config = funs.load_yaml("./config.yaml")
    args = funs.parse_arguments()
    main(config, args)
