#include "uart_1.h"
#include "stdio.h"

uint8_t uart_buf[256];


USART_RECEIVETYPE UsartType1;
USART_RECEIVETYPE UsartType3;

uint8_t u_buf[256];
uint8_t Rx_buff[50];



/**************************************************************************
函数功能：UART1（串口1）发送数据
入口参数：发送数据的数组，发送数据的长度
返回  值：无 
说    明：1.发送相关数据，并置位dmaSend_flag标志位；
		  2.DMA发送完成后会进入中断回调函数，重新置位dmaSend_flag标志位；
**************************************************************************/
// DMA发送函数
void Usart1SendData_DMA(uint8_t *pdata, uint16_t Length)  
{  
    while(UsartType1.dmaSend_flag == USART_DMA_SENDING);  
    UsartType1.dmaSend_flag = USART_DMA_SENDING;  
    HAL_UART_Transmit_DMA(&huart1, pdata, Length);  
}  

// DMA发送函数
void Usart3SendData_DMA(uint8_t *pdata, uint16_t Length)  
{  
    while(UsartType3.dmaSend_flag == USART_DMA_SENDING);  
    UsartType3.dmaSend_flag = USART_DMA_SENDING;  
    HAL_UART_Transmit_DMA(&huart3, pdata, Length);  
} 

  
// DMA发送完成中断回调函数
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{  
     __HAL_DMA_DISABLE(huart->hdmatx);  
		if(huart->Instance == huart1.Instance)
			UsartType1.dmaSend_flag = USART_DMA_SENDOVER; 
}





/**************************************************************************
函数功能：串口中断回调函数
入口参数：串口中断号
返回  值：无 
说    明：串口中断处理回调函数
**************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart1)
	{
		HAL_UART_Receive_IT(&huart1,Rx_buff,1);
	}
}

/**************************************************************************
函数功能：串口DMA接收空闲中断 
入口参数：串口中断号
返回  值：无 
说    明：串口DMA接收空闲中断处理函数；
		 相关串口数据数组：UsartType1.usartDMA_rxBuf；
		 相关串口数据数组长度：UsartType1.rx_len；
		 1.清除接收空闲中断标志位__HAL_UART_CLEAR_IDLEFLAG()；
		 2.停止DMA串口接收；处理接收数据长度；置位相关标志位；
		 3.重新开启DMA串口接收；
**************************************************************************/
void UsartReceive_IDLE(UART_HandleTypeDef *huart)
{  
    uint32_t temp;  
    
    /* 构建用于UART1 RX 接受数据接收的函数段 */
	if(huart->Instance == huart1.Instance)
	{
		if((__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) != RESET))
		{   
			__HAL_UART_CLEAR_IDLEFLAG(&huart1);  
			HAL_UART_DMAStop(&huart1); 
			
			temp = huart1.hdmarx->Instance->CNDTR;  
			UsartType1.rx_len =  RECEIVELEN - temp;
			UsartType1.receive_flag = 1;
							
			HAL_UART_Receive_DMA(&huart1, UsartType1.usartDMA_rxBuf, RECEIVELEN);  
		}  
	}

    /* 构建用于UART3 RX 接受数据接收的函数段 */
    if(huart->Instance == huart3.Instance)
	{
		if((__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) != RESET))
		{   
			__HAL_UART_CLEAR_IDLEFLAG(&huart3);  
			HAL_UART_DMAStop(&huart3); 
			
			temp = huart3.hdmarx->Instance->CNDTR;  
			UsartType3.rx_len =  RECEIVELEN - temp;
			UsartType3.receive_flag = 1;
							
			HAL_UART_Receive_DMA(&huart3, UsartType3.usartDMA_rxBuf, RECEIVELEN);
		}  
	}
}  

