# databuilder.py

import os
from scipy import io

from typing import Tuple

import numpy as np
import pandas as pd

def make_dataframe(config, data_dirs):

    df = {}
    df["data"] = []
    df["fault_type"] = []
    df["label"] = []
    df["RPM"] = []
    df["bearing_type"] = []
    for dir_path in data_dirs:
        for fname in os.listdir(dir_path):
            filepath = os.path.join(dir_path, fname)

            # 베어링 결함은 사용 X 
            split_str = filepath.split('_')
            if split_str[4] != 'H':
                continue

            data = io.loadmat(filepath)
            body = data['Data']
            body = np.ravel(body, order="F")
            fault_type = split_str[3].split('/')[-1]
            bearing_type = split_str[1].split('/')[0]  

            # Label(기계결함)에 없는 결함은 사용 X
            if fault_type not in config.label:
                continue

            df['data'].append(body)
            df['fault_type'].append(fault_type)
            df['label'].append(config.label[fault_type])
            df['RPM'].append(split_str[-1].split('.')[0])
            df['bearing_type'].append(bearing_type)

    data_frame = pd.DataFrame(df)

    return data_frame

def STmake_dataframe(config, data_dirs):

    df = {}
    df["data"] = []
    df["fault_type"] = []
    df["label"] = []
    df["RPM"] = []
    df["bearing_type"] = []
    for dir_path in os.listdir(data_dirs):
        for fname in os.listdir(os.path.join(data_dirs, dir_path)):
            filepath = os.path.join(data_dirs, dir_path, fname)

            fault_type = filepath.split('/')[-2]
            bearing_type = 'DeepGrooveBall'

            with open(filepath, 'r') as f:
                data = f.readlines()
            body = np.array(data, np.float64)

            df['data'].append(body)
            df['fault_type'].append(fault_type)
            df['label'].append(config.label[fault_type])
            df['RPM'].append(1400)
            df['bearing_type'].append(bearing_type)

    data_frame = pd.DataFrame(df)

    return data_frame


def split_dataframe(
    df: pd.DataFrame, train_ratio: float, val_ratio: float
) -> Tuple[pd.DataFrame, pd.DataFrame, pd.DataFrame]:
    """
    Split data segments of dataframe to the training, validation, and test segments.
    Author: Seongjae Lee
    """
    cum_train_ratio = train_ratio
    cum_val_ratio = cum_train_ratio + val_ratio

    train_df = {"data": [], "label": []}

    val_df = {"data": [], "label": []}

    test_df = {"data": [], "label": []}

    for _, row in df.iterrows():
        segment_length = row.data.size
        train_idx = (int)(segment_length * cum_train_ratio)
        val_idx = (int)(segment_length * cum_val_ratio)
        train_df["data"].append(row.data[:train_idx])
        train_df["label"].append(row.label)

        val_df["data"].append(row.data[train_idx:val_idx])
        val_df["label"].append(row.label)

        test_df["data"].append(row.data[val_idx:])
        test_df["label"].append(row.label)

    train_df = pd.DataFrame(train_df)
    val_df = pd.DataFrame(val_df)
    test_df = pd.DataFrame(test_df)

    return train_df, val_df, test_df

def build_from_dataframe(
    df: pd.DataFrame, sample_length: int, shift: int, one_hot: bool = False
) -> Tuple[np.ndarray, np.ndarray]:
    """
    Generate pairs of np.ndarrays from a dataframe.
    Author: Seongjae Lee
    """
    n_class = df["label"].max() - df["label"].min() + 1
    n_data = df.shape[0]
    data = []
    label = []
    for i in range(n_data):
        d = df.iloc[i]["data"]
        td, tl = sample_data(
            d, sample_length, shift, df.iloc[i]["label"], n_class, one_hot
        )
        data.append(td)
        label.append(tl)

    data_array = np.concatenate(tuple(data), axis=0)
    label_array = np.concatenate(tuple(label), axis=0)

    return data_array, label_array


def sample_data(
    data: np.ndarray,
    sample_length: int,
    shift: int,
    cls_id: int,
    num_class: int,
    one_hot: bool = False,
) -> Tuple[np.ndarray, np.ndarray]:
    """
    Generate samples from the data segment.
    Author: Seongjae Lee
    """
    if cls_id >= num_class:
        raise ValueError("class id is out of bound")
    sampled_data = np.array(
        [
            data[i : i + sample_length]
            for i in range(0, len(data) - sample_length, shift)
        ]
    )
    if one_hot:
        label = np.zeros((sampled_data.shape[0], num_class))
        label[:, cls_id] = 1
    else:
        label = np.zeros((sampled_data.shape[0]))
        label = label + cls_id
    return sampled_data, label

def STbuild_from_dataframe(
    df: pd.DataFrame, sample_length: int, shift: int, one_hot: bool = False
) -> Tuple[np.ndarray, np.ndarray]:
    """
    Generate pairs of np.ndarrays from a dataframe.
    Author: Seongjae Lee
    """
    n_class = df["label"].max() - df["label"].min() + 1
    n_data = df.shape[0]
    data = []
    label = []
    for i in range(n_data):
        d = df.iloc[i]["data"]
        td, tl = STsample_data(
            d, sample_length, shift, df.iloc[i]["label"], n_class, one_hot
        )
        data.append(td)
        label.append(tl)

    data_array = np.concatenate(tuple(data), axis=0)
    label_array = np.concatenate(tuple(label), axis=0)

    return data_array, label_array

def STsample_data(
    data: np.ndarray,
    sample_length: int,
    shift: int,
    cls_id: int,
    num_class: int,
    one_hot: bool = False,
) -> Tuple[np.ndarray, np.ndarray]:
    """
    Generate samples from the data segment.
    Author: Seongjae Lee
    """
    if cls_id >= num_class:
        raise ValueError("class id is out of bound")
    sampled_data = np.array(
        [
            data[i : i + sample_length]
            for i in range(0, len(data) - sample_length+1, shift)
        ]
    )
    if one_hot:
        label = np.zeros((sampled_data.shape[0], num_class))
        label[:, cls_id] = 1
    else:
        label = np.zeros((sampled_data.shape[0]))
        label = label + cls_id
    return sampled_data, label