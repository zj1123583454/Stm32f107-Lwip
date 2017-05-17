#include <string.h>
#include "stm32f10x.h"   // Device header
#include "stm32f10x_usart.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "include.h"
#include "uasrt.h"
#include "secure.h"
#include "stm32f10x_exti.h"
#include "stm32_eth.h"
#include "main.h"
#include "netconf.h"
#include "TCPClient.h"
#include "tcp.h"
extern uint8_t TCP_ClientFlag;
extern uint8_t IT_Begin;
extern struct tcp_pcb *Tcp_write;
extern struct echoclient *memtoryES;
uint8_t ConnectTime=0;
/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMIHbitandler(void)
{
}


/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFaultHbitandler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	  if (CoreDebug->DHCSR & 1) {  //check C_DEBUGEN == 1 -> Debugger Connected  
      __breakpoint(0);  // halt program execution here         
  }  
	while (1)
	{
		;
	}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManageHbitandler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFaultHbitandler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFaultHbitandler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVCHbitandler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMonHbitandler(void)
{
}

/**
  * @brief  This function handles PendSVHbitandler exception.
  * @param  None
  * @retval None
  */
void PendSVHbitandler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTickHbitandler(void)
{
}
void SysTick_Handler(void)
{
  /* Update the LocalTime by adding SYSTEMTICK_PERIOD_MS each SysTick interrupt */
  Time_Update();
	ConnectTime+=1;
	if(IT_Begin==BEGIN && ConnectTime>=100)                              
	{
			if(TCP_ClientFlag!=TCP_Connected)
			{
					Tcp_write=tcp_echoclient_connect();
			}
			ConnectTime=0;
	}		
} 
void ETH_IRQHandler(void)
{
  /* Handles all the received frames */	
		while(ETH_GetRxPktSize() != 0) 
		{	
			LwIP_Pkt_Handle();
		}
	
  /* Clear the Eth DMA Rx IT pending bits */
  ETH_DMAClearITPendingBit(ETH_DMA_IT_R);
  ETH_DMAClearITPendingBit(ETH_DMA_IT_NIS);
}

