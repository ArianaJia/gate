/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
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
#include "can.h"

/* USER CODE BEGIN 0 */
extern int Voltage[6][23];
extern int Temperature[6][8];

extern int Highest_Voltage;
extern int Lowest_Voltage;
extern int Highest_Temperature;
extern int Lowest_Temperature;
extern int Asking_Voltage;
extern int Asking_I;
extern int Sum_Voltage;
extern int Sum_I;
extern int Charging_Voltage;
extern int IMD;
extern int Air1;
extern int Air2;
extern int Air3;
extern int SOC;
extern int Battery_State;
extern int Charging_Signal;
CAN_TxHeaderTypeDef TxHeader;
uint8_t CAN_TxData[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 };
uint32_t CAN_TxMail;
uint32_t CAN_ID = 0x102;

CAN_RxHeaderTypeDef RxHeader;
uint8_t CAN_RxData[8] = { 0 };

/* USER CODE END 0 */

CAN_HandleTypeDef hcan;

/* CAN init function */
void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 24;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_3TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */

  /* USER CODE END CAN_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN GPIO Configuration
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
    HAL_NVIC_SetPriority(CAN1_RX1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX1_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN GPIO Configuration
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_RX1_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/*
 * @func: ����CAN���˲�
 *
 */
void CAN_Filter_Config(void)
{
	CAN_FilterTypeDef CAN_FilterInitStructure = {
			.FilterMode = CAN_FILTERMODE_IDMASK,
			.FilterActivation = ENABLE,                    //ʹ�ܹ�����
			.FilterBank = 0x00,                            //���������ţ���Χ��0-13
			.FilterFIFOAssignment = CAN_FILTER_FIFO0,      //���Ĵ洢FIFO��ţ�FIFO0
			.FilterIdHigh = 0x0000,           //��һ��ID
			.FilterIdLow = 0x0000,            //�ڶ���ID
			.FilterMaskIdHigh = 0x0000,       //������ID
			.FilterMaskIdLow = 0x0000,                     //���ĸ�ID
			.FilterScale = CAN_FILTERSCALE_32BIT,          //32λ��һ�����������������4����ͨ��id
			.SlaveStartFilterBank = 14                      //���ӹ������ֽ��ߣ���can������
	};
	HAL_CAN_ConfigFilter(&hcan, &CAN_FilterInitStructure);
}
//uint16_t CAN_RX_MSG_ID[4] = {0x401, 0x501, 0x502, 0x50};
//
//void CAN_Filter_Config(void)
//{
//	CAN_FilterTypeDef CAN_FilterInitStructure = {
//			.FilterActivation = ENABLE,                    //ʹ�ܹ�����
//			.FilterBank = 0x00,                            //���������ţ���Χ��0-13
//			.FilterFIFOAssignment = CAN_FILTER_FIFO0,      //���Ĵ洢FIFO��ţ�FIFO0
//			.FilterIdHigh = CAN_RX_MSG_ID[0]<<5,           //��һ��ID
//			.FilterIdLow = CAN_RX_MSG_ID[1]<<5,            //�ڶ���ID
//			.FilterMaskIdHigh = CAN_RX_MSG_ID[2]<<5,       //������ID
//			.FilterMaskIdLow = CAN_RX_MSG_ID[3]<<5,                     //���ĸ�ID
//			.FilterMode = CAN_FILTERMODE_IDLIST,           //ID�б�ģʽ
//			.FilterScale = CAN_FILTERSCALE_16BIT,          //16λ��һ�����������������4����ͨ��id
//			.SlaveStartFilterBank = 0                      //���ӹ������ֽ��ߣ���can������
//	};
//	HAL_CAN_ConfigFilter(&hcan, &CAN_FilterInitStructure);
//}
/*
 * @func: CAN���ķ���[��׼��ʽ������֡]
 */
void User_CAN_Send()
{
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.StdId = CAN_ID;
	TxHeader.TransmitGlobalTime = DISABLE;
	TxHeader.DLC = 8;
	HAL_CAN_AddTxMessage(&hcan, &TxHeader, CAN_TxData, &CAN_TxMail);
}

/*
 * @func: CAN���ķ���[��׼��ʽ������֡]
 */
//shaoqi_add
//����ָ��ID������
void User_CAN_Send_sq(uint32_t CAN_ID_NEW,uint8_t* CAN_TxData_NEW)
{
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.StdId = CAN_ID_NEW;
	TxHeader.TransmitGlobalTime = DISABLE;
	TxHeader.DLC = 8;
	HAL_CAN_AddTxMessage(&hcan, &TxHeader, CAN_TxData_NEW, &CAN_TxMail);
}

/*
 * @func: CAN���Ľ����ж�[FIFO0]
 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if(HAL_CAN_GetRxMessage(hcan, CAN_FILTER_FIFO0, &RxHeader, CAN_RxData)!= HAL_OK)
	{
	    // ������
	    Error_Handler();
	}
//	User_CAN_Send_sq(0x02,CAN_TxData);
//	printf("ID:0x%X\r\n",RxHeader.StdId);

	//���ݲ�ͬ��ID����ò�ͬ����Ϣ�������뿴���ӵ�CANЭ��
	//0x180050F3+((MODULE-1)*0x6+can_beat)*0x10000
	//0x184050F3+(MODULE-1)*0x10000
	if(RxHeader.ExtId>=0x180050F3&&RxHeader.ExtId<=0x184550F3)
	{
		int module_id;
//		User_CAN_Send_sq(0x03,CAN_TxData);
		if(RxHeader.ExtId>=0x184050F3)/*�¶�*/
		{
			module_id = (int)((RxHeader.ExtId>>16)&0x000F);
//			User_CAN_Send_sq(0x04,CAN_TxData);
			for(int i=0;i<=7;i++)
			{
				Temperature[module_id][i] = CAN_RxData[i]-30;
			}
		}else
		{
			int middle = (int)((RxHeader.ExtId-0x180050F3)>>16);
			module_id = middle/6;
			if(middle%6==0)
			{
//				User_CAN_Send_sq(0x04,CAN_TxData);
				for(int i=1;i<=3;i++)
				{
					Voltage[module_id][i] = (int)(CAN_RxData[2*i]+CAN_RxData[2*i+1]*256);
				}
			}else if(middle%6==1)
			{
//				User_CAN_Send_sq(0x04,CAN_TxData);
				for(int i=0;i<=3;i++)
				{
					Voltage[module_id][i+4] = (int)(CAN_RxData[2*i]+CAN_RxData[2*i+1]*256);
				}
			}else if(middle%6==2)
			{
//				User_CAN_Send_sq(0x04,CAN_TxData);
				for(int i=0;i<=3;i++)
				{
					Voltage[module_id][i+8] = (int)(CAN_RxData[2*i]+CAN_RxData[2*i+1]*256);
				}
			}else if(middle%6==3)
			{
//				User_CAN_Send_sq(0x04,CAN_TxData);
				for(int i=0;i<=3;i++)
				{
					Voltage[module_id][i+12] = (int)(CAN_RxData[2*i]+CAN_RxData[2*i+1]*256);
				}
			}else if(middle%6==4)
			{
//				User_CAN_Send_sq(0x04,CAN_TxData);
				for(int i=0;i<=3;i++)
				{
					Voltage[module_id][i+16] = (int)(CAN_RxData[2*i]+CAN_RxData[2*i+1]*256);
				}
			}else if(middle%6==5)
			{
//				User_CAN_Send_sq(0x04,CAN_TxData);
				for(int i=0;i<=3;i++)
				{
					Voltage[module_id][i+20] = (int)(CAN_RxData[2*i]+CAN_RxData[2*i+1]*256);
				}
			}
		}
	}
	if(RxHeader.ExtId>=0x186050F4&&RxHeader.ExtId<=0x186350F4)
	{
		if(RxHeader.ExtId==0x186050F4)
		{
			Sum_Voltage = (int)(CAN_RxData[0]*256+CAN_RxData[1]);
			Sum_I = (int)(CAN_RxData[2]*256+CAN_RxData[3]);
			SOC = (int)CAN_RxData[4];
			IMD = (int)CAN_RxData[5];
			Battery_State = (int)(CAN_RxData[6]&0xF0>>4)-2;
			if(Battery_State==3)
			{
				if(!Charging_Signal)
				{
					Battery_State=3;
				}else
				{
					Battery_State=4;
				}
			}
		}else if(RxHeader.ExtId==0x186150F4)
		{
			Highest_Voltage = (int)(256*CAN_RxData[0]+CAN_RxData[1]);
			Lowest_Voltage = (int)(256*CAN_RxData[2]+CAN_RxData[3]);
		}else if(RxHeader.ExtId==0x186250F4)
		{
			Highest_Temperature = (int)CAN_RxData[0]-30;
			Lowest_Temperature = (int)CAN_RxData[1]-30;
		}else if(RxHeader.ExtId==0x186350F4)
		{
			Air1=(int)((CAN_RxData[0]&0x0C)>>2);
			Air2=(int)((CAN_RxData[0]&0x30)>>4);
			Air3=(int)((CAN_RxData[0]&0xC0)>>6);
			Charging_Signal = (int)(CAN_RxData[1]&0x3F>>5);
			Asking_Voltage = (int)(256*CAN_RxData[2]+CAN_RxData[3]);
			Asking_I = (int)(256*CAN_RxData[4]+CAN_RxData[5])/10;
			Charging_Voltage = (int)(256*CAN_RxData[6]+CAN_RxData[7]);
		}
	}
}



/* USER CODE END 1 */
