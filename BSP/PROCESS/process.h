#ifndef __PROCESS_H
#define __PROCESS_H	 
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "dma.h"
#include "led.h"
#include "uart_1.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// #include <stdint.h>

// 定义结构体来表示解析后的数据
typedef struct {
    int LF; // 前左
    int LH; // 后左
    int RF; // 前右
    int RH; // 后右
} PressureSensorData;


extern PressureSensorData sensorData;
void parse_PressureData(uint8_t* input, PressureSensorData* data);
void process_PressureData(void);

#endif 