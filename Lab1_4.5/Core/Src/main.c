/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
void display_led(int led_state[]){
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,led_state[0]);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,led_state[1]);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,led_state[2]);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,led_state[3]);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,led_state[4]);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,led_state[5]);
}
void display_7segment(int number1,int number2){
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,((number1>>0)&0x01));
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,((number1>>1)&0x01));
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,((number1>>2)&0x01));
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,((number1>>3)&0x01));
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,((number1>>4)&0x01));
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,((number1>>5)&0x01));
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,((number1>>6)&0x01));
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,((number2>>0)&0x01));
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,((number2>>1)&0x01));
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,((number2>>2)&0x01));
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,((number2>>3)&0x01));
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,((number2>>4)&0x01));
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,((number2>>5)&0x01));
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,((number2>>6)&0x01));
}
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int led_state[6] = {1,1,1,1,1,1};
  int led_1 = 0,led_2 = 6;
  int time = 0;
  int clock_1 = 5,clock_2 = 3;
  int last_clock_1 = clock_1,last_clock_2 = clock_2;
  int arr[10] = {
		  0x00C0,  //0
		  0x00F9,  //1
		  0x00A4,  //2
		  0x00B0,  //3
		  0x0099,  //4
		  0x0092,  //5
		  0x0082,  //6
		  0x00F8,  //7
		  0x0080,  //8
		  0x0090,  //9
  };
  while (1)
  {
	  if(clock_1 == 0){
		  if(last_clock_1 == 3) clock_1 = 2;
		  else if(last_clock_1 == 2) clock_1 = 5;
		  else clock_1 = 3;
		  last_clock_1 = clock_1;
	  }
	  if(clock_2 == 0){
		  if(last_clock_2 == 3) clock_2 = 2;
		  else if(last_clock_2 == 2) clock_2 = 5;
		  else clock_2 = 3;
		  last_clock_2 = clock_2;
	  }
	  if(time == 10){
		  time = 0;
	  }
	  if(time < 3){
		  led_1 = 0;
		  led_2 = 5;
	  }
	  else if(time < 5){
		  led_1 = 0;
		  led_2 = 4;
	  }
	  else if(time < 8){
		  led_1 = 2;
		  led_2 = 3;
	  }
	  else if(time < 10){
		  led_1 = 1;
		  led_2 = 3;
	  }
	  led_state[led_1] = 0;
	  led_state[led_2] = 0;
	  display_led(led_state);
	  display_7segment(arr[clock_1],arr[clock_2]);
	  led_state[led_1] = 1;
	  led_state[led_2] = 1;
	  time+=1;
	  clock_1-=1;
	  clock_2-=1;
	  HAL_Delay(1000);
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA1 PA2 PA3 PA4
                           PA5 PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB10
                           PB11 PB12 PB13 PB3
                           PB4 PB5 PB6 PB7
                           PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
