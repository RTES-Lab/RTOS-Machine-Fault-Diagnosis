#!/bin/bash

nohup python -u main.py --epochs 50 --rpm 1400 > ./logs/epochs_50_1400rpm.log 
nohup python -u main.py --epochs 500 --rpm 1400 > ./logs/epochs_500_1400rpm.log 
nohup python -u main.py --epochs 1000 --rpm 1400 > ./logs/epochs_1000_1400rpm.log 
nohup python -u main.py --epochs 100 --rpm 1400 > ./logs/epochs_100_1400rpm.log 