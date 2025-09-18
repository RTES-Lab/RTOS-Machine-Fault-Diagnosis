# trainer.py

import numpy as np
import torch
import os 

class Trainer:
    def __init__(self, model, loss, optimizer, device, train_loader, eval_loader):
        self.model = model
        self.loss = loss
        self.optimizer = optimizer
        self.device = device
        self.train_loader = train_loader
        self.eval_loader = eval_loader

    def train(self, epoch):
        print("\nStarting Training... \n" + "-" * 40)
        self.model.train()
        train_loss_list = []
        val_loss_list = []

        for ep in range(0, epoch + 1):
            train_loss, train_accuracy = self.training_step(self.train_loader)
            train_loss_list.append(train_loss)

            if ep % 10 == 0 or ep == epoch:
                _, val_loss, _ = self.eval(self.eval_loader)
                val_loss_list.append(val_loss)
                print(f'[EPOCH: {ep}] \nTrain Loss: {train_loss:.5f}\nTrain Acc: {train_accuracy:.5f}\n'
                      f'Validation Loss: {val_loss:.5f}\n' + '-' * 40)

        return train_loss_list, val_loss_list

    def training_step(self, train_loader):
        train_loss = 0.0
        correct = 0

        for batch_idx, (data, label) in enumerate(train_loader):
            x = data.to(self.device)
            label = label.to(self.device)

            output = self.model(x)
            loss = self.loss(output, label.long())

            self.optimizer.zero_grad()
            loss.backward()
            self.optimizer.step()

            train_loss += loss.item()
            prediction = output.max(1, keepdim = True)[1]
            correct += prediction.eq(label.view_as(prediction)).sum().item()
        
        train_loss /= len(train_loader)
        train_accuracy = correct / len(train_loader.dataset)
        return train_loss, train_accuracy
            
    def eval(self, eval_loader):
        self.model.eval()
        eval_loss_list, fault_label_list, predicted_label_list = self.validation_step(eval_loader)

        val_loss = np.mean(eval_loss_list)
            
        return fault_label_list, val_loss, predicted_label_list
    
    def test(self, test_loader):
        print("\nStarting Test... \n" + "-" * 40)
        self.model.eval()
        test_loss_list, fault_label_list, predicted_label_list = self.validation_step(test_loader)

        test_loss = np.mean(test_loss_list)
        print(f'Test Loss: {test_loss:.5f}')
            
        return fault_label_list, test_loss_list, predicted_label_list

    def validation_step(self, dataloder):
        eval_loss_list = []

        fault_label_list = []
        predicted_label_list = []

        with torch.no_grad():
            for batch_idx, (data, label) in enumerate(dataloder):
                x = data.to(self.device)
                label = label.to(self.device)

                output = self.model(x)
                loss = self.loss(output, label.long())
                eval_loss_list.append(loss.item())

                fault_label_list.extend(label.cpu().numpy().tolist())
                prediction = output.max(1, keepdim=True)[1]
                predicted_label_list.extend(prediction.cpu().numpy().flatten().tolist())

        return eval_loss_list, fault_label_list, predicted_label_list


    def save(self, root, model_name):
        os.makedirs(f'{root}/', exist_ok=True)
        torch.save(self.model.state_dict(), f'{root}/{model_name}.pt')