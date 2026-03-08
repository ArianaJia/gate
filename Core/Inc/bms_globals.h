/*
 * bms_globals.h
 *
 *  Created on: Sep 27, 2025
 *      Author: lenovo
 */

#include "sys.h"

#ifndef INC_BMS_GLOBALS_H_
#define INC_BMS_GLOBALS_H_

// 声明全局变量（使用extern）
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

extern int Acc_x;
extern int Acc_y;
extern int Velocity;

// 函数声明
void init_bms_globals(void);
void update_bms_stats(uint8_t *);
int string2numbers(const char*, uint16_t*);

#endif /* INC_BMS_GLOBALS_H_ */
