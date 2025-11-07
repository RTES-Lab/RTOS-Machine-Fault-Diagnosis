# 🧠 Machine Fault Diagnosis on MCU
**Shaft Fault Diagnosis on STM32F401RET6**

---

## 📘 Overview
본 프로젝트는 **STM32F401RET6** Microcontroller(MCU) 위에서 구동되는 **축(Shaft) 고장 진단 시스템**입니다.  
가속도계(ModalShop 333D01 USB 센서)로부터 진동 데이터를 수집하고, 
경량 모델인 FRFconv-TDSNet을 바탕으로 **축 결함(Shaft Fault)**을 진단하고, 해당 결과를 아두이노 I2C 1602 LCD 모듈을 통해 출력합니다.

---

## 🧩 Latest Update (Nov 2025)

* 2025.11.07 : README.md Update

---

## 🧩 Directory Structure

```

RTOS-Machine-Fault-Diagnosis/
├── Core/
│   ├── Inc/              # 헤더 파일 (main.h, i2c_lcd.h 등)
│   └── Src/              # 주요 소스 코드 (main.c, i2c_lcd.c 등)
│
├── Middlewares/
│   ├── ST/
│   │   └── AI/           # X-CUBE-AI 생성 파일
│
├── USB_HOST/
│   ├── App/
│   └── Target/
│
├── X-CUBE-AI/
│   └── App/
│       ├── frfconv.c / .h
│       ├── frfconv_data.c / .h
│       ├── frfconv_config.h
│       ├── app_x-cube-ai.c / .h
│       ├── frfconv_generate_reprot.txt
│       └── frfconv_data_params.c /h
│
├── Debug/
│   └── (빌드 아티팩트: .cyclo, .list 등)
│
├── STM32F401RETX_FLASH.ld
├── RTOS-Machine-Fault-Diagnosis-test-execution_time.ioc
└── README.md

```

---

## 🧠 AI Model (X-CUBE-AI)

| 항목 | 설명 |
|------|------|
| **Model Name** | FRFConv-TDS |
| **Model MCU 임베딩 방식** | PyTorch → ONNX → X-CUBE-AI |
| **Input Dimension** | 1 × 2048 (time-series vibration signal) |
| **Output Classes** | Normal / Looseness (L) / Misalignment (M1, M2, M3) / Unbalance (U1, U2, U3) |
---

## 🔌 Hardware Configuration

| 구성 요소 | 설명 |
|------------|------|
| **MCU** | STM32F401RET6 (ARM 32-bit Cortex-M4 (84 MHz) / 512 KB Flash / 96 KB SRAM) |
| **Sensor** | ModalShop 333D01 USB Digital Accelerometer |
| **LCD** | Arduino I2C 1602 LCD Module |
---

## 🧰 Build & Run

1. **STM32CubeIDE** 실행
2. **Select a directory as workspace**에서, 해당 프로젝트 선택후 Launch
3. **STM32CubeIDE**에서 'File' 선택 후 'Import' → 'General' → 'Existing Projects into Workspace' → 'Next'
4. **Import Projects**에서 'Select root directory' 옆의 'Browse' 클릭 후 프로젝트와 동일한 이름의 내부 디렉토리 클릭 후 '폴더 선택', 이후 'Finish'
5. **'Project Explorer'**의 프로젝트 명 위에서 우클릭 후 'Clean Project' → 'Build Project'
6. PC와 MCU 연결 후 **상단 바의 'Run' 버튼 실행**
---

## 🧭 Repository Info

| Branch                         | 설명 |
| ------------------------------ | -------------------- |
| **main**                       | 안정 버전 (USB 가속도계 → X-CUBE-AI 모델 → LCD 표시까지 통합 완료된 코드) |
| **feature/integrated_version** | USB 마이크 가속도계에서 2,048개 진동 샘플(48kHz→16kHz 다운샘플)을 수집한 뒤 FRFconv 모델로 추론하고, 16×2 I2C LCD에 H/L/M1–M3/U1–U3 라벨 및 OK/ALRT 상태·신뢰도(%)를 표시하는 비-RTOS 단일 루프 통합 버전 브랜치 |
| **test/model_task**            | FreeRTOS의 xTaskCreate() API를 활용하여 단일 modelTask만 스케줄링, modelTask는 FRFConv 딥러닝 모델 1회 추론에 걸리는 시간을 FreeRTOS tick 기준으로 100번 측정한 뒤, 평균/최소/최대/분산/표준편차를 ms 단위로 UART로 출력하는 태스크 |
| **test/model**                 | PC 기반의 FRFconv 모델 학습용 브랜치 |
| **test/rtosX**                 | USB 진동 데이터 수집 → FRFconv 모델 단일 추론 → LCD 결과 표시까지의 파이프라인을 main 루프에서 폴링 방식으로 동작시키며, 추후 FreeRTOS 태스크로 분리하기 위한 기반 코드를 포함한 RTOS 포팅 실험 브랜치 |
| **test/16kHz_Verification**    | USB 마이크에서 24bit 2채널 데이터를 받아 3배 다운샘플링(48kHz→16kHz)·스케일링한 후, 2,048 샘플이 채워질 때마다 헤더(0xAA, 0xFF)와 함께 float 배열을 UART로 전송해 **16kHz 유효 샘플링 및 스트리밍 동작을 검증**하는 FreeRTOS 태스크 기반 브랜치 (LCD에는 간단한 “Hello World” 메시지 출력) |
| **test/execution_time**        | DWT 사이클 카운터를 활성화해 USB 2,048샘플 수집 태스크, FRFconv 모델 추론 태스크、 LCD 갱신 태스크 각각의 실행 시간을 μs/ms 수준으로 측정하고, 평균/최소/최대/표준편차를 계산해 UART로 출력하는 정밀 실행 시간 측정용 브랜치 |


---

## 🧾 License

이 프로젝트는 **MIT License** 하에 배포됩니다.
일부 모듈은 다음 라이선스를 따릅니다:

* **FreeRTOS Kernel** — MIT License
* **X-CUBE-AI (STMicroelectronics)** — ST AI Software License Agreement

---

## 👥 Contributors

| 이름                        | 역할                                    |
| ------------------------- | ------------------------------------- |
| **최성현 (SeongHyeon Choi)** | 시스템 설계, 센싱 모듈 설계(부), 데이터 수집 및 검증, LCD 모듈 설계 |
| **김서랑 (Seorang Kim)** | 시스템 설계, 센싱 모듈 설계(정), 모델 학습 및 임베딩 |
| **김태현 교수님 (Prof. Taehyeon Kim)** | 지도교수님 |

---

** RTES-Lab @ University of Seoul**


