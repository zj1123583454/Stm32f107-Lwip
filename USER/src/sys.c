#include "sys.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_flash.h"

//�������·���ʵ��ִ�л��ָ��WFI
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
//�������ģʽ	 
//check ok 
//091202
void Sys_Standby(void)
{
	SCB->SCR|=1<<2;//ʹ��SLEEPDEEPλ (SYS->CTRL)	   
	RCC->APB1ENR|=1<<28;     //ʹ�ܵ�Դʱ��	    
	PWR->CSR|=1<<8;          //����WKUP���ڻ���
	PWR->CR|=1<<2;           //���Wake-up ��־
	PWR->CR|=1<<1;           //PDDS��λ		  
	WFI_SET();				 //ִ��WFIָ��		 
}	  

//ϵͳ��λ
//CHECK OK
//091209
void Sys_Soft_Reset(void)
{   
	SCB->AIRCR =0X05FA0000|(u32)0x04;	  
} 

//JTAGģʽ����,��������JTAG��ģʽ
//mode:jtag,swdģʽ����;00,ȫʹ��;01,ʹ��SWD;10,ȫ�ر�;
//CHECK OK	
//100818		  
void JTAG_Set(u8 mode)
{
	u32 temp;
	temp=mode;
	temp<<=25;
	RCC->APB2ENR|=1<<0;     //��������ʱ��	   
	AFIO->MAPR&=0XF8FFFFFF; //���MAPR��[26:24]
	AFIO->MAPR|=temp;       //����jtagģʽ
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
//	RCC->APB2ENR|=0x00000005;//��PAʱ�� 	����ʱ��
//	RCC->APB2ENR|=1<<3;//��PBʱ��	����ʱ��
////	RCC->APB2ENR|=1<<4;//��PCʱ��	����ʱ��
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

