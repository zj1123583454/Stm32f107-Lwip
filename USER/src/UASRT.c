#include "stm32f10x_usart.h"
#include "stm32f10x_dma.h"
#include "misc.h"
#include "uasrt.h"
#include "include.h"

#include <stdio.h>
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "usart.h"
//#define	LENG	10
//#define	UASRTLENG	15

//volatile bool Uasrt1_tx_falg=0;
//volatile bool Uasrt2_tx_falg=0;

//unsigned char uasrt1_rxBuffer[UART_RX_LEN]={0};
//unsigned char uasrt1_txBuffer[LENG]={0};

//unsigned char uasrt2_rxBuffer[UART_RX_LEN]={0};
//unsigned char uasrt2_txBuffer[UART_RX_LEN]={0};

//extern unsigned char	buf[200];


//void DMA1_Channel4_Configuration(void)
//{
//	DMA_InitTypeDef DMA_InitStructure;
//	NVIC_InitTypeDef 	NVIC_InitStructure;
//	//---------------------串口功能配置---------------------   
//    //启动DMA时钟  
//    RCC->AHBENR	|=1<<0;		//使能DMA时钟
//    //DMA发送中断设置  
//    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;  
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
//    NVIC_Init(&NVIC_InitStructure);  
//    //DMA1通道4配置  
//    DMA_DeInit(DMA1_Channel4);  
//    //外设地址  
//    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);  
//    //内存地址  
//    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)uasrt1_txBuffer;  
//    //dma传输方向单向  
//    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  
//    //设置DMA在传输时缓冲区的长度  
//    DMA_InitStructure.DMA_BufferSize = UART_RX_LEN;  
//    //设置DMA的外设递增模式，一个外设  
//    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
//    //设置DMA的内存递增模式  
//    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
//    //外设数据字长  
//    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
//    //内存数据字长  
//    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;  
//    //设置DMA的传输模式  
//    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA_Mode_Circular DMA_Mode_Normal
//    //设置DMA的优先级别  
//    DMA_InitStructure.DMA_Priority = DMA_Priority_High;  
//    //设置DMA的2个memory中的变量互相访问  
//    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  
//    DMA_Init(DMA1_Channel4,&DMA_InitStructure);  
//    DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);  
//      
//    //使能通道4  
//    //DMA_Cmd(DMA1_Channel4, ENABLE);
//}

//void DMA1_Channel5_Configuration(void)
//{
//	DMA_InitTypeDef DMA_InitStructure;
//	//串口收DMA配置    
//    //启动DMA时钟  
//    RCC->AHBENR	|=1<<0;		//使能DMA时钟
//    //DMA1通道5配置  
//    DMA_DeInit(DMA1_Channel5);  
//    //外设地址  
//    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);  
//    //内存地址  
//    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)uasrt1_rxBuffer;  
//    //dma传输方向单向  
//    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  
//    //设置DMA在传输时缓冲区的长度  
//    DMA_InitStructure.DMA_BufferSize = UART_RX_LEN;  
//    //设置DMA的外设递增模式，一个外设  
//    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
//    //设置DMA的内存递增模式  
//    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
//    //外设数据字长  
//    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
//    //内存数据字长  
//    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  
//    //设置DMA的传输模式  
//    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  
//    //设置DMA的优先级别  
//    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  
//    //设置DMA的2个memory中的变量互相访问  
//    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  
//    DMA_Init(DMA1_Channel5,&DMA_InitStructure);  
// 
//    //使能通道5  
//    DMA_Cmd(DMA1_Channel5,ENABLE);
//}


//void DMA1_Channel7_Configuration(void)
//{
//	DMA_InitTypeDef DMA_InitStructure;
//	
//	//??DMA??  
//    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);  
//    //DMA1??5??  
//    DMA_DeInit(DMA1_Channel7);  
//    //????  
//    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART2->DR);  
//    //????  
//    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)buf;  
//    //dma??????  
//    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  
//    //??DMA??????????  
//    DMA_InitStructure.DMA_BufferSize = UART_RX_LEN;  
//    //??DMA???????,????  
//    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
//    //??DMA???????  
//    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
//    //??????  
//    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
//    //??????  
//    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  
//    //??DMA?????  
//    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  
//    //??DMA?????  
//    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  
//    //??DMA?2?memory????????  
//    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  
//    DMA_Init(DMA1_Channel7,&DMA_InitStructure);  
//  
//    //????5  
////    DMA_Cmd(DMA1_Channel7,ENABLE);  
//      
//	
//	
////	//	NVIC_InitTypeDef 	NVIC_InitStructure;
////	//---------------------串口功能配置---------------------   
////    //启动DMA时钟  
////    RCC->AHBENR	|=1<<0;		//使能DMA时钟
////    //DMA发送中断设置  
//////    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel7_IRQn;  
//////    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  
//////    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  
//////    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
//////    NVIC_Init(&NVIC_InitStructure);  
////    //DMA1通道4配置  
////    DMA_DeInit(DMA1_Channel7);  
////    //外设地址  
////    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART2->DR);  
////    //内存地址  
////    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)uasrt2_txBuffer;  
////    //dma传输方向单向  
////    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  
////    //设置DMA在传输时缓冲区的长度  
////    DMA_InitStructure.DMA_BufferSize = UART_RX_LEN;  
////    //设置DMA的外设递增模式，一个外设  
////    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
////    //设置DMA的内存递增模式  
////    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
////    //外设数据字长  
////    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
////    //内存数据字长  
////    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;  
////    //设置DMA的传输模式  
////    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//DMA_Mode_Circular DMA_Mode_Normal
////    //设置DMA的优先级别  
////    DMA_InitStructure.DMA_Priority = DMA_Priority_High;  
////    //设置DMA的2个memory中的变量互相访问  
////    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  
////    DMA_Init(DMA1_Channel7,&DMA_InitStructure);  
//////    DMA_ITConfig(DMA1_Channel7,DMA_IT_TC,ENABLE);  
////      
////    //使能通道7
////    DMA_Cmd(DMA1_Channel7, ENABLE);
//}

//void DMA1_Channel6_Configuration(void)
//{
//	DMA_InitTypeDef DMA_InitStructure;
//	//串口收DMA配置    
//    //启动DMA时钟  
//    RCC->AHBENR	|=1<<0;		//使能DMA时钟
//    //DMA1通道6配置  	通道6是串口2的接收DMA通道
//    DMA_DeInit(DMA1_Channel6);  
//    //外设地址  
//    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART2->DR);  
//    //内存地址  
//    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)uasrt2_rxBuffer;  
//    //dma传输方向单向  	传输方向为外设到内存
//    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  
//    //设置DMA在传输时缓冲区的长度  
//    DMA_InitStructure.DMA_BufferSize = UART_RX_LEN;  
//    //设置DMA的外设递增模式，一个外设  
//    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
//    //设置DMA的内存递增模式  
//    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
//    //外设数据字长  
//    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
//    //内存数据字长  
//    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  
//    //设置DMA的传输模式  
//    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  
//    //设置DMA的优先级别  
//    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  
//    //设置DMA的2个memory中的变量互相访问  
//    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  
//    DMA_Init(DMA1_Channel6,&DMA_InitStructure);  
// 
//    //使能通道6  
//    DMA_Cmd(DMA1_Channel6,ENABLE);
//}

void UASRT1_Config(void)
{	
	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef 	NVIC_InitStructure;

	RCC->APB2ENR|=1<<2;   	//使能PORTA口时钟  
	RCC->APB2ENR|=1<<14;  	//使能串口时钟
//	AFIO->MAPR	|=1<<2;		//串口I/O映射到PB6 PB7

//	GPIOA->CRH&=0XFFFFF00F; 
//	GPIOA->CRH|=0X000008B0;//IO状态设置

//	//初始化参数    
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;    
	USART_InitStructure.USART_StopBits = USART_StopBits_1;    
	USART_InitStructure.USART_Parity = USART_Parity_No;    
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;    
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;      

	//初始化串口   
	USART_Init(USART1,&USART_InitStructure);    
//	//TXE发送中断,TC传输完成中断,RXNE接收中断,PE奇偶错误中断,可以是多个     
//	//USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);  

//	//中断配置  
//	USART_ITConfig(USART1,USART_IT_TC,DISABLE);  
//	USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);  
//	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);    

//	//配置UART1中断    
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);  
//	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;               //通道设置为串口1中断    
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;       //中断占先等级0    
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;              //中断响应优先级0    
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //打开中断    
//	NVIC_Init(&NVIC_InitStructure);     
//	 
//	//采用DMA方式发送  采用DMA方式接收  
//	USART_DMACmd(USART1,USART_DMAReq_Tx|USART_DMAReq_Rx,ENABLE);  
//	
//	//启动串口    
	USART_Cmd(USART1, ENABLE);  
}

//void UASRT2_Config(void)
//{	
//	GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure; 
//	/* Configure the NVIC Preemption Priority Bits */  
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

//	/* config USART2 clock */
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

//	/* USART2 GPIO config */
//   /* Configure USART2 Tx (PA.02) as alternate function push-pull */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//	    
//  /* Configure USART2 Rx (PA.03) as input floating */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//	  
//	/* USART2 mode config */
//	USART_InitStructure.USART_BaudRate = 115200;
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	USART_InitStructure.USART_Parity = USART_Parity_No ;
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

////	USART_Init(USART2, &USART_InitStructure);
//////	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);		//  串口2接收中断
////	//中断配置  
////	USART_ITConfig(USART2,USART_IT_TC,DISABLE);  
////	USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);  
////	USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);  
////	
////	//采用DMA方式接收  
////	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);  
////  USART_Cmd(USART2, ENABLE);
////	
////	
////	/* Enable the USART2 Interrupt */
////	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;	 
////	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
////	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
////	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
////	NVIC_Init(&NVIC_InitStructure);

////	GPIO_InitTypeDef GPIO_InitStructure;
////	USART_InitTypeDef USART_InitStructure;

////	/* config USART2 clock */
////	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
////	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

////	/* USART2 GPIO config */
////   /* Configure USART2 Tx (PA.02) as alternate function push-pull */
////  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
////  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
////  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////  GPIO_Init(GPIOA, &GPIO_InitStructure);
////	    
////  /* Configure USART2 Rx (PA.03) as input floating */
////  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
////  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
////  GPIO_Init(GPIOA, &GPIO_InitStructure);
////	  
////	/* USART2 mode config */
////	USART_InitStructure.USART_BaudRate = 115200;
////	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
////	USART_InitStructure.USART_StopBits = USART_StopBits_1;
////	USART_InitStructure.USART_Parity = USART_Parity_No ;
////	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
////	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

////	USART_Init(USART2, &USART_InitStructure); 
////  USART_Cmd(USART2, ENABLE);
//	
//}

//u8 Uart2SendByte(u8 ch)
//{
//  USART_SendData(USART2,ch);
//  while ( USART_GetFlagStatus(USART2,USART_FLAG_TXE) == RESET)
//  {
//  }
//  return ch;
//}

//void Uart2SendString(u8 *bb,u16 length)
//{

//	while(length)
//	{
//		Uart2SendByte(*bb++);
//		length--;		
//	}
//}

//unsigned char Uart2RevData(void)
//{
//	u8 c2;
//	c2 = USART_ReceiveData(USART2);
//	while( USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET );
//	return c2;
//}


//void	Uasrt1endData(void)
//{
//	Uasrt1_tx_falg=1;
//	DMA1_Channel4->CCR|=DMA_CCR4_EN;//使能DMA1的通道4
//	while(Uasrt1_tx_falg);
//}

////void	Uasrt2endData(void)
////{
////	Uasrt2_tx_falg=1;
////	DMA_SetCurrDataCounter(DMA1_Channel7,UASRT_Send_Flag.value);
////	DMA1_Channel7->CCR|=DMA_CCR7_EN;//使能DMA1的通道7
////	UASRT_Send_Flag.value=0;
////	while(Uasrt2_tx_falg);
////}

//void USART_Iint(void)
//{
////	DMA1_Channel4_Configuration();
////	DMA1_Channel5_Configuration();
////	DMA1_Channel6_Configuration();
////	DMA1_Channel7_Configuration();
////	USART_Configuration();
//	//UASRT1_Config();__NOP();
//	//UASRT2_Config();__NOP();
//}
