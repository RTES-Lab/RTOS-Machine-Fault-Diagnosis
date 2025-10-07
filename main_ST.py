import funs
import funs.model as model

import torch
import os

from torch.optim import Adam
from torch.nn import CrossEntropyLoss
from torchvision import transforms

from sklearn.model_selection import train_test_split

def main(config, args):
    # Initalize 
    funs.set_seed(config.seed)
    device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
    print('device =', device)

    # Argument setting
    aEp = args.epochs

    # name setting
    model_name = f'ST_FRFconv-TDS_{aEp}'
    log_file = f'ST_log_per_acc_{aEp}.txt'
    cm_name = f'ST_confusion_matrix_{aEp}.png'

    # Data preparation
    data_root_dirs = os.path.join(config.dataset_root_st)

    print("Making dataframes...")

    df =funs.STmake_dataframe(config, data_root_dirs)

    # Split the dataframe into train, validation, and test sets
    train_df, temp_df = train_test_split(
        df, 
        test_size=0.4,      # 40%를 val+test로 남김
        stratify=df['label'], 
        random_state=config.seed
    )

    val_df, test_df = train_test_split(
        temp_df, 
        test_size=0.5,      # 남은 40% 중 절반씩
        stratify=temp_df['label'], 
        random_state=config.seed
    )

    train_df = train_df.reset_index(drop=True)
    val_df = val_df.reset_index(drop=True)
    test_df = test_df.reset_index(drop=True)

    # Build data
    train_data, train_label = funs.STbuild_from_dataframe(train_df, config.sample_size, config.overlap, False)
    val_data, val_label = funs.STbuild_from_dataframe(val_df, config.sample_size, config.overlap, False)
    test_data, test_label = funs.STbuild_from_dataframe(test_df, config.sample_size, config.overlap, False)

    # np -> tensor transform
    tf_data = transforms.Compose([funs.processing.NpToTensor(), funs.processing.ToSignal()])
    tf_label = transforms.Compose([funs.processing.NpToTensor()])

    # Dataset & Dataloader
    train_dataset = funs.NumpyDataset(train_data, train_label, transform=tf_data, target_transform=tf_label)
    val_dataset = funs.NumpyDataset(val_data, val_label, transform=tf_data, target_transform=tf_label)
    test_dataset = funs.NumpyDataset(test_data, test_label, transform=tf_data, target_transform=tf_label)

    train_loader = funs.get_dataloader(train_dataset, config.batch_size, True)
    val_loader = funs.get_dataloader(val_dataset, config.batch_size, False)
    test_loader = funs.get_dataloader(test_dataset, config.batch_size, False)


    # Model, Optimizer, Loss
    n_classes = df["label"].max() - df["label"].min() + 1
    FRFconv_TDS = model.Mynet2(n_classes=n_classes).to(device)

    optimizer = Adam(FRFconv_TDS.parameters(), lr = float(config.learning_rate))
    loss = CrossEntropyLoss()

    # Train & Test
    trainer = funs.Trainer(FRFconv_TDS, loss, optimizer, device, train_loader, val_loader)
    _, _ = trainer.train(epoch=aEp)              # train
    trainer.save(config.model_root_st, model_name) # save the trained model

    model_path = f'{config.model_root_st}/{model_name}.pt'
    trainer.model.load_state_dict(torch.load(model_path, weights_only=True))        # load the trained model

    fault_label_list, test_loss, predicted_label_list = trainer.test(test_loader)   # test

    # acc per class logging
    funs.log_class_acc(config.log_root_st, fault_label_list, predicted_label_list, f'{log_file}')

    # confusion matrix plot
    funs.plot_confusion_matrix(config.pic_root_st ,fault_label_list, predicted_label_list, cm_name)

if __name__=='__main__':
    config = funs.load_yaml('./config.yaml')
    args = funs.parse_arguments()

    main(config, args)