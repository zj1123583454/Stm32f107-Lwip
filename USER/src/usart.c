/**
  ******************************************************************************
  * @file    usart.c
  * $Author: wdluo $
  * $Revision: 17 $
  * $Date:: 2012-07-06 11:16:48 +0800 #$
  * @brief   串口相关函数。
  ******************************************************************************
  * @attention
  *
  *<h3><center>&copy; Copyright 2009-2012, ViewTool</center>
  *<center><a href="http:\\www.viewtool.com">http://www.viewtool.com</a></center>
  *<center>All Rights Reserved</center></h3>
  * 
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include "stm32f107.h"
#include "stm32f10x_gpio.h"
/** @addtogroup USART
  * @brief 串口模块
  * @{
  */

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


/**
  * @brief  开启GPIOA,串口1时钟 
  * @param  None
  * @retval None
  * @note  对于某些GPIO上的默认复用功能可以不开启服用时钟，如果用到复用功能的重
           映射，则需要开启复用时钟
  */
void USART_RCC_Configuration(void)
{
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//开复用时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
}

/**
  * @brief  设置串口1发送与接收引脚的模式 
  * @param  None
  * @retval None
  */
void USART_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/**
  * @brief  配置串口1，并使能串口1
  * @param  None
  * @retval None
  */
void USART_Configuration(void)
{
	USART_InitTypeDef USART_InitStruct;
//	NVIC_InitTypeDef 	NVIC_InitStructure;
	USART_RCC_Configuration();
	USART_GPIO_Configuration();

	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStruct);
	
//	USART_ITConfig(USART1,USART_IT_TC,DISABLE);  
//	USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);  
//	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);    

	//配置UART1中断    
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);  
//	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;               //通道设置为串口1中断    
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;       //中断占先等级0    
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;              //中断响应优先级0    
//	NVIC_InitStructure.NVIC_IRQ-ChannelCmd = ENABLE;                 //打开中断    
//	NVIC_Init(&NVIC_InitStructure);     
//	 
	//采用DMA方式发送  采用DMA方式接收  
//	USART_DMACmd(USART1,USART_DMAReq_Tx|USART_DMAReq_Rx,ENABLE);  
	
//	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//使能接收中断
	USART_Cmd(USART1, ENABLE);//使能串口1
}



//不使用半主机模式
#if 1 //如果没有这段，则需要在target选项中选择使用USE microLIB
#pragma import(__use_no_semihosting)
struct __FILE  
{  
	int handle;  
};  
FILE __stdout;  

_sys_exit(int x)  
{  
	x = x;  
}
#endif


PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(USART1,(u8)ch);

	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

	return ch;
}
/**
  * @}
  */

/*********************************END OF FILE**********************************/

