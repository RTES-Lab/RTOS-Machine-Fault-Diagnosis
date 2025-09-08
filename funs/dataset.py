# dataset.py

from torch.utils.data import Dataset, DataLoader
import numpy as np
from torchvision import transforms

from typing import Tuple

class NumpyDataset(Dataset):
    """
    PyTorch Dataset for numpy array-style dataset.
    Author: Seongjae Lee

    Attributes
    ----------
    data: np.ndarray
        Numpy array-style data. shape: [N, ...]
    label: np.ndarray
        Numpy array-style label. shape: [N,]
    transfrom: torchvision.transforms.transforms.Compose
        Data transform class. default: None
    target_transform: torchvision.transforms.transforms.Compose
        Label transform class. default: None

    Methods
    ----------
    __len__:
        Return the length of the data.
    __getitem__(idx):
        Return the "idx-th" index of the data.
    """

    def __init__(
        self,
        data: np.ndarray,
        label: np.ndarray,
        transform: transforms.transforms.Compose = None,
        target_transform: transforms.transforms.Compose = None,
    ) -> None:
        self.data = data
        self.label = label
        self.transform = transform
        self.target_transform = target_transform

    def __len__(self) -> int:
        return self.data.shape[0]

    def __getitem__(self, idx: int) -> Tuple[np.ndarray, np.ndarray]:
        x = self.data[idx, :].astype("float32")
        t = np.array(self.label[idx]).astype("int64")

        if self.transform:
            x = self.transform(x)
        if self.target_transform:
            t = self.target_transform(t)

        return x, t
    
def get_dataloader(dataset: Dataset, batch_size: int, shuffle: bool = False) -> DataLoader:
    return DataLoader(dataset, batch_size=batch_size, shuffle=shuffle, drop_last=False, pin_memory=True)
