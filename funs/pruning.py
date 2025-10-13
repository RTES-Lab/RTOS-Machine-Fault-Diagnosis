# funs/pruning.py
from __future__ import annotations
import os
from typing import Iterable, Tuple, Optional

import torch
import torch.nn as nn
import torch.nn.utils.prune as prune


def _resolve_model(m: nn.Module) -> nn.Module:
    """DataParallel / DistributedDataParallel 대응."""
    if hasattr(m, "module"):
        return m.module
    return m


def _iter_target_modules(
    model: nn.Module,
    include_types: Tuple[type, ...] = (nn.Conv1d, nn.Linear),
    exclude_last_linear: bool = False,
) -> Iterable[Tuple[str, nn.Module]]:
    """
    모델 내 프루닝 대상 모듈들을 순회.
    - Conv1d: 출력 채널 단위(dim=0) 구조적 프루닝
    - Linear: 출력 뉴런 단위(dim=0) 구조적 프루닝
    """
    named = list(model.named_modules())

    # 마지막 Linear 제외 옵션 처리
    last_linear_name = None
    if exclude_last_linear:
        for name, mod in reversed(named):
            if isinstance(mod, nn.Linear):
                last_linear_name = name
                break

    for name, mod in named:
        if not isinstance(mod, include_types):
            continue
        if exclude_last_linear and name == last_linear_name:
            continue
        yield name, mod


def _apply_ln_structured(module: nn.Module, amount: float, n: int = 2, dim: int = 0):
    """
    torch.nn.utils.prune.ln_structured 래퍼
    - amount: 0~1 비율 또는 정수(제거할 채널 수)
    - n: L_n norm (기본 2)
    - dim: 구조적 프루닝 축 (Conv/Linear의 out-dim=0)
    """
    prune.ln_structured(module, name="weight", amount=amount, n=n, dim=dim)


def apply_structured_pruning(
    model: nn.Module,
    prune_ratio: float,
    *,
    norm_type: str = "ln",
    n: int = 2,
    include: Tuple[type, ...] = (nn.Conv1d, nn.Linear),
    exclude_last_linear: bool = False,
    verbose: bool = True,
) -> nn.Module:
    """
    Conv1d/Linear에 구조적 프루닝을 적용.
    - prune_ratio: 0.2, 0.4, 0.6, 0.8 등 제거 비율
    - norm_type: 'ln' 만 지원(필요 시 확장)
    - n: Ln의 n (기본 2)
    - include: 대상 모듈 타입
    - exclude_last_linear: 마지막 Linear(클래스 분류기) 제외 여부
    반환: 프루닝 마스크가 적용된 model (in-place)
    """
    assert 0.0 < prune_ratio < 1.0 or isinstance(prune_ratio, int), "prune_ratio는 (0,1) 또는 int여야 합니다."
    model = _resolve_model(model)

    for name, mod in _iter_target_modules(model, include, exclude_last_linear):
        if isinstance(mod, nn.Conv1d):
            dim = 0  # out_channels 기준 채널 제거
        elif isinstance(mod, nn.Linear):
            dim = 0  # out_features 기준 뉴런 제거
        else:
            continue

        if norm_type == "ln":
            _apply_ln_structured(mod, amount=prune_ratio, n=n, dim=dim)
        else:
            raise NotImplementedError(f"지원하지 않는 norm_type: {norm_type}")

        if verbose:
            try:
                w = mod.weight
                mask = getattr(mod, "weight_mask")
                kept = int(mask.sum().item())
                total = mask.numel()
                print(f"[prune] {name:<40} kept={kept}/{total}  (~{kept/total:.2%})")
            except Exception:
                print(f"[prune] {name}")

    return model


def remove_pruning_and_save_structured(
    *,
    save_dir: str,
    model: nn.Module,
    tag: str,
    create_dir: bool = True,
    verbose: bool = True,
) -> str:
    """
    모든 모듈의 pruning reparam(=weight_orig, weight_mask)을 제거하여
    실제 weight에 반영한 뒤 state_dict를 저장.
    반환: 저장 경로
    """
    model = _resolve_model(model)

    # 마스크 제거
    for name, mod in model.named_modules():
        if hasattr(mod, "weight_mask"):
            try:
                prune.remove(mod, "weight")
                if verbose:
                    print(f"[prune-remove] {name}")
            except Exception as e:
                if verbose:
                    print(f"[prune-remove][WARN] {name}: {e}")

    # 저장
    if create_dir:
        os.makedirs(save_dir, exist_ok=True)
    path = os.path.join(save_dir, f"{tag}.pt")
    torch.save(model.state_dict(), path)
    if verbose:
        print(f"[save] {path}")
    return path


# ---- (옵션) 진단/통계 유틸 ----
def count_total_parameters(model: nn.Module) -> int:
    return sum(p.numel() for p in model.parameters())


def count_nonzero_parameters(model: nn.Module) -> int:
    nz = 0
    for p in model.parameters():
        nz += int(torch.count_nonzero(p).item())
    return nz


# ---- (옵션) 간단 파인튜너: Trainer가 없을 때 사용하려면 주석 해제 ----
# def fine_tune_structured(
#     model: nn.Module,
#     train_loader,
#     val_loader=None,
#     *,
#     epochs: int = 100,
#     optimizer: Optional[torch.optim.Optimizer] = None,
#     loss_fn: Optional[nn.Module] = None,
#     device: Optional[torch.device] = None,
#     scheduler: Optional[torch.optim.lr_scheduler._LRScheduler] = None,
#     verbose: bool = True,
# ):
#     model.train()
#     for ep in range(1, epochs + 1):
#         total = 0.0
#         for x, y in train_loader:
#             x = x.to(device, non_blocking=True)
#             y = y.to(device, non_blocking=True)
#             optimizer.zero_grad(set_to_none=True)
#             logits = model(x)
#             loss = loss_fn(logits, y.squeeze() if y.ndim > 1 else y)
#             loss.backward()
#             optimizer.step()
#             total += loss.item()
#         if scheduler:
#             scheduler.step()
#         if verbose and ep % max(1, epochs // 10) == 0:
#             print(f"[ft] epoch {ep}/{epochs}  loss={total/len(train_loader):.4f}")
