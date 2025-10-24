#ifndef __UART_1_H
#define __UART_1_H	 
#include "main.h"

#include "usart.h"
#include "gpio.h"
#include "stdio.h"
#include "dma.h"

#include "string.h"
#include "stdio.h"


extern uint8_t uart_buf[256];

// 串口DMA发送方式（非阻塞），增加延时以保证数据的完整性
#define UART1_printf_DMA(...) HAL_UART_Transmit_DMA(&huart1,\
												   (uint8_t *)uart_buf,\
													sprintf((char*)uart_buf,__VA_ARGS__))


// 普通串口发送方式（阻塞）
#define UART1_printf_Tr(...) HAL_UART_Transmit(&huart1,\
											  (uint8_t *)uart_buf,\
											   sprintf((char*)uart_buf,__VA_ARGS__),\
											   0xffff)

// 普通串口发送方式（阻塞）
#define UART3_printf_Tr(...) HAL_UART_Transmit(&huart3,\
											  (uint8_t *)uart_buf,\
											   sprintf((char*)uart_buf,__VA_ARGS__),\
											   0xffff)

/* 构建用于UART数据接收的结构体USART_RECEIVETYPE */
#define RECEIVELEN 1024  
#define USART_DMA_SENDING 1     // 发生未完成
#define USART_DMA_SENDOVER 0    // 发生完成 

typedef struct  
{  
uint8_t receive_flag:1;             // 空闲接收完成 
uint8_t dmaSend_flag:1;             // 发送完成  
uint16_t rx_len;                    // 接收长度	
uint8_t usartDMA_rxBuf[RECEIVELEN]; // DMA接收缓存  
}USART_RECEIVETYPE;  
   
extern USART_RECEIVETYPE UsartType1;
extern USART_RECEIVETYPE UsartType3;
extern uint8_t u_buf[256];
extern uint8_t Rx_buff[50];

void Usart1SendData_DMA(uint8_t *pdata, uint16_t Length);
void Usart3SendData_DMA(uint8_t *pdata, uint16_t Length);
void UsartReceive_IDLE(UART_HandleTypeDef *huart);

#endif