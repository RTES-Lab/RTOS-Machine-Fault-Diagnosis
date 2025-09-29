/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "crc.h"
#include "i2c.h"
#include "usart.h"
#include "usb_host.h"
#include "gpio.h"
#include "app_x-cube-ai.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "usbh_audio.h"
#include "i2c_lcd.h"

#include "ai_datatypes_defines.h"
#include "ai_platform.h"
#include "frfconv.h"
#include "frfconv_data.h"
#include "app_x-cube-ai.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
// 진동 데이터 센싱 관련 상수 정의
#define SAMPLES_TO_SAVE 2048
#define CHANNELS 2
#define BYTES_PER_SAMPLE 3
#define FRAME_SIZE (CHANNELS * BYTES_PER_SAMPLE)
#define SCALE_FACTOR (0.10197f / (32550.0f * 1.02575f))
#define DOWNSAMPLE_FACTOR 3
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* 전역/외부 심볼 */
extern ApplicationTypeDef Appli_state;
extern char USBHPath[4];
extern USBH_HandleTypeDef hUsbHostFS;
// 데이터 수집 완료를 알리기 위한 바이너리 세마포어 핸들
SemaphoreHandle_t xDataReadySemaphore;
// USBReadTask에서 수집하고 modelTask에서 사용할 공유 데이터 버퍼
static float sample_buffer[SAMPLES_TO_SAVE];

extern UART_HandleTypeDef huart2;

static ai_u8 activations[AI_FRFCONV_DATA_ACTIVATIONS_SIZE];
static ai_float in_data[AI_FRFCONV_IN_1_SIZE];
static ai_float out_data[AI_FRFCONV_OUT_1_SIZE];

static ai_buffer *ai_input;
static ai_buffer *ai_output;
/* USER CODE END PV */

/* Private function prototypes ---------------------------m--------------------*/
void SystemClock_Config(void);
void MX_USB_HOST_Process(void);

/* USER CODE BEGIN PFP */
/* Cube가 I2C를 생성했다면 i2c.h가 생기며 MX_I2C1_Init도 생성됩니다.
   나중에 LCD를 쓸 때 main에서 MX_I2C1_Init()을 호출할 계획이면
   i2c.h를 include하고 아래 프로토타입을 추가하세요. (지금은 호출하지 않음)
   // #include "i2c.h"
   // static void MX_I2C1_Init(void);
*/

int32_t convert24bitToInt32(uint8_t *p);

/* 프린트/태스크/헬퍼 함수 프로토타입 */
void SystemClock_Config(void);
void vPrintString(const char *str);
void vUSBReadTask(void *pvParameters);
void DumpHexUART(uint8_t *buf, uint16_t len);
void modelTask(void *pvParameters);
void vLCDTask(void *pvParameters);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER 영역(전역 함수 구현 전 준비 공간) */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
  /* (필요 시 프리런 초기화 코드) */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* 현재 구성 유지: HSI → PLL → SYSCLK=84MHz, PLLQ=7로 48MHz 확보 */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_CRC_Init();
  /* USER CODE BEGIN 2 */
  const char *boot = "[BOOT] UART ready\r\n";
  HAL_UART_Transmit(&huart2, (uint8_t*)boot, strlen(boot), 100);

//  MX_I2C1_Init();
//  lcd_init();

  xDataReadySemaphore = xSemaphoreCreateBinary();
  if (xDataReadySemaphore == NULL) {
      vPrintString("[ERROR] Failed to create data ready semaphore!\r\n");
      while(1); // 시스템 정지
  }

  xTaskCreate(vUSBReadTask, "USBRead",  1024,  NULL, 1, NULL);
//  xTaskCreate(vLCDTask, "LCD Task", 512, NULL, 3, NULL);
  xTaskCreate(modelTask, "model Task", 1024*2, NULL, 2, NULL);

  // HAL_Delay 등 기능은 무조건 RTOS 시작 후 실행되게 하기 위해 초기화 늦게 수행
  MX_USB_HOST_Init();

  vTaskStartScheduler();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
  }

}
  /* USER CODE END 3 */

/**
  * @brief System Clock Configuration
  * @retval None
  */
//void SystemClock_Config(void)
//{
//  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
//  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
//
//  /** Configure the main internal regulator output voltage
//  */
//  __HAL_RCC_PWR_CLK_ENABLE();
//  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
//
//  /** Initializes the RCC Oscillators according to the specified parameters
//  * in the RCC_OscInitTypeDef structure.
//  */
//  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
//  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
//  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
//  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
//  RCC_OscInitStruct.PLL.PLLM = 4;
//  RCC_OscInitStruct.PLL.PLLN = 168;
//  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
//  RCC_OscInitStruct.PLL.PLLQ = 7;
//  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Initializes the CPU, AHB and APB buses clocks
//  */
//  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
//                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
//  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
//  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
//  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
//  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
//
//  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
//  {
//    Error_Handler();
//  }
//}

/* USER CODE BEGIN 4 */
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }

}

/* ===== 사용자 함수 구현부 ===== */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
  (void)xTask; (void)pcTaskName;
  taskDISABLE_INTERRUPTS();
  for(;;) { }
}

void vPrintString(const char *str) {
  HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}


/**
  * @brief  받은 진동 데이터 터미널에 출력하는 함수 (디버깅용)
  */
void DumpHexUART(uint8_t *buf, uint16_t len)
{
    char str[80];
    for (uint16_t i = 0; i < len; i += 16)
    {
        int chunk_len = (len - i > 16) ? 16 : (len - i);
        int offset = sprintf(str, "%04X: ", i);
        for (int j = 0; j < chunk_len; j++)
        {
            offset += sprintf(&str[offset], "%02X ", buf[i + j]);
        }
        sprintf(&str[offset], "\r\n");
    }
}

/**
  * @brief  USB 가속도계로부터 데이터를 읽고 출력하는 태스크. 주기 10ms
  */
void vUSBReadTask(void *pvParameters)
{
    AUDIO_HandleTypeDef *audio_handle;
    uint8_t *buf;

    int collected_samples = 0;
    static uint8_t isoc_submitted = 0;

    for (;;) {
       MX_USB_HOST_Process();
        audio_handle = (AUDIO_HandleTypeDef *)hUsbHostFS.pActiveClass->pData;

        if (!(audio_handle && audio_handle->microphone.supported)) {
        	vTaskDelay(pdMS_TO_TICKS(1));
        	continue;
        }

        buf = audio_handle->microphone.buf;

        if (!isoc_submitted) {
            if (USBH_IsocReceiveData(&hUsbHostFS,
                           buf,
                           audio_handle->microphone.frame_length,
                           audio_handle->microphone.Pipe) == USBH_OK) {
               isoc_submitted = 1;
            }
            vTaskDelay(pdMS_TO_TICKS(1));
            continue;
        }

        USBH_URBStateTypeDef urb =
                    USBH_LL_GetURBState(&hUsbHostFS, audio_handle->microphone.Pipe);

        if (urb == USBH_URB_DONE) {
            int frames_in_buf = audio_handle->microphone.frame_length / FRAME_SIZE;

            for (int i = 0; i < frames_in_buf; i += DOWNSAMPLE_FACTOR){
               if (collected_samples < SAMPLES_TO_SAVE) {
                    int32_t sample_val = convert24bitToInt32(&buf[i * FRAME_SIZE]);
                    float scaled_val = (float)sample_val * SCALE_FACTOR;
                    sample_buffer[collected_samples++] = scaled_val;
               }
               // 2048개 샘플이 모두 모였을 때
               if (collected_samples >= SAMPLES_TO_SAVE){
                   vPrintString("[USBTask] Sampled Data:\r\n");
                    char buf[128];
                    // 처음 3개
                    snprintf(buf, sizeof(buf), "  Start: %.4f, %.4f, %.4f\r\n", sample_buffer[0], sample_buffer[1], sample_buffer[2]);
                    vPrintString(buf);
                    // 중간 3개
                    snprintf(buf, sizeof(buf), "  Mid:   %.4f, %.4f, %.4f\r\n", sample_buffer[1023], sample_buffer[1024], sample_buffer[1025]);
                    vPrintString(buf);
                    // 마지막 3개
                    snprintf(buf, sizeof(buf), "  End:   %.4f, %.4f, %.4f\r\n", sample_buffer[2045], sample_buffer[2046], sample_buffer[2047]);
                    vPrintString(buf);
                  vPrintString("Data collected. Giving semaphore to model task.\r\n");
                  xSemaphoreGive(xDataReadySemaphore);
                  collected_samples = 0;
                  break;
               }
            }
            // 다음 데이터 패킷을 받기 위해 수신 요청을 다시 제출
            (void)USBH_IsocReceiveData(&hUsbHostFS,
                                       buf,
                                       audio_handle->microphone.frame_length,
                                       audio_handle->microphone.Pipe);
        	}
        else{
//        	vTaskDelay(pdMS_TO_TICKS(1));
        }
   }
}


// LCD Task
void vLCDTask(void *pvParameters)
{
    for (;;)
    {
        lcd_clear();

        lcd_put_cursor(0, 0);
        lcd_send_string("Hello World!");

        lcd_put_cursor(1, 0);
        lcd_send_string("From STM32Nucleo");

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

// Model task
void modelTask(void *pvParameters){

    ai_handle frfconv = AI_HANDLE_NULL;
    ai_error err;
    ai_network_report report;

    const ai_handle acts[] = { activations };
    err = ai_frfconv_create_and_init(&frfconv, acts, NULL);
    if (err.type != AI_ERROR_NONE) {
       vPrintString("ai init_and_create error\n");
    }

    if (ai_frfconv_get_report(frfconv, &report) != true) {
       vPrintString("ai get report error\n");
    }

    for (;;){
       if (xSemaphoreTake(xDataReadySemaphore, portMAX_DELAY) == pdTRUE) {
          vPrintString("Semaphore received. Model task is running...\r\n");
          memcpy(in_data, sample_buffer, sizeof(float) * SAMPLES_TO_SAVE);

          vPrintString("[ModelTask] Copied Data:\r\n");
          char buf[128];
          // 처음 3개
          snprintf(buf, sizeof(buf), "  Start: %.4f, %.4f, %.4f\r\n", in_data[0], in_data[1], in_data[2]);
          vPrintString(buf);
          // 중간 3개
          snprintf(buf, sizeof(buf), "  Mid:   %.4f, %.4f, %.4f\r\n", in_data[1023], in_data[1024], in_data[1025]);
          vPrintString(buf);
          // 마지막 3개
          snprintf(buf, sizeof(buf), "  End:   %.4f, %.4f, %.4f\r\n", in_data[2045], in_data[2046], in_data[2047]);
          vPrintString(buf);

            ai_i32 n_batch;

            ai_input = &report.inputs[0];
            ai_output = &report.outputs[0];

//          ai_input = ai_frfconv_inputs_get(frfconv, NULL);
//          ai_output = ai_frfconv_outputs_get(frfconv, NULL);

            ai_input[0].data = AI_HANDLE_PTR(in_data);
            ai_output[0].data = AI_HANDLE_PTR(out_data);

            n_batch = ai_frfconv_run(frfconv, &ai_input[0], &ai_output[0]);
            if (n_batch != 1) {
               ai_error err = ai_frfconv_get_error(frfconv);
               int len = snprintf(buf, sizeof(buf), "ai run error %d, %d\r\n", err.type, err.code);
               HAL_UART_Transmit(&huart2, (uint8_t*)buf, len, HAL_MAX_DELAY);
                }

            int len = snprintf(buf, sizeof(buf), "\r\nInference output: ");
            HAL_UART_Transmit(&huart2, (uint8_t*)buf, len, HAL_MAX_DELAY);

            for (int i = 0; i < AI_FRFCONV_OUT_1_SIZE; i++) {
                float y_val = (float)out_data[i];
                len = snprintf(buf, sizeof(buf), "%.2f,", y_val);
                HAL_UART_Transmit(&huart2, (uint8_t*)buf, len, HAL_MAX_DELAY);
            }
             vPrintString("\r\n");
       }
    }

}


void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                   StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize ) {
  static StaticTask_t xIdleTaskTCB;
  static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

  *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
  *ppxIdleTaskStackBuffer = uxIdleTaskStack;
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                    StackType_t **ppxTimerTaskStackBuffer,
                                    uint32_t *pulTimerTaskStackSize ) {
  static StaticTask_t xTimerTaskTCB;
  static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

  *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;
  *ppxTimerTaskStackBuffer = uxTimerTaskStack;
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}


/**
  * @brief  24bit 수를 32bit 정수로 변환하는 함수
  */
int32_t convert24bitToInt32(uint8_t *p) {
    int32_t val = p[0] | (p[1] << 8) | (p[2] << 16);
    if (val & 0x800000) { // 부호 확장
        val |= 0xFF000000;
    }
    return val;
}

void vApplicationMallocFailedHook(void) {
    while(1);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
