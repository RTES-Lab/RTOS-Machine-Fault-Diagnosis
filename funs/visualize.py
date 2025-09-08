# visualize.py

import os

from sklearn.metrics import confusion_matrix
import matplotlib.pyplot as plt
import seaborn as sns

import numpy as np

def plot_confusion_matrix(root, fault_label_list, predicted_label_list, pic_name):
    os.makedirs(f'{root}/', exist_ok=True)

    cm = confusion_matrix(fault_label_list, predicted_label_list)
    classes = np.unique(fault_label_list)  

    # 시각화
    plt.figure(figsize=(8, 6))
    sns.heatmap(cm, annot=True, fmt="d", cmap="Blues", xticklabels=classes, yticklabels=classes)
    plt.xlabel("Predicted Labels")
    plt.ylabel("True Labels")
    plt.title("Confusion Matrix")
    plt.savefig(f'{root}/{pic_name}')