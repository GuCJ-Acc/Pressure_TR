#include "process.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

PressureSensorData sensorData;

/**************************************************************************
函数功能：解析相关气压ADC串口数据函数
入口参数：无
返回  值：无
说    明：解析相关气压ADC串口字符串数据函数，数据解析完成后，将相关数据用于整理转发
**************************************************************************/
void parse_PressureData(uint8_t* input, PressureSensorData* data)
{
    char *token;
    // char input_copy[100];
    // strcpy(input_copy, input);

    char *input_copy = strdup((const char *)input); // 复制输入字符串方便分割
    token = strtok(input_copy, ",");

    // 使用 strtok 函数按逗号分割输入字符串，并使用 sscanf 解析每个部分的数值
    while (token != NULL) {
        if (sscanf(token, "LF:%hhu", &data->LF) == 1) {
            // 解析 LF 值
        } else if (sscanf(token, "LH:%hhu", &data->LH) == 1) {
            // 解析 LH 值
        } else if (sscanf(token, "RF:%hhu", &data->RF) == 1) {
            // 解析 RF 值
        } else if (sscanf(token, "RH:%hhu", &data->RH) == 1) {
            // 解析 RH 值
        }
        token = strtok(NULL, ",");
    }
    
    free(input_copy); // 释放复制的字符串
}



/**************************************************************************
函数功能：解析相关气压ADC串口数据函数
入口参数：无
返回  值：无
说    明：解析相关气压ADC串口字符串数据函数，数据解析完成后，将相关数据用于整理转发
**************************************************************************/
void process_PressureData(void)
{
    if(UsartType3.receive_flag) // 如果产生了空闲中断
    {
        UsartType3.receive_flag=0;  // 清零标记

        // 解析串口数据
        parse_PressureData(UsartType3.usartDMA_rxBuf, &sensorData);
        
        // 打印解析结果
        // UART3_printf_Tr("LF:%d\r\n", sensorData.LF);
        // UART3_printf_Tr("LH:%d\r\n", sensorData.LH);
        // UART3_printf_Tr("RF:%d\r\n", sensorData.RF);
        // UART3_printf_Tr("RH:%d\r\n", sensorData.RH);
        // UART3_printf_Tr("-------------\r\n");
    }
}