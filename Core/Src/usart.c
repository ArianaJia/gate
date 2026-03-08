/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
#include "usart.h"

/* USER CODE BEGIN 0 */
char IMD_mode[2][24] = {"正常","错误"};
char Air_mode[2][24] = {"断开","闭合"};
char Battery_mode[6][24] = {"自检","待机","预充","放电","充电","故障"};
/* USER CODE END 0 */

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}
/* USART3 init function */

void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */
////
  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN USART2_MspInit 1 */
////
  /* USER CODE END USART2_MspInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */
////
  /* USER CODE END USART3_MspInit 0 */
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* USART3 interrupt Init */
    HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspInit 1 */
////
  /* USER CODE END USART3_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();

    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

    /* USART3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

void HMI_set_Voltage(int model,int number,int voltage)
{
	char buff[30];
	//锟斤拷锟斤拷小锟斤拷锟斤拷锟斤拷位锟斤拷
	sprintf(buff, "model%d.V_%d.val=%d\xff\xff\xff", model,number,voltage);
	HAL_UART_Transmit(&huart2, (uint8_t*) buff, strlen(buff), 200);
}

void HMI_set_Temperature(int model,int number,int temperature)
{
	char buff[30];
	sprintf(buff, "model%d.T_%d.val=%d\xff\xff\xff", model,number,temperature);
	HAL_UART_Transmit(&huart2, (uint8_t*) buff, strlen(buff), 200);
}
void HMI_set_V(int Highest_Voltage,int Lowest_Voltage,int Asking_Voltage,int Sum_Voltage,int Charging_Voltage)
{
	char buff[30];
	sprintf(buff, "main.Highest_V.val=%d\xff\xff\xff", Highest_Voltage);
	HAL_UART_Transmit(&huart2, (uint8_t*) buff, strlen(buff), 200);
	sprintf(buff, "main.Lowest_V.val=%d\xff\xff\xff", Lowest_Voltage);
	HAL_UART_Transmit(&huart2, (uint8_t*) buff, strlen(buff), 200);
	sprintf(buff, "main.Asking_V.val=%d\xff\xff\xff", Asking_Voltage);
	HAL_UART_Transmit(&huart2, (uint8_t*) buff, strlen(buff), 200);
	sprintf(buff, "main.Sum_V.val=%d\xff\xff\xff", Sum_Voltage);
	HAL_UART_Transmit(&huart2, (uint8_t*) buff, strlen(buff), 200);
	sprintf(buff, "main.Charging_V.val=%d\xff\xff\xff", Charging_Voltage);
	HAL_UART_Transmit(&huart2, (uint8_t*) buff, strlen(buff), 200);
}
void HMI_set_I(int Asking_I,int Sum_I)
{
	char buff[30];
	sprintf(buff, "main.Asking_I.val=%d\xff\xff\xff", Asking_I);
	HAL_UART_Transmit(&huart2, (uint8_t*) buff, strlen(buff), 200);
	sprintf(buff, "main.Sum_I.val=%d\xff\xff\xff", Sum_I);
	HAL_UART_Transmit(&huart2, (uint8_t*) buff, strlen(buff), 200);
}
void HMI_set_T(int Highest_Temperature,int Lowest_Temperature)
{
	char buff[30];
	sprintf(buff, "main.Highest_T.val=%d\xff\xff\xff", Highest_Temperature);
	HAL_UART_Transmit(&huart2, (uint8_t*) buff, strlen(buff), 200);
	sprintf(buff, "main.Lowest_T.val=%d\xff\xff\xff", Lowest_Temperature);
	HAL_UART_Transmit(&huart2, (uint8_t*) buff, strlen(buff), 200);
}
void HMI_set_State(int IMD,int Air1,int Air2,int Air3,int SOC,int Battery_State)
{
	char buff[40];
	sprintf(buff, "main.IMD.txt=\"%s\"\xff\xff\xff", IMD_mode[IMD]); //锟街凤拷锟斤拷锟斤拷要锟斤拷锟斤拷锟斤拷锟斤拷
	HAL_UART_Transmit(&huart2, (uint8_t*) buff, strlen(buff), 200);
	sprintf(buff, "main.AIR1.txt=\"%s\"\xff\xff\xff", Air_mode[Air1]); //锟街凤拷锟斤拷锟斤拷要锟斤拷锟斤拷锟斤拷锟斤拷
	HAL_UART_Transmit(&huart2, (uint8_t*) buff, strlen(buff), 200);
	sprintf(buff, "main.AIR2.txt=\"%s\"\xff\xff\xff", Air_mode[Air2]); //锟街凤拷锟斤拷锟斤拷要锟斤拷锟斤拷锟斤拷锟斤拷
	HAL_UART_Transmit(&huart2, (uint8_t*) buff, strlen(buff), 200);
	sprintf(buff, "main.AIR3.txt=\"%s\"\xff\xff\xff", Air_mode[Air3]); //锟街凤拷锟斤拷锟斤拷要锟斤拷锟斤拷锟斤拷锟斤拷
	HAL_UART_Transmit(&huart2, (uint8_t*) buff, strlen(buff), 200);
	sprintf(buff, "main.Battery.txt=\"%s\"\xff\xff\xff", Battery_mode[Battery_State]); //锟街凤拷锟斤拷锟斤拷要锟斤拷锟斤拷锟斤拷锟斤拷
	HAL_UART_Transmit(&huart2, (uint8_t*) buff, strlen(buff), 200);
	sprintf(buff, "main.SOC.val=%d\xff\xff\xff", SOC);
	HAL_UART_Transmit(&huart2, (uint8_t*) buff, strlen(buff), 200);
}

void HMI_set_A(int Velocity,int Acc_x,int Acc_y)
{
	char buff[30];
	sprintf(buff, "main.Velocity.val=%d\xff\xff\xff", Velocity);
	HAL_UART_Transmit(&huart2, (uint8_t*) buff, strlen(buff), 200);
	sprintf(buff, "main.Acc_x.val=%d\xff\xff\xff", Acc_x);
	HAL_UART_Transmit(&huart2, (uint8_t*) buff, strlen(buff), 200);
	sprintf(buff, "main.Acc_y.val=%d\xff\xff\xff", Acc_y);
	HAL_UART_Transmit(&huart2, (uint8_t*) buff, strlen(buff), 200);
}
/* USER CODE END 1 */
