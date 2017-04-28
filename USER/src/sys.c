#include "sys.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_flash.h"

//采用如下方法实现执行汇编指令WFI
//CHECK OK
//091209
__asm void WFI_SET(void)
{
	WFI;    
}
__asm void wait()
{
      BX lr
}
//进入待机模式	 
//check ok 
//091202
void Sys_Standby(void)
{
	SCB->SCR|=1<<2;//使能SLEEPDEEP位 (SYS->CTRL)	   
	RCC->APB1ENR|=1<<28;     //使能电源时钟	    
	PWR->CSR|=1<<8;          //设置WKUP用于唤醒
	PWR->CR|=1<<2;           //清除Wake-up 标志
	PWR->CR|=1<<1;           //PDDS置位		  
	WFI_SET();				 //执行WFI指令		 
}	  

//系统软复位
//CHECK OK
//091209
void Sys_Soft_Reset(void)
{   
	SCB->AIRCR =0X05FA0000|(u32)0x04;	  
} 

//JTAG模式设置,用于设置JTAG的模式
//mode:jtag,swd模式设置;00,全使能;01,使能SWD;10,全关闭;
//CHECK OK	
//100818		  
void JTAG_Set(u8 mode)
{
	u32 temp;
	temp=mode;
	temp<<=25;
	RCC->APB2ENR|=1<<0;     //开启辅助时钟	   
	AFIO->MAPR&=0XF8FFFFFF; //清除MAPR的[26:24]
	AFIO->MAPR|=temp;       //设置jtag模式
} 


//void Set_USBClock(void)
//{
//	/* Select USBCLK source */
//	
//	RCC_USBCLKConfig((uint32_t)0x00010000);//RCC_USBCLKSource_PLLCLK_1Div5
//	/* Enable USB clock */
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
//}
//void Open_GPIO_Clock_(void)
//{
//	RCC->APB2ENR|=0x00000005;//打开PA时钟 	辅助时钟
//	RCC->APB2ENR|=1<<3;//打开PB时钟	辅助时钟
////	RCC->APB2ENR|=1<<4;//打开PC时钟	辅助时钟
//}

void OPEN_DMA1_RCC_APB2PeriphClock(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
}

//void RCC_Clock_init(void)
//{
//	Set_USBClock();
////	Open_GPIO_Clock_();
//	OPEN_DMA1_RCC_APB2PeriphClock();
//	JTAG_Set(0);
//}

static volatile ErrorStatus HSEStartUpStatus = SUCCESS;

void STM32_RCC_Config(void)
{
	RCC_DeInit();
	/* Enable HSE */
	RCC_HSEConfig(RCC_HSE_ON);

	/* Wait till HSE is ready */
	HSEStartUpStatus = RCC_WaitForHSEStartUp();

	if(HSEStartUpStatus == SUCCESS)
	{
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

		/* Flash 2 wait state */
		FLASH_SetLatency(FLASH_Latency_2);

		/* HCLK = SYSCLK */
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 

		/* PCLK2 = HCLK */
		RCC_PCLK2Config(RCC_HCLK_Div1); 

		/* PCLK1 = HCLK/2 */
		RCC_PCLK1Config(RCC_HCLK_Div2);

// 		/* ADCCLK = PCLK2/6 */
// 		RCC_ADCCLKConfig(RCC_PCLK2_Div6);

		/* PLLCLK = 8MHz * 9 = 72 MHz */
		RCC_PLLConfig((uint32_t)0x00010000, RCC_PLLMul_9);  //RCC_PLLSource_HSE_Div1

		/* Enable PLL */ 
		RCC_PLLCmd(ENABLE);

		/* Wait till PLL is ready */
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		{
		}

		/* Select PLL as system clock source */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

		/* Wait till PLL is used as system clock source */
		while(RCC_GetSYSCLKSource() != 0x08)
		{
		}
//		RCC_Clock_init();
	}
	/***PLL????? 72M usb 12M ***********/
	/* Enable GPIOD and GPIOE clock */
}

