# processing.py

import torch

class NpToTensor:
    """
    Convert numpy array to PyTorch Tensor
    Author: Seongjae Lee
    """
    def __call__(self, x):
        return torch.from_numpy(x)

class ToSignal:
    """
    Convert (N, ) 1D Tensor to (1, N) 2D Tensor
    Author: Seongjae Lee
    """

    def __call__(self, x):
        return x.view(1, -1)