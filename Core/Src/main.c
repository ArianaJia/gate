/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "can.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bms_globals.h"
#include "atk_mw1278d_uart.h"
#include "atk_mw1278d.h"
#include "demo.h"
#include "delay.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t CAN_TxData2[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 };
uint8_t* rx_data;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
//int Voltage[6][23] = {0,};
//int Temperature[6][8] = {0,};
//
//int Highest_Voltage = 0;
//int Lowest_Voltage = 0;
//int Highest_Temperature = 0;
//int Lowest_Temperature = 0;
//int Asking_Voltage = 0;
//int Asking_I = 0;
//int Sum_Voltage = 0;
//int Sum_I = 0;
//int Charging_Voltage = 0;
//int IMD = 1;
//int Air1 = 0;
//int Air2 = 0;
//int Air3 = 0;
//int SOC = 0;
//int Battery_State = 0;
//int Charging_Signal = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
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
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_CAN_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8, GPIO_PIN_RESET);
  HAL_CAN_Start(&hcan);   //����can
  HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING); //����FIFO0�ж�
  CAN_Filter_Config();    //����CAN�˲���
  for(int i=0;i<=5;i++)
  {
	  for(int j=0;j<=22;j++)
	  {
		  Voltage[i][j]=i;
	  }
  }
  for(int i=0;i<=5;i++)
  {
	  for(int j=0;j<=7;j++)
	  {
		  Temperature[i][j]=i*2;
	  }
  }
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5, GPIO_PIN_SET);
  delay_init(72);                     /* ��ʱ��ʼ�� */
  HAL_Delay(50);
  demo_run();                         /* ����ʾ������ */
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8, GPIO_PIN_RESET);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//  HAL_UART_Transmit_IT(&huart3, (uint8_t*) "Start", 5);
//  char buff[30];
  init_bms_globals();

  while (1)
  {
//	  User_CAN_Send_sq(0x01,CAN_TxData2);
//	  HAL_UART_Transmit(&huart2, (uint8_t*) "DingZhen", 8, 10000);
//	  HAL_UART_Transmit_IT(&huart2, (uint8_t*) "DingZhen", 8);
	  HMI_set_V(Highest_Voltage,Lowest_Voltage,Asking_Voltage,Sum_Voltage,Charging_Voltage);
//	  atk_mw1278d_uart_printf("HV:%d\r\n",Highest_Voltage);
//	  atk_mw1278d_uart_printf("LV:%d\r\n",Lowest_Voltage);
//	  atk_mw1278d_uart_printf("Sum_V:%d\r\n",Sum_Voltage);
//
	  HMI_set_I(Asking_I,(int)(((float)Sum_I-10000.0)*2.4/10));
//	  atk_mw1278d_uart_printf("Sum_I:%d\r\n",(int)(((float)Sum_I-10000.0)*2.4/10));

	  HMI_set_T(Highest_Temperature,Lowest_Temperature);
//	  atk_mw1278d_uart_printf("HT:%d\r\n",Highest_Temperature);
//	  atk_mw1278d_uart_printf("LT:%d\r\n",Lowest_Temperature);

	  HMI_set_State(IMD,Air1,Air2,Air3,SOC,Battery_State);
//	  atk_mw1278d_uart_printf("IMD:%d\r\n",IMD);
//	  atk_mw1278d_uart_printf("AirP:%d\r\n",Air1);
//	  atk_mw1278d_uart_printf("Air-:%d\r\n",Air2);
//	  atk_mw1278d_uart_printf("Air+:%d\r\n",Air3);
//	  atk_mw1278d_uart_printf("SOC:%d\r\n",SOC);
//	  atk_mw1278d_uart_printf("BS:%d\r\n",Battery_State);
//
//	  atk_mw1278d_uart_printf("Acc_x:%d\r\n",Acc_x);
//	  atk_mw1278d_uart_printf("Acc_y:%d\r\n",Acc_y);
//	  atk_mw1278d_uart_printf("Velocity:%d\r\n",Velocity);

//	  HMI_set_A(Velocity,Acc_x,Acc_y);
// Voltage[0][0]=3812;

	  for(int i=0;i<=5;i++)
	  {
		  for(int j=0;j<=22;j++)
		  {
			  HMI_set_Voltage(i+1,j+1,Voltage[i][j]);
			  //sprintf(buff, "%dmV ", Voltage[i][j]);
			  //HAL_UART_Transmit(&huart3, (uint8_t*) buff, strlen(buff), HAL_MAX_DELAY);
			  //HAL_UART_Transmit_IT(&huart3, (uint8_t*) buff, st  rlen(buff));
		  }
		   HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_4);
	  }
//	  HAL_UART_Transmit_IT(&huart3, (uint8_t*) "\r\n", 2);
	  for(int i=0;i<=5;i++)
	  {
		  for(int j=0;j<=7;j++)
		  {
			  Temperature[0][0]=20;
			  HMI_set_Temperature(i+1,j+1,Temperature[i][j]);
			  //sprintf(buff, "%doC ", Temperature[i][j]);
			  //HAL_UART_Transmit(&huart3, (uint8_t*) buff, strlen(buff), HAL_MAX_DELAY);
			  //HAL_UART_Transmit_IT(&huart3, (uint8_t*) buff, strlen(buff));
		  }
		   HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
	  }
//	  HAL_UART_Transmit_IT(&huart3, (uint8_t*) "\r\n", 2);-
//	  atk_mw1278d_uart_printf("\r\n");
//	  atk_mw1278d_uart_printf("\r\n");
//	  HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_4);
//	  HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
	  rx_data = atk_mw1278d_uart_rx_get_frame();
	  if(rx_data != NULL){
//		  atk_mw1278d_uart_printf("%s\r\n","I got sth.");
		  update_bms_stats(rx_data);
	  }
//	  if (rx_data[0] == '1') {
//		  atk_mw1278d_uart_printf("%s\r\n","What can I say");
//	  }else if (rx_data[0] == '2') {
//		  atk_mw1278d_uart_printf("%s\r\n","MAMBA OUT");
//	  }else{
//		  atk_mw1278d_uart_printf("%s\r\n","MAN");
//	  }
	  atk_mw1278d_uart_rx_restart();
	  HAL_Delay(200);


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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
