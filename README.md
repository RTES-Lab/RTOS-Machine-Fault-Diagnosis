# RTOS-Machine-Fault-Diagnosis

RTES 연구실 2025년 여름방학 스터디

## 실행 방법

1. `dataset/` 폴더에 UOS 데이터셋을 위치시킵니다.

```text
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
```

2. 실행 명령어:
   ```bash
   python main.py --epochs 50
   ```
   또는
   ```bash
   ./main.sh
   ```

## 파일 구조

### 폴더

- **dataset**: UOS 데이터셋
- **funs**: 코드에 필요한 함수 패키지
- **models**: 저장된 모델
- **pics**: 그림 파일 (예: confusion matrix)

### 파일

- **config.yaml**: 설정값을 모아둔 yaml 파일
- **main.py**: 주 실행 코드. 실행 시 에폭 인자를 입력해야 함 (예: --epochs 50)
- **main.sh**: main.py를 쉽게 실행하기 위한 쉘 스크립트
- **torch2onnx.py**: .pt 파일을 .onnx로 변환하는 코드
- **test.ipynb**: 개인 확인용 ipynb 파일 (무시)
- **quant.ipynb**: 개인 확인용 ipynb 파일 (무시)