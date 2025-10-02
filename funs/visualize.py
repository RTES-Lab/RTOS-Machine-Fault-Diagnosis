# visualize.py

import os

from sklearn.metrics import confusion_matrix, accuracy_score
import matplotlib.pyplot as plt
import seaborn as sns

import numpy as np

def plot_confusion_matrix(root, fault_label_list, predicted_label_list, pic_name):
    os.makedirs(f'{root}/', exist_ok=True)

    class_labels = ['H', 'L', 'M1', 'M2', 'M3', 'U1', 'U2', 'U3']

    cm = confusion_matrix(fault_label_list, predicted_label_list, normalize='true')
    acc = accuracy_score(fault_label_list, predicted_label_list)

    # 시각화
    plt.figure(figsize=(8, 6))
    sns.heatmap(cm, annot=True, fmt=".2f", cmap="Blues", 
                xticklabels=class_labels, yticklabels=class_labels)
    plt.xlabel("Predicted Labels")
    plt.ylabel("True Labels")
    plt.title(f"Confusion Matrix (Mean Acc: {acc:.2f})")
    plt.savefig(f'{root}/{pic_name}')