#!/bin/bash

# nohup python -u main_UOS.py --epochs 50 --rpm 1400 > ./logs/epochs_50_1400rpm.log 
# nohup python -u main_UOS.py --epochs 500 --rpm 1400 > ./logs/epochs_500_1400rpm.log 
# nohup python -u main_UOS.py --epochs 1000 --rpm 1400 > ./logs/epochs_1000_1400rpm.log 
# nohup python -u main_UOS.py --epochs 100 --rpm 1400 > ./logs/epochs_100_1400rpm.log 

# nohup python -u main_ST.py --epochs 50 --rpm 1400 > ./logs_st/STepochs_50.log 
# nohup python -u main_ST.py --epochs 500 --rpm 1400 > ./logs_st/STepochs_500.log 
# nohup python -u main_ST.py --epochs 1000 --rpm 1400 > ./logs_st/STepochs_1000.log 
# nohup python -u main_ST.py --epochs 100 --rpm 1400 > ./logs_st/STepochs_100.log 

# nohup python -u main_ST.py --epochs 50 --rpm 1400 > ./logs_st/STepochs_50_1013.log 
# nohup python -u main_ST.py --epochs 100 --rpm 1400 > ./logs_st/STepochs_100_1013.log 
# nohup python -u main_ST.py --epochs 500 --rpm 1400 > ./logs_st/STepochs_500_1013.log 
# nohup python -u main_ST.py --epochs 1000 --rpm 1400 > ./logs_st/STepochs_1000_1013.log 

nohup python -u main_ST_8c.py --epochs 50 --rpm 1400 > ./logs_st/STepochs_50_1013_v2.log 
nohup python -u main_ST_8c.py --epochs 100 --rpm 1400 > ./logs_st/STepochs_100_1013_v2.log 
nohup python -u main_ST_8c.py --epochs 500 --rpm 1400 > ./logs_st/STepochs_500_1013_v2.log 
nohup python -u main_ST_8c.py --epochs 1000 --rpm 1400 > ./logs_st/STepochs_1000_1013_v2.log 

nohup python -u main_ST.py --epochs 50 --rpm 1400 > ./logs_st/STepochs_50_1013_v3.log 
nohup python -u main_ST.py --epochs 100 --rpm 1400 > ./logs_st/STepochs_100_1013_v3.log 
nohup python -u main_ST.py --epochs 500 --rpm 1400 > ./logs_st/STepochs_500_1013_v3.log 
nohup python -u main_ST.py --epochs 1000 --rpm 1400 > ./logs_st/STepochs_1000_1013_v3.log 