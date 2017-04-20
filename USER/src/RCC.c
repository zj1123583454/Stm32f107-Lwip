// #include "stm32f10x.h"
// #include "stm32f10x_flash.h"

// static volatile ErrorStatus HSEStartUpStatus = SUCCESS;

// void STM32_RCC_PEIZHI(void)
// {
// 	RCC_DeInit();
// 	/* Enable HSE */
// 	RCC_HSEConfig(RCC_HSE_ON);

// 	/* Wait till HSE is ready */
// 	HSEStartUpStatus = RCC_WaitForHSEStartUp();

// 	if(HSEStartUpStatus == SUCCESS)
// 	{
// 		/* Enable Prefetch Buffer */
// 		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

// 		/* Flash 2 wait state */
// 		FLASH_SetLatency(FLASH_Latency_2);

// 		/* HCLK = SYSCLK */
// 		RCC_HCLKConfig(RCC_SYSCLK_Div1); 

// 		/* PCLK2 = HCLK */
// 		RCC_PCLK2Config(RCC_HCLK_Div1); 

// 		/* PCLK1 = HCLK/2 */
// 		RCC_PCLK1Config(RCC_HCLK_Div2);

// // 		/* ADCCLK = PCLK2/6 */
// // 		RCC_ADCCLKConfig(RCC_PCLK2_Div6);

// 		/* PLLCLK = 8MHz * 9 = 72 MHz */
// 		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

// 		/* Enable PLL */ 
// 		RCC_PLLCmd(ENABLE);

// 		/* Wait till PLL is ready */
// 		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
// 		{
// 		}

// 		/* Select PLL as system clock source */
// 		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

// 		/* Wait till PLL is used as system clock source */
// 		while(RCC_GetSYSCLKSource() != 0x08)
// 		{
// 		}
// 	}
// 	/***PLL为系统时钟 72M usb 12M ***********/
// 	/* Enable GPIOD and GPIOE clock */
// }

// void OPEN_GPIOA_RCC_APB2PeriphClock(void)
// {
// 	/*使能串口1使用的GPIOA时钟*/
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO , ENABLE);	
// }

// void OPEN_GPIOB_RCC_APB2PeriphClock(void)
// {
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
// }

// void OPEN_GPIOC_RCC_APB2PeriphClock(void)
// {
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
// }

// void OPEN_GPIOD_RCC_APB2PeriphClock(void)
// {
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
// }

// void OPEN_GPIOE_RCC_APB2PeriphClock(void)
// {
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
// }

// void OPEN_USART1_RCC_APB2PeriphClock(void)
// {
// 	/*使能串口1时钟*/
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);  
// }

// void Set_USBClock(void)
// {
// 	/* Select USBCLK source */
// 	RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
// 	/* Enable USB clock */
// 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
// }

// void OPEN_DMA1_RCC_APB2PeriphClock(void)
// {
// 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
// }

// void ARC_RCC_init(void)
// {
// 	STM32_RCC_PEIZHI();
// 	Set_USBClock();
// 	OPEN_GPIOA_RCC_APB2PeriphClock();
// 	OPEN_GPIOB_RCC_APB2PeriphClock();
// 	OPEN_GPIOC_RCC_APB2PeriphClock();
// 	OPEN_GPIOD_RCC_APB2PeriphClock();
// 	OPEN_GPIOE_RCC_APB2PeriphClock();
// 	OPEN_USART1_RCC_APB2PeriphClock();
// 	OPEN_DMA1_RCC_APB2PeriphClock();
// }
