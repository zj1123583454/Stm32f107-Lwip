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
//	//---------------------���ڹ�������---------------------   
//    //����DMAʱ��  
//    RCC->AHBENR	|=1<<0;		//ʹ��DMAʱ��
//    //DMA�����ж�����  
//    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;  
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
//    NVIC_Init(&NVIC_InitStructure);  
//    //DMA1ͨ��4����  
//    DMA_DeInit(DMA1_Channel4);  
//    //�����ַ  
//    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);  
//    //�ڴ��ַ  
//    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)uasrt1_txBuffer;  
//    //dma���䷽����  
//    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  
//    //����DMA�ڴ���ʱ�������ĳ���  
//    DMA_InitStructure.DMA_BufferSize = UART_RX_LEN;  
//    //����DMA���������ģʽ��һ������  
//    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
//    //����DMA���ڴ����ģʽ  
//    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
//    //���������ֳ�  
//    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
//    //�ڴ������ֳ�  
//    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;  
//    //����DMA�Ĵ���ģʽ  
//    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA_Mode_Circular DMA_Mode_Normal
//    //����DMA�����ȼ���  
//    DMA_InitStructure.DMA_Priority = DMA_Priority_High;  
//    //����DMA��2��memory�еı����������  
//    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  
//    DMA_Init(DMA1_Channel4,&DMA_InitStructure);  
//    DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);  
//      
//    //ʹ��ͨ��4  
//    //DMA_Cmd(DMA1_Channel4, ENABLE);
//}

//void DMA1_Channel5_Configuration(void)
//{
//	DMA_InitTypeDef DMA_InitStructure;
//	//������DMA����    
//    //����DMAʱ��  
//    RCC->AHBENR	|=1<<0;		//ʹ��DMAʱ��
//    //DMA1ͨ��5����  
//    DMA_DeInit(DMA1_Channel5);  
//    //�����ַ  
//    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);  
//    //�ڴ��ַ  
//    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)uasrt1_rxBuffer;  
//    //dma���䷽����  
//    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  
//    //����DMA�ڴ���ʱ�������ĳ���  
//    DMA_InitStructure.DMA_BufferSize = UART_RX_LEN;  
//    //����DMA���������ģʽ��һ������  
//    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
//    //����DMA���ڴ����ģʽ  
//    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
//    //���������ֳ�  
//    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
//    //�ڴ������ֳ�  
//    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  
//    //����DMA�Ĵ���ģʽ  
//    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  
//    //����DMA�����ȼ���  
//    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  
//    //����DMA��2��memory�еı����������  
//    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  
//    DMA_Init(DMA1_Channel5,&DMA_InitStructure);  
// 
//    //ʹ��ͨ��5  
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
////	//---------------------���ڹ�������---------------------   
////    //����DMAʱ��  
////    RCC->AHBENR	|=1<<0;		//ʹ��DMAʱ��
////    //DMA�����ж�����  
//////    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel7_IRQn;  
//////    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  
//////    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  
//////    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
//////    NVIC_Init(&NVIC_InitStructure);  
////    //DMA1ͨ��4����  
////    DMA_DeInit(DMA1_Channel7);  
////    //�����ַ  
////    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART2->DR);  
////    //�ڴ��ַ  
////    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)uasrt2_txBuffer;  
////    //dma���䷽����  
////    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  
////    //����DMA�ڴ���ʱ�������ĳ���  
////    DMA_InitStructure.DMA_BufferSize = UART_RX_LEN;  
////    //����DMA���������ģʽ��һ������  
////    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
////    //����DMA���ڴ����ģʽ  
////    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
////    //���������ֳ�  
////    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
////    //�ڴ������ֳ�  
////    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;  
////    //����DMA�Ĵ���ģʽ  
////    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//DMA_Mode_Circular DMA_Mode_Normal
////    //����DMA�����ȼ���  
////    DMA_InitStructure.DMA_Priority = DMA_Priority_High;  
////    //����DMA��2��memory�еı����������  
////    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  
////    DMA_Init(DMA1_Channel7,&DMA_InitStructure);  
//////    DMA_ITConfig(DMA1_Channel7,DMA_IT_TC,ENABLE);  
////      
////    //ʹ��ͨ��7
////    DMA_Cmd(DMA1_Channel7, ENABLE);
//}

//void DMA1_Channel6_Configuration(void)
//{
//	DMA_InitTypeDef DMA_InitStructure;
//	//������DMA����    
//    //����DMAʱ��  
//    RCC->AHBENR	|=1<<0;		//ʹ��DMAʱ��
//    //DMA1ͨ��6����  	ͨ��6�Ǵ���2�Ľ���DMAͨ��
//    DMA_DeInit(DMA1_Channel6);  
//    //�����ַ  
//    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART2->DR);  
//    //�ڴ��ַ  
//    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)uasrt2_rxBuffer;  
//    //dma���䷽����  	���䷽��Ϊ���赽�ڴ�
//    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  
//    //����DMA�ڴ���ʱ�������ĳ���  
//    DMA_InitStructure.DMA_BufferSize = UART_RX_LEN;  
//    //����DMA���������ģʽ��һ������  
//    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
//    //����DMA���ڴ����ģʽ  
//    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
//    //���������ֳ�  
//    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
//    //�ڴ������ֳ�  
//    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  
//    //����DMA�Ĵ���ģʽ  
//    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  
//    //����DMA�����ȼ���  
//    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  
//    //����DMA��2��memory�еı����������  
//    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  
//    DMA_Init(DMA1_Channel6,&DMA_InitStructure);  
// 
//    //ʹ��ͨ��6  
//    DMA_Cmd(DMA1_Channel6,ENABLE);
//}

void UASRT1_Config(void)
{	
	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef 	NVIC_InitStructure;

	RCC->APB2ENR|=1<<2;   	//ʹ��PORTA��ʱ��  
	RCC->APB2ENR|=1<<14;  	//ʹ�ܴ���ʱ��
//	AFIO->MAPR	|=1<<2;		//����I/Oӳ�䵽PB6 PB7

//	GPIOA->CRH&=0XFFFFF00F; 
//	GPIOA->CRH|=0X000008B0;//IO״̬����

//	//��ʼ������    
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;    
	USART_InitStructure.USART_StopBits = USART_StopBits_1;    
	USART_InitStructure.USART_Parity = USART_Parity_No;    
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;    
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;      

	//��ʼ������   
	USART_Init(USART1,&USART_InitStructure);    
//	//TXE�����ж�,TC��������ж�,RXNE�����ж�,PE��ż�����ж�,�����Ƕ��     
//	//USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);  

//	//�ж�����  
//	USART_ITConfig(USART1,USART_IT_TC,DISABLE);  
//	USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);  
//	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);    

//	//����UART1�ж�    
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);  
//	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;               //ͨ������Ϊ����1�ж�    
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;       //�ж�ռ�ȵȼ�0    
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;              //�ж���Ӧ���ȼ�0    
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //���ж�    
//	NVIC_Init(&NVIC_InitStructure);     
//	 
//	//����DMA��ʽ����  ����DMA��ʽ����  
//	USART_DMACmd(USART1,USART_DMAReq_Tx|USART_DMAReq_Rx,ENABLE);  
//	
//	//��������    
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
//////	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);		//  ����2�����ж�
////	//�ж�����  
////	USART_ITConfig(USART2,USART_IT_TC,DISABLE);  
////	USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);  
////	USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);  
////	
////	//����DMA��ʽ����  
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
//	DMA1_Channel4->CCR|=DMA_CCR4_EN;//ʹ��DMA1��ͨ��4
//	while(Uasrt1_tx_falg);
//}

////void	Uasrt2endData(void)
////{
////	Uasrt2_tx_falg=1;
////	DMA_SetCurrDataCounter(DMA1_Channel7,UASRT_Send_Flag.value);
////	DMA1_Channel7->CCR|=DMA_CCR7_EN;//ʹ��DMA1��ͨ��7
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
