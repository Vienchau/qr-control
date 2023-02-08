/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "pid.h"
#include "utils.h"
#include "motor.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MOTOR_1 1
#define MOTOR_2 2
#define SAMPLING_TIME 0.005

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
#define SAMPLE_STRING "0000"
#define MAX_LEN_DATA 5

void SerialInit(void);
void SerialAcceptReceive(void);
void SerialWriteComm();

void MotorInit(void);
void MotorSetDuty(uint16_t nDuty, uint8_t channel);
void MotorSetDir(int8_t nDir, uint8_t channel);
void MotorSetRun();
void Motor1Fordward();
void Motor1Backward();
void Mortor2Fordward();
void Mortor2Backward();
void MotorGetPulse(uint32_t *nPulse, uint8_t motor);
void MotorMovePos(PROFILE_t *tProfile, PID_CONTROL_t *tPIDControl, uint8_t motor);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
char dataBuffer[MAX_LEN_DATA];
uint8_t counter_timer = 0;
uint8_t counter_timer_2 = 0;
uint32_t nPulse_counter;

uint32_t g_nActPulse_1;
uint32_t g_nActPulse_2;

uint32_t g_nCmdPulse;
float g_dCmdVel;

uint32_t nPulse1, nPulse1_test;
uint32_t nPulse2, nPulse2_test;

PID_CONTROL_t tPID_1, tPID_2;
PROFILE_t tProfile_1, tProfile_2;

uint8_t tProcess;

uint32_t g_nActPulse_1, g_nActPulse_2;
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
  /* USER CODE BEGIN 1 */

  // Go ahead
  //  MotorTrapzoidalInit(&tProfile_1, 1000, 90, 45);
  //  MotorTrapzoidalInit(&tProfile_2, 1000, 90, 45);

  // Rotate left
  MotorTrapzoidalInit(&tProfile_1, 360, 60, 10);
  	MotorTrapzoidalInit(&tProfile_2, 360, 60, 10);
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM8_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  SerialInit();
  MotorInit();

  __HAL_TIM_SetCounter(&htim8, 32768);
  __HAL_TIM_SetCounter(&htim1, 32768);
  tProcess = RUN_TEST;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  //      MotorSetDuty(500, MOTOR_1);
  //      MotorSetDuty(500, MOTOR_2);
  //
  //  MotorSetRun();
  while (1)
  {

    //	  MotorSetDuty(200, MOTOR_2);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void SerialInit(void)
{
  HAL_UART_Receive_IT(&huart1, (uint8_t *)dataBuffer, MAX_LEN_DATA);
}

// receive data
void SerialAcceptReceive(void)
{
  HAL_UART_Receive_IT(&huart1, (uint8_t *)dataBuffer, MAX_LEN_DATA);
}

// interupt uart RX
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == huart1.Instance)
  {
    SerialAcceptReceive();
  }
}

// set motor direction

void SerialWriteComm()
{
  char *pBuff;
  pBuff = (char *)malloc(MAX_LEN_DATA);
  strncpy(pBuff, dataBuffer, MAX_LEN_DATA);
  HAL_UART_Transmit(&huart1, (uint8_t *)pBuff, MAX_LEN_DATA, 1000);
  free(pBuff);
}

// set (-) pwm
void MotorSetRun()
{
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
}

void Motor1Forward()
{
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);
}

void Motor1Backward()
{
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET);
}

void Motor2Forward()
{
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
}

void Motor2Backward()
{
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
}

void MotorSetDuty(uint16_t nDuty, uint8_t channel)
{
  if (channel == MOTOR_1)
  {
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, nDuty);
  }
  else if (channel == MOTOR_2)
  {
    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, nDuty);
  }
}

// init params for timer interrupt...
void MotorInit(void)
{
  HAL_TIM_Base_Start_IT(&htim2);

  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);

  HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_2);

  HAL_TIM_Encoder_Start(&htim8, TIM_CHANNEL_1);
  HAL_TIM_Encoder_Start(&htim8, TIM_CHANNEL_2);
  PIDInit(&tPID_1, 3.5, 1.5, 0.2);
  PIDInit(&tPID_2, 3.5, 1.5, 0.2);
  //  Motor1Fordward();
  //  Motor1Forward();
  //  Motor2Forward();

  MotorSetDuty(0, MOTOR_1);
  MotorSetDuty(0, MOTOR_2);
}

void MotorGetPulse(uint32_t *nPulse, uint8_t motor)
{
  if (motor == MOTOR_1)
  {
    *nPulse = __HAL_TIM_GetCounter(&htim8);
  }
  else if (motor == MOTOR_2)
  {
    *nPulse = __HAL_TIM_GetCounter(&htim1);
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

  if (htim->Instance == htim2.Instance)
  {
    switch (tProcess)
    {
    case NONE:
      break;
    case RUN_TEST:
      MotorMovePos(&tProfile_1, &tPID_1, MOTOR_1);
            MotorMovePos(&tProfile_2, &tPID_2, MOTOR_2);
    }
    //    MotorGetPulse(&nPulse1_test, MOTOR_1);
    //    if (nPulse1_test < 10752)
    //    {
    //      MotorSetDuty(500, MOTOR_1);
    //    }
    //    else
    //    {
    //      MotorSetDuty(0, MOTOR_1);
    //    }
    //
    //    MotorGetPulse(&nPulse2_test, MOTOR_2);
    ////	  nPulse2_test = TIM8 -> CNT;
    //    if (nPulse2_test < 10752)
    //    {
    //      MotorSetDuty(500, MOTOR_2);
    //    }
    //    else
    //    {
    //      MotorSetDuty(0, MOTOR_2);
    //    }
  }
}

void MotorMovePos(PROFILE_t *tProfile, PID_CONTROL_t *tPIDControl, uint8_t motor)
{
  int32_t g_nDutyCycle;
  uint32_t g_nActPulse;
  if (motor == MOTOR_1)
  {
	MotorGetPulse(&nPulse1, motor); // get encoder counter

    g_nActPulse_1 = nPulse1 - 32768;
    g_nActPulse = g_nActPulse_1;
  }
  else
  {
    MotorGetPulse(&nPulse2, motor); // get encoder counter
    g_nActPulse_2 = nPulse2 - 32768;
    g_nActPulse = g_nActPulse_2;
  }

  float dPosTemp = 0;

  // Profile trapezoidal Speed
  if (tProfile->nTime <= tProfile->dMidStep1)
  {
    dPosTemp = (int32_t)(tProfile->dA1 * tProfile->nTime * tProfile->nTime);
    g_dCmdVel = 2 * tProfile->dA1 * tProfile->nTime;
  }
  else if (tProfile->nTime <= tProfile->dMidStep2)
  {
    dPosTemp = (int32_t)(tProfile->dA2 * tProfile->nTime + tProfile->dB2);
    g_dCmdVel = tProfile->dA2;
  }
  else if (tProfile->nTime <= tProfile->dMidStep3)
  {
    dPosTemp = (int32_t)(tProfile->dA3 * tProfile->nTime * tProfile->nTime + tProfile->dB3 * tProfile->nTime + tProfile->dC3);
    g_dCmdVel = 2 * tProfile->dA3 * tProfile->nTime + tProfile->dB3;
  }
  else
  {
    dPosTemp = tProfile->dPosMax;
  }

  // Control PID
  g_nCmdPulse = ConvertDegToPulse(dPosTemp);
  g_nDutyCycle = (int16_t)PIDCompute(tPIDControl, g_nCmdPulse, g_nActPulse, SAMPLING_TIME);
  if (g_nDutyCycle >= 0)
  {
    if (motor == MOTOR_1)
    {
      Motor1Forward();
    }
    else
    {
      Motor2Forward();
    }

    MotorSetDuty(abs(g_nDutyCycle), motor);
  }
  else if (g_nDutyCycle < 0)
  {

    if (motor == MOTOR_1)
    {
      Motor1Backward();
    }
    else
    {
      Motor2Backward();
    }

    MotorSetDuty(abs(g_nDutyCycle), motor);
  }

  if (tProfile->nTime > tProfile->dMidStep3)
  {
    __HAL_TIM_SetCounter(&htim4, 32768);
    dPosTemp = 0;
    g_nDutyCycle = 0;
    g_dCmdVel = 0;
    tProfile->nTime = 0;
    tProcess = NONE;
    MotorSetDuty(abs(g_nDutyCycle), motor);
  }

  tProfile->nTime += SAMPLING_TIME;
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
