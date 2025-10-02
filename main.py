import funs
import funs.model as model

import torch
import os

from torch.optim import Adam
from torch.nn import CrossEntropyLoss
from torchvision import transforms

import pandas as pd 

def main(config, args):
    # Initalize 
    funs.set_seed(config.seed)
    device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
    print('device =', device)

    # Argument setting
    aEp = args.epochs
    aRpm = args.rpm
    aBearingType = "DeepGrooveBall"

    # name setting
    model_name = f'FRFconv-TDS_{aEp}_rpm{aRpm}_{aBearingType}'
    log_file = f'log_per_acc_{aEp}_rpm{aRpm}_{aBearingType}.txt'
    cm_name = f'confusion_matrix_{aEp}_rpm{aRpm}_{aBearingType}.png'

    # Data preparation
    data_root_dirs = os.path.join(config.dataset_root)

    if aRpm: # given rpm 
        # Cylindrical_dirs = funs.get_bearing_paths(data_root_dirs, 'CylindricalRoller', [aRpm], config.sampling_rate)
        DepGroove_dirs = funs.get_bearing_paths(data_root_dirs, 'DeepGrooveBall', [aRpm], config.sampling_rate)
        # Tapered_dirs = funs.get_bearing_paths(data_root_dirs, 'TaperedRoller', [aRpm].rpm, config.sampling_rate)
    else: # default rpm list
        # Cylindrical_dirs = funs.get_bearing_paths(data_root_dirs, 'CylindricalRoller', config.rpm, config.sampling_rate)
        DepGroove_dirs = funs.get_bearing_paths(data_root_dirs, 'DeepGrooveBall', config.rpm, config.sampling_rate)
        # Tapered_dirs = funs.get_bearing_paths(data_root_dirs, 'TaperedRoller', config.rpm, config.sampling_rate)

    print("Making dataframes...")

    # Cylindrical_df = funs.make_dataframe(config, Cylindrical_dirs)
    DepGroove_df =funs.make_dataframe(config, DepGroove_dirs)
    # Tapered_df = funs.make_dataframe(config, Tapered_dirs)  

    print("concat dataframes...")
    # all_df = pd.concat([Cylindrical_df, DepGroove_df, Tapered_df], ignore_index=True)
    all_df = DepGroove_df

    # Split the dataframe into train, validation, and test sets
    train_df, val_df, test_df = funs.split_dataframe(all_df, 0.6, 0.2)

    # Build data
    train_data, train_label = funs.build_from_dataframe(train_df, config.sample_size, config.overlap, False)
    val_data, val_label = funs.build_from_dataframe(val_df, config.sample_size, config.overlap, False)
    test_data, test_label = funs.build_from_dataframe(test_df, config.sample_size, config.overlap, False)

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
    n_classes = all_df["label"].max() - all_df["label"].min() + 1
    FRFconv_TDS = model.Mynet2(n_classes=n_classes).to(device)

    optimizer = Adam(FRFconv_TDS.parameters(), lr = float(config.learning_rate))
    loss = CrossEntropyLoss()

    # Train & Test
    trainer = funs.Trainer(FRFconv_TDS, loss, optimizer, device, train_loader, val_loader)
    _, _ = trainer.train(epoch=aEp)              # train
    trainer.save(config.model_root, model_name) # save the trained model

    model_path = f'{config.model_root}/{model_name}.pt'
    trainer.model.load_state_dict(torch.load(model_path, weights_only=True))        # load the trained model

    fault_label_list, test_loss, predicted_label_list = trainer.test(test_loader)   # test

    # acc per class logging
    funs.log_class_acc(config.log_root, fault_label_list, predicted_label_list, f'{log_file}')
    # confusion matrix plot
    funs.plot_confusion_matrix(config.pic_root ,fault_label_list, predicted_label_list, cm_name)

if __name__=='__main__':
    config = funs.load_yaml('./config.yaml')
    args = funs.parse_arguments()

    main(config, args)