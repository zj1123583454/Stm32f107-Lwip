#include <stm32f10x.h>
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
//void	GPIOA_Config(void)
//{
//	RCC->APB2ENR|=1<<2;//打开PA口时钟
//	
//	GPIOA->CRH&=0xfffffff0;
//	GPIOA->CRH|=0x00000004;
//}

/*********************
PB13 	TX_FRAME 输入                   changePC7
PB12 	RX_FRAME 推挽输出               changePC6

PB11	I2C SDAT 开漏输出               changePB7
PB10	I2C SCLK 开漏输出								changePB6

PB9 	蜂鸣器
PB8	LED

*********************/
void	GPIOB_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 |GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*RCC->APB2ENR|=1<<3;//打开PB口时钟
	
	GPIOB->CRL	&=0XFFFFFF00;
	GPIOB->CRL	|=0X00000033;
	
	GPIOB->CRH	&=0XFF000000;
	GPIOB->CRH	|=0X00347733;
	
	GPIOB->ODR	|=(3<<0);
	GPIOB->ODR	|=(3<<8);
	GPIOB->ODR	|=(1<<13);
	GPIOB->BRR	=(1<<9); */
}

void	GPIO_Config(void)
{
//	GPIOA_Config();
	GPIOB_Config();
}

