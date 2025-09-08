import numpy as np

import torch
from torch import nn
import torch.nn.functional as F
import copy

from typing import Union, Tuple, List

class DownSampler(nn.Module):
    def __init__(self, in_channels, out_channels, kernel_size, downsample_ratio, len=None):
        super(DownSampler, self).__init__()
        stride = downsample_ratio
        padding_size = int((kernel_size-stride)/2)
        if len is not None:
            norm1 = torch.nn.GroupNorm(out_channels,out_channels)
            norm2 = torch.nn.GroupNorm(in_channels,in_channels)
            norm3 = torch.nn.GroupNorm(out_channels,out_channels)
        else:
            norm1 = torch.nn.BatchNorm1d(out_channels)
            norm2 = torch.nn.BatchNorm1d(in_channels)
            norm3 = torch.nn.BatchNorm1d(out_channels)
        if in_channels == 1:
            self.conv = nn.Sequential(
                torch.nn.Conv1d(in_channels, out_channels, kernel_size, stride, padding_size),
                norm1,
                torch.nn.ReLU(),
            )
        else:
            self.conv = nn.Sequential(
                torch.nn.Conv1d(in_channels, in_channels, kernel_size, stride, padding_size, groups=in_channels),
                norm2,
                torch.nn.ReLU(),
                torch.nn.Conv1d(in_channels, out_channels, 1),
                norm3,
                torch.nn.ReLU(),
            )
        
    def forward(self, x):
        y = self.conv(x)
        return y

class ExpandDsConv1d(nn.Module):
    def __init__(self, in_channels, out_channels, kernel_size, expand_ratio, len=None):
        super(ExpandDsConv1d, self).__init__()
        padding_size = int((kernel_size-1)/(2))
        if len is not None:
            # norm1 = torch.nn.LayerNorm([len])
            # norm2 = torch.nn.LayerNorm([len])
            norm1 = torch.nn.GroupNorm(in_channels*expand_ratio,in_channels*expand_ratio)
            norm2 = torch.nn.GroupNorm(out_channels,out_channels)
        else:
            norm1 = torch.nn.BatchNorm1d(int(in_channels*expand_ratio))
            norm2 = torch.nn.BatchNorm1d(out_channels)
        self.dwconv = torch.nn.Sequential(
            torch.nn.Conv1d(in_channels, int(in_channels*expand_ratio),
                            kernel_size, stride=1, padding=padding_size,
                            groups=in_channels),
            norm1,
            torch.nn.ReLU(),
        )
        self.pwconv = torch.nn.Sequential(            
            torch.nn.Conv1d(in_channels*expand_ratio, out_channels, 1),
            norm2,
        )
        self.act = torch.nn.ReLU()
        self.identical = in_channels == out_channels
        self.add = torch.nn.quantized.FloatFunctional()

    def forward(self, x):
        y = self.dwconv(x)
        y = self.pwconv(y)
        if self.identical:
            y = self.add.add(x, y)
            y = self.act(y)
        return y
    
class Mixer(nn.Module):
    def __init__(self, in_channels, out_channels, len=None):
        super(Mixer, self).__init__()
        self.layer = nn.Sequential(
            torch.nn.Linear(len, len),
            torch.nn.BatchNorm1d(in_channels),
            torch.nn.ReLU(),
            torch.nn.Conv1d(in_channels, out_channels, 1),
            torch.nn.BatchNorm1d(out_channels)
        )
        self.act = torch.nn.ReLU()
        self.identical = in_channels == out_channels
        self.add = torch.nn.quantized.FloatFunctional()

    def forward(self, x):
        y = self.layer(x)
        if self.identical:
            y = self.add.add(x, y)
            y = self.act(y)
        return y

    
class Mynet2(nn.Module):
    def __init__(self, n_classes=10,
                 first_kernel=64,
                 ds_factor=8,
                 channel=8,
                 rf_factor=1,
                 n_convs=3,
                 use_tds=True,
                 manual_kernel=None):
        super(Mynet2, self).__init__()

        input_length = 2048
        c = channel
        ratio= rf_factor
        self.use_tds = use_tds

        fields = [int(input_length / ds_factor),
                  int(input_length / ds_factor / ds_factor)]
        
        k = [int(fields[0] * ratio - 1),
             int(fields[1] * ratio - 1)]
        
        if manual_kernel is not None:
            k = manual_kernel

        self.convnet = nn.Sequential()
        self.convnet.add_module("dropout", nn.Dropout(0.5))
        self.convnet.add_module("conv1",
                                DownSampler(1, c, first_kernel, ds_factor, len=None))
        for i in range(n_convs):
            self.convnet.add_module(f"conv2_{i+1}",
                                    ExpandDsConv1d(c, c, k[0], 1, len=None))
        self.convnet.add_module("conv2",
                                DownSampler(c, c, 24, ds_factor, len=None))
        for i in range(n_convs):
            self.convnet.add_module(f"conv3_{i}",
                                    ExpandDsConv1d(c, c, k[1], 1, len=None))
        self.convnet.add_module(f"conv4",
                                nn.Sequential(
                                    nn.Conv1d(c, 8, 9, 1, 4),
                                    nn.BatchNorm1d(8),
                                    nn.ReLU()
                                ))
        self.convnet.add_module("gap", torch.nn.AdaptiveAvgPool1d((1)))
        self.convnet.add_module("flatten", torch.nn.Flatten())

        # self.mini_mlp = nn.Sequential(
        #     nn.Linear(4, 16),
        #     nn.BatchNorm1d(16),
        #     nn.Linear(16, 4),
        #     nn.BatchNorm1d(4),
        # )

        if use_tds:
            self.linear = nn.Sequential(
                # torch.nn.BatchNorm1d(12),
                torch.nn.Linear(8+4, n_classes)
            )
        else:
            self.linear = torch.nn.Linear(8, n_classes)
    
    def get_tds_(self, x):
        u = torch.mean(x, (2), keepdim=True)
        pk, _ = torch.max(torch.abs(x), dim=(2), keepdim=True)
        std = torch.std(x, dim=(2), keepdim=True)
        rms = torch.sqrt(torch.mean(x*x, (2), keepdim=True))
        crest = pk / rms
        kurtosis = (1 / (std**4))*torch.mean((x-u)**4, (2), keepdim=True)
        skew = (1 / (std**3))*torch.mean((x-u)**3, (2), keepdim=True)

        return torch.cat((u, pk, rms, crest, skew, kurtosis, std), 1).squeeze(2)
    
    def normalize_(self, x):
        linf, _ = torch.max(torch.abs(x), dim=(2), keepdim=True)
        return x / linf

    
    def forward(self, x):
        rawsig = self.normalize_(x)
        tds = self.get_tds_(x)[:, :4]
        # tds = self.mini_mlp(tds)

        rawsig = self.convnet(rawsig)

        if self.use_tds:
            concated = torch.concat((rawsig, tds), dim=1)
        else:
            concated = rawsig

        y = self.linear(concated)

        return y
    
    def get_intermediate_output(self, x):
        o = []

        x = self.normalize_(x)
        tds = self.get_tds_(x)[:, :4]

        for layer in [0, 1]:
            x = self.convnet[layer](x)
        
        o.append(x.cpu().detach().numpy())

        for layer in [2, 3, 4]:
            x = self.convnet[layer](x)
        
        o.append(x.cpu().detach().numpy())

        for layer in [5]:
            x = self.convnet[layer](x)
        
        o.append(x.cpu().detach().numpy())

        for layer in [6, 7, 8]:
            x = self.convnet[layer](x)
        
        o.append(x.cpu().detach().numpy())

        return o



class ConvBackbone(nn.Module):
    def __init__(self, n_classes=10,
                 first_kernel=64,
                 ds_factor=8,
                 channel=16,
                 rf_factor=1,
                 n_convs=1,
                 manual_kernel=None):
        super(ConvBackbone, self).__init__()

        input_length = 2048
        self.c = channel
        ratio= rf_factor

        fields = [int(input_length / ds_factor),
                  int(input_length / ds_factor / ds_factor)]
        
        k = [int(fields[0] * ratio - 1),
             int(fields[1] * ratio - 1)]
        
        if manual_kernel is not None:
            k = manual_kernel

        self.pre = nn.Dropout(0.5)
        self.convnet = nn.Sequential()
        self.convnet.add_module("dropout", nn.Dropout(0.5))
        self.convnet.add_module("conv1",
                                DownSampler(1, self.c, first_kernel, ds_factor, len=None))
        for i in range(n_convs):
            self.convnet.add_module(f"conv2_{i+1}",
                                    ExpandDsConv1d(self.c, self.c, k[0], 1, len=None))
        self.convnet.add_module("conv2",
                                DownSampler(self.c, self.c, first_kernel, ds_factor, len=None))
        for i in range(n_convs):
            self.convnet.add_module(f"conv3_{i}",
                                    ExpandDsConv1d(self.c, self.c, k[1], 1, len=None))
        self.convnet.add_module("gap", torch.nn.AdaptiveAvgPool1d((1)))
        self.convnet.add_module("flatten", torch.nn.Flatten())

        self.linear = torch.nn.Linear(self.c, n_classes)
    
    def normalize_(self, x):
        linf, _ = torch.max(torch.abs(x), dim=(2), keepdim=True)
        return x / linf
    
    def forward(self, x):
        x = self.normalize_(x)
        x = self.convnet(x)
        x = self.linear(x)

        return x

class TDSnet(nn.Module):
    def __init__(self,
                 n_classes=10,
                 first_kernel=64,
                 ds_factor=8,
                 channel=16,
                 rf_factor=1,
                 n_convs=1,
                 manual_kernel=None):
        super(TDSnet, self).__init__()
        self.backbone = ConvBackbone(n_classes,
                                     first_kernel,
                                     ds_factor,
                                     channel,
                                     rf_factor,
                                     n_convs,
                                     manual_kernel)
        for p in self.backbone.parameters():
            p.requires_grad = False
        self.clf = torch.nn.Linear(channel + 4, n_classes)
    
    def load_backbone_(self, path):
        self.backbone.load_state_dict(torch.load(path))
        for p in self.backbone.parameters():
            p.requires_grad = False

    def get_tds_(self, x):
        u = torch.mean(x, (2), keepdim=True)
        pk, _ = torch.max(x, dim=(2), keepdim=True)
        mpk = torch.min(x, dim=(2), keepdim=True)
        pk2pk = pk - mpk
        std = torch.std(x, dim=(2), keepdim=True)
        rms = torch.sqrt(torch.mean(x*x, (2), keepdim=True))
        crest = pk / rms
        kurtosis = (1 / (std**3))*torch.mean((x-u)**3, (2), keepdim=True)

        return torch.cat((kurtosis, pk2pk, rms, crest, std, kurtosis), 1).squeeze(2)
    
    def normalize_(self, x):
        linf, _ = torch.max(torch.abs(x), dim=(2), keepdim=True)
        return x / linf
    
    def forward(self, x):
        y = self.normalize_(x)
        y = self.backbone.convnet(y)
        tds = self.get_tds_(x)[:, :4]
        y = torch.concat((y, tds), dim=1)
        y = self.clf(y)

        return y