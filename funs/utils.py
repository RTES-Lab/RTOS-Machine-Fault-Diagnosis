# utils.py

import os
from datetime import datetime
import yaml
from box import Box
import random

import numpy as np
import torch

from sklearn.metrics import confusion_matrix

def load_yaml(config_path: str) -> Box:
    """
    YAML 파일을 load하는 함수

    Parameters
    ----------
    config_path : str
        YAML 파일 경로

    Returns
    -------
    Box 
        Box 개체
    """
    with open(config_path) as f:
        config_yaml = yaml.load(f, Loader=yaml.FullLoader)
        config = Box(config_yaml)

    return config

def set_seed(seed: int):
    """
    랜덤 시드 고정 함수.

    Parameters
    ----------
    seed : int
        고정할 시드 값
    """
    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    if torch.cuda.is_available():
        torch.cuda.manual_seed_all(seed)


def get_bearing_paths(root: str, bearing_type: str, rpm_list: list, sampling_rate: str) -> list:
    """
    주어진 베어링 타입과 rpm 리스트에 따라 데이터셋 경로를 반환하는 함수.

    Parameters
    ----------
    root : str
        데이터셋의 루트 디렉토리 경로
    bearing_type : str
        베어링 종류 (예: CylindricalRoller, DeepGrooveBall, TaperedRoller)
    rpm_list : list
        사용할 회전 속도(rpm) 값들의 리스트 (예: [600, 1200, 1800])

    Returns
    -------
    list
        각 rpm에 해당하는 데이터셋 경로들의 리스트
    """
    base = os.path.join(root, f'BearingType_{bearing_type}', f'SamplingRate_{sampling_rate}') # 16000만 사용
    return [os.path.join(base, f'RotatingSpeed_{rpm}') for rpm in rpm_list]


def log_class_acc(root, fault_label_list, predicted_label_list, log_file):
    os.makedirs(f'{root}/', exist_ok=True)
    cm = confusion_matrix(fault_label_list, predicted_label_list)
    per_class_acc = cm.diagonal() / cm.sum(axis=1)

    # 클래스별 정확도 출력
    print("Class-wise Accuracy:")
    for cls_idx, acc in enumerate(per_class_acc):
        print(f"Class {cls_idx}: {acc:.5f}")

    # 로그 파일 기록
    now = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    with open(f'{root}/{log_file}', "a") as f:
        f.write(f"{now}  ")
        for cls_idx, acc in enumerate(per_class_acc):
            f.write(f"Class {cls_idx}: {acc:.5f}  ")
        f.write("\n")
    print("Class-wise accuracy logged to", log_file)