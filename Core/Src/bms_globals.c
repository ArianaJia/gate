/*
 * bms_globals.c
 *
 *  Created on: Sep 27, 2025
 *      Author: lenovo
 */
#include "bms_globals.h"
#include "atk_mw1278d_uart.h"
#include <string.h>

// 定义全局变量（分配内存）
int Voltage[6][23] = {0};
int Temperature[6][8] = {0};
int Highest_Voltage = 0;
int Lowest_Voltage = 0;
int Highest_Temperature = 0;
int Lowest_Temperature = 0;
int Asking_Voltage = 0;
int Asking_I = 0;
int Sum_Voltage = 0;
int Sum_I = 0;
int Charging_Voltage = 0;
int IMD = 1;
int Air1 = 0;
int Air2 = 0;
int Air3 = 0;
int SOC = 0;
int Battery_State = 0;
int Charging_Signal = 0;
int Acc_x = 0;
int Acc_y = 0;
int Velocity = 0;


void init_bms_globals(void) {
    memset(Voltage, 0, sizeof(Voltage));
    memset(Temperature, 0, sizeof(Temperature));
    Highest_Voltage = 0;
    Lowest_Voltage = 0;
    Highest_Temperature = 0;
    Lowest_Temperature = 0;
    Asking_Voltage = 0;
    Asking_I = 0;
    Sum_Voltage = 0;
    Sum_I = 0;
    Charging_Voltage = 0;
    IMD = 1;
    Air1 = 0;
    Air2 = 0;
    Air3 = 0;
    SOC = 0;
    Battery_State = 0;
    Charging_Signal = 0;
    Acc_x = 0;
    Acc_y = 0;
    Velocity = 0;
    Voltage[0][0]=3812;
}

// 返回解析到的数字个数
int string2numbers(const char *str, uint16_t *array) {
    int i = 0;
    int num = 0;
    int count = 0;  // 本地计数器

    while(i < ATK_MW1278D_UART_TX_BUF_SIZE && str[i] != '\0' && count < 23) {
        if (str[i] >= '0' && str[i] <= '9') {
            // 处理数字
            num = num * 10 + (str[i] - '0');
        } else if (str[i] == ',' || str[i] == ';') {
            // 遇到分隔符，保存数字
            if (num <= 65535) {
                array[count++] = (uint16_t)num;
            }
            num = 0; // 重置数字
        }
        i++;
    }

    // 处理最后一个数字
    if (num <= 65535 && count < 23) {
        array[count++] = (uint16_t)num;
    }

    return count;  // 返回解析到的数字个数
}

void safe_array_access(void) {
    // 检查全局变量的地址
	atk_mw1278d_uart_printf("  Highest_Voltage: %p\r\n", (void*)&Highest_Voltage);
	atk_mw1278d_uart_printf("  Lowest_Voltage: %p\r\n", (void*)&Lowest_Voltage);
	atk_mw1278d_uart_printf("  Highest_Temperature: %p\r\n", (void*)&Highest_Temperature);
	atk_mw1278d_uart_printf("  Lowest_Temperature: %p\r\n", (void*)&Lowest_Temperature);
	atk_mw1278d_uart_printf("  Asking_Voltage: %p\r\n", (void*)&Asking_Voltage);
	atk_mw1278d_uart_printf("  Asking_I: %p\r\n", (void*)&Asking_I);
	atk_mw1278d_uart_printf("  Sum_Voltage: %p\r\n", (void*)&Sum_Voltage);
	atk_mw1278d_uart_printf("  Sum_I: %p\r\n", (void*)&Sum_I);
	atk_mw1278d_uart_printf("  Charging_Voltage: %p\r\n", (void*)&Charging_Voltage);
	atk_mw1278d_uart_printf("  IMD: %p\r\n", (void*)&IMD);
	atk_mw1278d_uart_printf("  Air1: %p\r\n", (void*)&Air1);
	atk_mw1278d_uart_printf("  Air2: %p\r\n", (void*)&Air2);
	atk_mw1278d_uart_printf("  Air3: %p\r\n", (void*)&Air3);
	atk_mw1278d_uart_printf("  SOC: %p\r\n", (void*)&SOC);
	atk_mw1278d_uart_printf("  Battery_State: %p\r\n", (void*)&Battery_State);
	atk_mw1278d_uart_printf("  Charging_Signal: %p\r\n", (void*)&Charging_Signal);
	atk_mw1278d_uart_printf("  Acc_x: %p\r\n", (void*)&Acc_x);
	atk_mw1278d_uart_printf("  Acc_y: %p\r\n", (void*)&Acc_y);
	atk_mw1278d_uart_printf("  Velocity: %p\r\n", (void*)&Velocity);
}

void update_bms_stats(uint8_t *rx_data) {
	atk_mw1278d_uart_printf("%s\r\n","Data received!");
//	safe_array_access();

    if(rx_data[0] == 'V') {
        int row = rx_data[1] - '0';
        if(row >= 0 && row < 6) {
            uint16_t array[23];
            int count = string2numbers((const char*)(rx_data + 2), array);

            // 逐个复制数组元素
            for(int i = 0; i < count && i < 23; i++) {
                Voltage[row][i] = array[i];
            }
        }

    } else if(rx_data[0] == 'T') {
        int row = rx_data[1] - '0';
        if(row >= 0 && row < 6) {
            uint16_t array[8];
            int count = string2numbers((const char*)(rx_data + 2), array);

            for(int i = 0; i < count && i < 8; i++) {
                Temperature[row][i] = array[i];
            }
        }

    } else if(rx_data[0] == 'A') {
        uint16_t array[3];
        int count = string2numbers((const char*)(rx_data + 1), array);

        if(count >= 3) {
        	atk_mw1278d_uart_printf("%s\r\n","Processing A Data!");
            Acc_x = array[0];
            Acc_y = array[1];
            Velocity = array[2];
        }

    } else if(rx_data[0] == 'O') {
        uint16_t array[16];
        int count = string2numbers((const char*)(rx_data + 1), array);

        // 检查是否解析到足够的数据
        if(count >= 16) {
        	atk_mw1278d_uart_printf("%s\r\n","Processing O Data!");
            Highest_Voltage = array[0];
            Lowest_Voltage = array[1];
            Highest_Temperature = array[2];
            Lowest_Temperature = array[3];
            Asking_Voltage = array[4];
            Asking_I = array[5];
            Sum_Voltage = array[6];
            Sum_I = array[7];
            Charging_Voltage = array[8];
            IMD = array[9];
            Air1 = array[10];
            Air2 = array[11];
            Air3 = array[12];
            SOC = array[13];
            Battery_State = array[14];
            Charging_Signal = array[15];
        }

    }

}
