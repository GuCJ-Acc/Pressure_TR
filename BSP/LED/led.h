#ifndef __LED_H
#define __LED_H	 
#include "main.h"
#include "gpio.h"

#define LED0_ON 		HAL_GPIO_WritePin(LED0_GPIO_Port,  LED0_Pin,  GPIO_PIN_SET)
#define LED0_OFF		HAL_GPIO_WritePin(LED0_GPIO_Port,  LED0_Pin, GPIO_PIN_RESET)
#define LED0_Toggle		HAL_GPIO_TogglePin(LED0_GPIO_Port,  LED0_Pin)

void led_bling(uint32_t time);
void led_bling2(uint32_t time);
void led_bling3(uint32_t time);
void led_bling_sum(uint32_t sum,uint32_t time);

#endif 