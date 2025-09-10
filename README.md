# RTOS-Machine-Fault-Diagnosis
RTES 연구실 2025 여름방학 스터디

실행방법
1. dataset/ 폴더에 UOS 데이터셋 위치
dataset/
├── BearingType_CylindricalRoller
│   ├── SamplingRate_16000
│   │   ├── RotatingSpeed_1000
│   │   ├── RotatingSpeed_1200
│   │   ├── RotatingSpeed_1400
│   │   ├── RotatingSpeed_1600
│   │   ├── RotatingSpeed_600
│   │   └── RotatingSpeed_800
│   └── SamplingRate_8000
│       ├── RotatingSpeed_1000
│       ├── RotatingSpeed_1200
│       ├── RotatingSpeed_1400
│       ├── RotatingSpeed_1600
│       ├── RotatingSpeed_600
│       └── RotatingSpeed_800
├── BearingType_DeepGrooveBall
│   ├── SamplingRate_16000
│   │   ├── RotatingSpeed_1000
│   │   ├── RotatingSpeed_1200
│   │   ├── RotatingSpeed_1400
│   │   ├── RotatingSpeed_1600
│   │   ├── RotatingSpeed_600
│   │   └── RotatingSpeed_800
│   └── SamplingRate_8000
│       ├── RotatingSpeed_1000
│       ├── RotatingSpeed_1200
│       ├── RotatingSpeed_1400
│       ├── RotatingSpeed_1600
│       ├── RotatingSpeed_600
│       └── RotatingSpeed_800
└── BearingType_TaperedRoller
    ├── SamplingRate_16000
    │   ├── RotatingSpeed_1000
    │   ├── RotatingSpeed_1200
    │   ├── RotatingSpeed_1400
    │   ├── RotatingSpeed_1600
    │   ├── RotatingSpeed_600
    │   └── RotatingSpeed_800
    └── SamplingRate_8000
        ├── RotatingSpeed_1000
        ├── RotatingSpeed_1200
        ├── RotatingSpeed_1400
        ├── RotatingSpeed_1600
        ├── RotatingSpeed_600
        └── RotatingSpeed_800
2. $ python main.py

# 파일 구조 설명
## 폴더
funs: 코드 작업에 필요한 여러 함수들을 모아둔 패키지
models: 저장된 모델들
pics: 그림들 (ex: confusion matrix)

## 파일
config.yaml: 기타 설정값들을 모아둔 yaml 파일
main.py: 주 실행 코드
test.ipynb: 개인 확인용 ipynb 파일