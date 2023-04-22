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
#define SAMPLE_STRING "0360,0045,0045,1,0"
#define ARRAY_CHECKER "1111,1111,1111,1,1"
#define MAX_LEN_DATA 18
void SerialInit(void);
void SerialAcceptReceive(void);


void MotorInit(void);
void MotorSetDuty(uint16_t nDuty, uint8_t channel);
void MotorSetDir(int8_t nDir, uint8_t channel);
void MotorSetRun();
void MotorGetPulse(uint32_t *nPulse, uint8_t motor);
void MotorMovePos(PROFILE_t *tProfile, PID_CONTROL_t *tPIDControl1, PID_CONTROL_t *tPIDControl2, uint8_t dir1, uint8_t dir2);

#define GO_AHEAD 1
#define GO_BACK 0
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
PROFILE_t tProfile;

uint8_t tProcess;
ArrData_t arrData1;
uint32_t g_nActPulse_1, g_nActPulse_2;

uint8_t dir1, dir2;
char statusOK[] = "OK\r\n";
uint8_t flag1 = 0;
uint8_t flag2 = 0;

uint32_t deg1 = 0, deg2 = 0;
int32_t dutyCycle_global_1 = 0,  dutyCycle_global_2 = 0;
// void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
//{
//    HAL_UART_Transmit_IT(&huart2, data, sizeof(data));
// }
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
  //  MotorTrapzoidalInit(&tProfile_1, 360, 60, 10, BACK);
  //  MotorTrapzoidalInit(&tProfile_2, 360, 60, 10, BACK);
  // char hehe[] = "hello";
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
  MX_TIM5_Init();
  MX_TIM1_Init();
  MX_USART2_UART_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  SerialInit();
  MotorInit();
  MotorSetRun();

  tProcess = NONE;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  __HAL_TIM_SetCounter(&htim3, 32768);
  __HAL_TIM_SetCounter(&htim4, 32768);
  while (1)
  {
//	  	MotorGetPulse(&nPulse1, MOTOR_1); // get encoder counter
//	   	MotorGetPulse(&nPulse2, MOTOR_2); // get encoder counter
//	   	Motor1Forward();
//	   	Motor2Forward();
//	  	MotorSetDuty(300, MOTOR_1);
//	  	MotorSetDuty(300, MOTOR_2);
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

/* USER CODE BEGIN 4 */
void SerialInit(void)
{
  HAL_UART_Receive_IT(&huart2, (uint8_t *)dataBuffer, MAX_LEN_DATA);
}

// receive data
void SerialAcceptReceive(void)
{
  HAL_UART_Receive_IT(&huart2, (uint8_t *)dataBuffer, MAX_LEN_DATA);
}

// interupt uart RX
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == huart2.Instance)
  {
//    	MotorSetDuty(0, MOTOR_2);
//    	MotorSetDuty(0, MOTOR_1);
    	__HAL_TIM_SetCounter(&htim3, 32768);
	    __HAL_TIM_SetCounter(&htim4, 32768);
	    tProcess = NONE;
	    PIDReset(&tPID_1);
	    PIDReset(&tPID_2);


	    if(!strcmp(dataBuffer, ARRAY_CHECKER)){
	    	HAL_UART_Transmit(&huart2, (uint8_t *)statusOK, sizeof(statusOK), 1000);
	    }
	    else {
	    	 HAL_UART_Transmit(&huart2, (uint8_t *)dataBuffer, MAX_LEN_DATA, 1000);
	    	    arrData1 = ArrProcess(dataBuffer);
	    	    MotorTrapzoidalInit(&tProfile, arrData1.pos1, arrData1.vel1, arrData1.acc1);
	    	    dir1 = arrData1.dir1;
	    	    dir2 = arrData1.dir2;
	    	    tProcess = RUN_TEST;

	    }
	    SerialAcceptReceive();
  }
}

// set motor direction

// set (-) pwm
void MotorSetRun()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET);
}

void Motor1Forward()
{
	 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
}

void Motor1Backward()
{
	 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
}

void Motor2Forward()
{
	 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
}

void Motor2Backward()
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
}

void MotorSetDuty(uint16_t nDuty, uint8_t channel)
{
  if (channel == MOTOR_1)
  {
	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,nDuty);
  }
  else if (channel == MOTOR_2)
  {
	  __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1,nDuty);
  }
}

// init params for timer interrupt...
void MotorInit(void)
{
  HAL_TIM_Base_Start_IT(&htim2);


  HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);

  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);

  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_2);

  HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_1);
  HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_2);

  PIDInit(&tPID_1, 3.5, 1.5, 0.2);
  PIDInit(&tPID_2, 3.5, 1.5, 0.2);

  MotorSetDuty(0, MOTOR_1);
  MotorSetDuty(0, MOTOR_2);

}

void MotorGetPulse(uint32_t *nPulse, uint8_t motor)
{
  if (motor == MOTOR_1)
  {
    *nPulse = __HAL_TIM_GetCounter(&htim4);
  }
  else if (motor == MOTOR_2)
  {
    *nPulse = __HAL_TIM_GetCounter(&htim3);
  }
}

/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

  if (htim->Instance == htim2.Instance)
  {
    switch (tProcess)
    {
    case NONE:
    	break;
    case RUN_TEST:
    	MotorSetRun();
    	MotorMovePos(&tProfile, &tPID_1, &tPID_2, dir1, dir2);
    }
  }
}

void MotorMovePos(PROFILE_t *tProfile, PID_CONTROL_t *tPIDControl1, PID_CONTROL_t *tPIDControl2, uint8_t dir1, uint8_t dir2)
{
  int32_t g_nDutyCycle_1, g_nDutyCycle_2;
  uint32_t g_nActPulse_1_tmp, g_nActPulse_2_tmp;

  MotorGetPulse(&nPulse1, MOTOR_1); // get encoder counter
  MotorGetPulse(&nPulse2, MOTOR_2); // get encoder counter
  if (dir1 == HEAD)
  {
	  if((nPulse1 < 32768) && (tProfile->nTime < 0.5)){

		  nPulse1 = 32768;
	  }
    g_nActPulse_1 = nPulse1 - 32768;
  }
  else
  {
	  if((nPulse1 > 32768) && (tProfile->nTime < 0.5)){
		  nPulse1 = 32768;
	  }
    g_nActPulse_1 = 32768 - nPulse1;
  }

  if (dir2 == HEAD)
  {
	  if((nPulse2 < 32768) && (tProfile->nTime < 0.5)){
		  nPulse2 = 32768;
	  }
	  g_nActPulse_2 = nPulse2 - 32768;
  }
  else
  {
	  if((nPulse2 > 32768) && (tProfile->nTime < 0.5)){
		  nPulse2 = 32768;
	  }
    g_nActPulse_2 = 32768 - nPulse2;
  }

  g_nActPulse_1_tmp = g_nActPulse_1;
  g_nActPulse_2_tmp = g_nActPulse_2;





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

  g_nDutyCycle_1 = (int16_t)PIDCompute(tPIDControl1, g_nCmdPulse, g_nActPulse_1_tmp, SAMPLING_TIME);
  g_nDutyCycle_2 = (int16_t)(PIDCompute(tPIDControl2, g_nCmdPulse, g_nActPulse_2_tmp, SAMPLING_TIME));

  dutyCycle_global_1 = g_nDutyCycle_1;
  dutyCycle_global_2 = g_nDutyCycle_2;

  if (g_nDutyCycle_1 >= 0)
  {
    if (dir1 == HEAD)
    {
    	Motor1Forward();
    }
    else
    {
    	Motor1Backward();
    }
  }
  else if (g_nDutyCycle_1 < 0)
  {
    if (dir1 == HEAD)
    {
    	Motor1Backward();
    }
    else
    {
    	Motor1Forward();
    }
  }

  if (g_nDutyCycle_2 >= 0)
  {
    if (dir2 == HEAD)
    {
    	Motor2Forward();
    }
    else
    {
    	Motor2Backward();
    }
  }
  else if (g_nDutyCycle_2 < 0)
  {

    if (dir2 == HEAD)
    {
    	Motor2Backward();
    }
    else
    {
    	Motor2Forward();

    }
  }
  MotorSetDuty(abs(g_nDutyCycle_1), MOTOR_1);
  MotorSetDuty(abs(g_nDutyCycle_2), MOTOR_2);

  if (tProfile->nTime > tProfile->dMidStep3)
  {
    __HAL_TIM_SetCounter(&htim4, 32768);
    __HAL_TIM_SetCounter(&htim3, 32768);
    dPosTemp = 0;
    g_nDutyCycle_1 = 0;
    g_nDutyCycle_2 = 0;
    g_dCmdVel = 0;
    tProfile->nTime = 0;
    tProcess = NONE;
    MotorSetDuty(0, MOTOR_1);
    MotorSetDuty(0, MOTOR_2);
    PIDReset(&tPID_2);
    PIDReset(&tPID_1);
    HAL_UART_Transmit(&huart2, (uint8_t *)statusOK, sizeof(statusOK), 1000);
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

#ifdef  USE_FULL_ASSERT
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
