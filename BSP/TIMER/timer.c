#include "timer.h"
#include "led.h"
#include "stdio.h"

char Device_Index[3];

/**************************************************************************
函数功能：定时器TIMx的中断函数
入口参数：[*htim]: 定时器的指针
返回  值：无
说    明：定时器的中断函数处理
**************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    // 检查定时器是否为TIM3定时器
    if(htim->Instance == TIM3)
	{
		// LED0_Toggle;

        TIM3_IRQProcess();
	}
}


/**************************************************************************
函数功能：复制ADC模拟量数据函数，并进行串口输出
入口参数：[copy_buf]: ADC数据数组
返回  值：无
说    明：使用 getArrayADC(); 获取 main.c 中 adc_buf 数组数据，并进行打印输出
**************************************************************************/
void Copy_ADCbuf()
{    
    uint16_t* adc_buf = getArrayADC();

    int LF = sensorData.LF;
    int LH = sensorData.LH;
    int RF = sensorData.RF;
    int RH = sensorData.RH;

    int cur_ADC = adc_buf[0];

    if(strcmp(Device_Index, "LF") == 0)
    {   LF = cur_ADC;  }
    else if(strcmp(Device_Index, "LH") == 0)
    {   LH = cur_ADC;  }
    else if(strcmp(Device_Index, "RF") == 0)
    {   RF = cur_ADC;  }
    else if(strcmp(Device_Index, "RH") == 0)
    {   RH = cur_ADC;  }
    
    // UART1_printf_Tr("ADC:%d\r\n", adc_buf[0]);

    UART1_printf_Tr("LF:%d,LH:%d,RF:%d,RH:%d\r\n", LF, LH, RF, RH);

}


/**************************************************************************
函数功能：定时器TIMx的PWM输出占空比CCRx设置函数
入口参数：[TIMx]:TIM1~8、[CHx]:TIM_CHANNEL_1~4、[CCR]:0~65535（舵机控制时：0~2500）
返回  值：无
说    明：通过设置TIMx寄存器CCRx的值设置输出通道的占空比
**************************************************************************/
void TIM_SetCCR(TIM_TypeDef *TIMx, uint32_t CHx, uint16_t CCR) 
{    
    if(CHx==TIM_CHANNEL_1)    TIMx->CCR1 = CCR;
    if(CHx==TIM_CHANNEL_2)    TIMx->CCR2 = CCR;
    if(CHx==TIM_CHANNEL_3)    TIMx->CCR3 = CCR;
    if(CHx==TIM_CHANNEL_4)    TIMx->CCR4 = CCR;
} 


/**************************************************************************
函数功能：定时器TIM3的中断处理函数
入口参数：无
返回  值：无
说    明：处理定时器TIM3的中断内容
**************************************************************************/
void TIM3_IRQProcess(void)
{
    static int i = 0;
    i++;

    if (i > 10)
    {
        i = 0;
        LED0_Toggle;    // LED0 取反
    }
    
    Copy_ADCbuf();  // 读取ADC模拟量数据，并进行串口输出

}