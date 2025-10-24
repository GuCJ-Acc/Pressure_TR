#include "led.h"


//  LED0--PC13

/**************************************************************************
函数功能：LED闪烁
入口参数：闪烁时间（ms）
返回  值：无 
说    明：采用原始数据对HAL库进行操作
**************************************************************************/

void led_bling(uint32_t time)
{
		HAL_GPIO_WritePin((GPIO_TypeDef *) GPIOD,(uint16_t) GPIO_PIN_2,(GPIO_PinState) 0);
		HAL_GPIO_WritePin((GPIO_TypeDef *) GPIOA,(uint16_t) GPIO_PIN_8,(GPIO_PinState) 0);
		HAL_Delay(time);
	
	
		HAL_GPIO_WritePin((GPIO_TypeDef *) GPIOD,(uint16_t) GPIO_PIN_2,(GPIO_PinState) 1);
		HAL_GPIO_WritePin((GPIO_TypeDef *) GPIOA,(uint16_t) GPIO_PIN_8,(GPIO_PinState) 1);
		HAL_Delay(time);
}


/**************************************************************************
函数功能：LED闪烁
入口参数：闪烁时间（ms）
返回  值：无 
说    明：采用Cube中 User Labl 标签的对HAL库进行操作
**************************************************************************/

void led_bling2(uint32_t time)
{
		HAL_GPIO_WritePin(LED0_GPIO_Port,  LED0_Pin, GPIO_PIN_RESET);
		HAL_Delay(time);
	
		HAL_GPIO_WritePin(LED0_GPIO_Port,  LED0_Pin,  GPIO_PIN_SET);
		HAL_Delay(time);
}


/**************************************************************************
函数功能：LED闪烁
入口参数：闪烁时间（ms）
返回  值：无 
说    明：采用宏定义，Cube中 User Labl 标签的对HAL库进行操作
**************************************************************************/

void led_bling3(uint32_t time)
{
	//两个LED灯亮着
	LED0_ON;
	HAL_Delay(time);

	//两个LED灯灭掉
	LED0_OFF;
	HAL_Delay(time);
}


/**************************************************************************
函数功能：LED闪烁次数
入口参数：闪烁时间（ms）
返回  值：无 
说    明：使用HAL库中的GPIO取反函数控制灯闪烁次数
**************************************************************************/
void led_bling_sum(uint32_t sum,uint32_t time)
{
	for(int i=0;i<sum;i++)
	{
		HAL_Delay(time);
		HAL_GPIO_TogglePin(LED0_GPIO_Port,  LED0_Pin);
	}
}
