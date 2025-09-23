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
#include "i2c.h"
#include "usart.h"
#include "usb_host.h"
#include "gpio.h"

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

SemaphoreHandle_t xBinarySemaphore;
extern UART_HandleTypeDef huart2;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
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
//void vUSBInitTask(void *pvParameters);
void vUSBReadTask(void *pvParameters);
static void vHandlerTask(void *pvParameters);
void DumpHexUART(uint8_t *buf, uint16_t len);

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
  MX_USB_HOST_Init();
  MX_GPIO_Init();
  MX_USART2_UART_Init();


  /* USER CODE BEGIN 2 */
  const char *boot = "[BOOT] UART ready\r\n";
  HAL_UART_Transmit(&huart2, (uint8_t*)boot, strlen(boot), 100);

  MX_I2C1_Init();
  lcd_init();


//  xTaskCreate(vUSBInitTask, "USB Task",  512,  NULL, 1, NULL);
  xTaskCreate(vUSBReadTask, "USBRead",  1024,  NULL, 2, NULL);
//  xTaskCreate(vLCDTask, "LCD Task", 512, NULL, 3, NULL);

  vTaskStartScheduler();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

	/* USER CODE BEGIN 3 */
//    MX_USB_HOST_Process();


  }

}
/* USER CODE END 3 */


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
  * @brief  USB init 태스크. 주기 10ms
  */
//void vUSBInitTask(void *pvParameters)
//{
//  MX_USB_HOST_Init();
//    for (;;)
//    {
//        MX_USB_HOST_Process();
//        vTaskDelay(pdMS_TO_TICKS(10));
//    }
//}

/**
  * @brief  USB 가속도계로부터 데이터를 읽고 출력하는 태스크. 주기 10ms
  */
void vUSBReadTask(void *pvParameters)
{
    AUDIO_HandleTypeDef *audio_handle;
    uint8_t *buf;
    char msg[64];

    static float sample_buffer[SAMPLES_TO_SAVE];

    int collected_samples = 0;
    static uint8_t isoc_submitted = 0;

//    while (Appli_state != APPLICATION_READY) // APPLICATION_READY 상태가 될때까지 대기
//    {
//        vPrintString("Waiting for USB ready...\r\n");
//        vTaskDelay(pdMS_TO_TICKS(500));
//    }

    for (;;) {
    	MX_USB_HOST_Process();
        audio_handle = (AUDIO_HandleTypeDef *)hUsbHostFS.pActiveClass->pData;

        if (!(audio_handle && audio_handle->microphone.supported)) {
//            taskYIELD();
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
                    // 다음 틱에서 DONE 될 때까지 기다림
                    taskYIELD();
                    continue;
                }

        USBH_URBStateTypeDef urb =
                    USBH_LL_GetURBState(&hUsbHostFS, audio_handle->microphone.Pipe);


        if (urb == USBH_URB_DONE) {
        	int frames_in_buf = audio_handle->microphone.frame_length / FRAME_SIZE; // 1ms 패킷 안에 들어있는 샘플 프레임 개수, 1 USB 프레임 길이 frame_length = 288, 1 오디오 FRAME_SIZE = 2(채널) * 3(24 bit)


			for (int i = 0; i < frames_in_buf; i += DOWNSAMPLE_FACTOR) // frames_in_buf는 결국 1ms에 들어온 48개의 오디오 프레임을 의미
			{
				int32_t sample_val = convert24bitToInt32(&buf[i * FRAME_SIZE]);
				float scaled_val = (float)sample_val * SCALE_FACTOR;

				if (collected_samples < SAMPLES_TO_SAVE) {
					 sample_buffer[collected_samples++] = scaled_val;
				}

				// ★ 2048개 꽉 찼을 때만 전송
				else{
					uint8_t hdr[2];
					hdr[0] = 0xAA;
					hdr[1] = 0xFF;

					HAL_UART_Transmit(&huart2, hdr, (uint16_t)sizeof(hdr), HAL_MAX_DELAY);

					HAL_UART_Transmit(&huart2,
									  (uint8_t*)sample_buffer,
									  (uint16_t)(SAMPLES_TO_SAVE * sizeof(float)),
									  HAL_MAX_DELAY);
					collected_samples = 0;
					sample_buffer[collected_samples++] = scaled_val;
				}
			}
            (void)USBH_IsocReceiveData(&hUsbHostFS,
                                       buf,
                                       audio_handle->microphone.frame_length,
                                       audio_handle->microphone.Pipe);

//				if (collected_samples >= SAMPLES_TO_SAVE) {
//					for (int i = 0; i < SAMPLES_TO_SAVE; i++) {
////                            	// 헤더 추가 부분
////                                uint8_t packet[6]; // 헤더 2 + int32 4
////                                packet[0] = 0xAA;
////                                packet[1] = 0x55;
////                                memcpy(&packet[2], &sample_val, sizeof(float));
//
//						HAL_UART_Transmit(&huart2, sample_buffer, SAMPLES_TO_SAVE * sizeof(float), HAL_MAX_DELAY); // 헤더 없는 버전
////						HAL_UART_Transmit(&huart2, packet, sizeof(packet), HAL_MAX_DELAY); // 헤더 있는 버전
//						collected_samples = 0;
//					}
//				}
		} //taskYIELD()
	}
}
//void vUSBReadTask(void *pvParameters)
//{
//    AUDIO_HandleTypeDef *audio_handle;
//    uint8_t *buf;
//    static int32_t sample_buffer[SAMPLES_TO_SAVE];
//    int collected = 0;
//
//    // USB 준비 대기
//    while (Appli_state != APPLICATION_READY) {
//        vTaskDelay(pdMS_TO_TICKS(50));
//    }
//
//    audio_handle = (AUDIO_HandleTypeDef *)hUsbHostFS.pActiveClass->pData;
//    if (!(audio_handle && audio_handle->microphone.supported)) {
//        vPrintString("Audio mic not supported.\r\n");
//        vTaskDelete(NULL);
//    }
//
//    buf = audio_handle->microphone.buf;
//    uint8_t pipe = audio_handle->microphone.Pipe;
//    uint16_t flen = audio_handle->microphone.frame_length; // 보통 288B/1ms
//    // 최초 제출
//    USBH_IsocReceiveData(&hUsbHostFS, buf, flen, pipe);
//
//    for (;;) {
//        USBH_URBStateTypeDef s = USBH_LL_GetURBState(&hUsbHostFS, pipe);
//        if (s == USBH_URB_DONE) {
//            // 1ms 분량 도착 → 처리
//            int frames_in_buf = flen / FRAME_SIZE; // FRAME_SIZE = 6B(24bit*2ch)
//            for (int i = 0; i < frames_in_buf; i += DOWNSAMPLE_FACTOR) {
//                if (collected < SAMPLES_TO_SAVE) {
//                    int32_t v = convert24bitToInt32(&buf[i * FRAME_SIZE]);
//                    sample_buffer[collected++] = v;
//                }
//                if (collected >= SAMPLES_TO_SAVE) {
//                    // 2048개 모이면 UART 전송
//                    for (int k = 0; k < SAMPLES_TO_SAVE; k++) {
//                        float fv = (float)sample_buffer[k] * SCALE_FACTOR;
//                        uint8_t packet[6] = {0xAA, 0x55, 0,0,0,0};
//                        memcpy(&packet[2], &fv, sizeof(float));
//                        HAL_UART_Transmit(&huart2, packet, sizeof(packet), HAL_MAX_DELAY);
//                    }
//                    collected = 0;
//                }
//            }
//            // 다음 프레임 즉시 재제출(지연 금지)
//            USBH_IsocReceiveData(&hUsbHostFS, buf, flen, pipe);
//        } else if (s == USBH_URB_NOTREADY || s == USBH_URB_IDLE) {
//            // 아직 도착 전: 잠깐 양보만
//            taskYIELD();
//        } else if (s == USBH_URB_ERROR || s == USBH_URB_STALL) {
//            // 에러 처리 후 재시도
//            USBH_IsocReceiveData(&hUsbHostFS, buf, flen, pipe);
//        }
//    }
//}


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

static void vHandlerTask(void *pvParameters){
  (void)pvParameters;
  for(;;){
    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
    vPrintString("Handler task - Processing event.\r\n");
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
