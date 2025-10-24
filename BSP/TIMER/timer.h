#ifndef __TIMER_H
#define __TIMER_H	 
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "dma.h"
#include "led.h"
#include "stdio.h"
#include "string.h"
#include "uart_1.h"
#include "process.h"

extern uint16_t* getArrayADC();
extern char Device_Index[3];

void TIM_SetCCR(TIM_TypeDef *TIMx, uint32_t CHx, uint16_t CCR);
void TIM3_IRQProcess(void);
void Copy_ADCbuf();

#endif 