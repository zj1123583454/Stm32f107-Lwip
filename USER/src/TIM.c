#include "stm32f10x_tim.h"
#include "misc.h"
#include "stm32f10x_rcc.h"

void Tim2_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);	
//	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  													
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	  
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void Tim3_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void Tim2_init(unsigned short int arr,unsigned short int psc)
{
//	RCC->APB1ENR|=1<<0;//  TIM2时钟使能
//	TIM2->ARR=arr;     //  设定计数器自动重新装载 10=1ms 10000=1s
//	TIM2->PSC=psc;     //  预分频器7200，得到10Khz的计数时钟
//	TIM2->DIER|=1<<0;  //  允许更新中断
//	TIM2->DIER|=1<<6;  //  允许触发中断
//	TIM2->CR1|=0x01;   //  使能定时器2
//	Tim2_NVIC_Config();//中断分组
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , DISABLE);		/*先关闭等待使用*/ 
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		/* 设置TIM2CLK 为 72MHZ */
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
    //TIM_DeInit(TIM2);
	
	/* 自动重装载寄存器周期的值(计数值) */
  TIM_TimeBaseStructure.TIM_Period=1;
	
    /* 累计 TIM_Period个频率后产生一个更新或者中断 */
	  /* 时钟预分频数为72 */
  TIM_TimeBaseStructure.TIM_Prescaler= (36000-1);
	
		/* 对外部时钟进行采样的时钟分频,这里没有用到 */
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);				//清除定时器标志位
	
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);			//定时器2中断开启
		
  TIM_Cmd(TIM2, ENABLE);			
		
	Tim2_NVIC_Config();//中断分组
    
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , DISABLE);		/*先关闭等待使用*/  

}


void Tim3_init(unsigned short int arr,unsigned short int psc)
{
	RCC->APB1ENR|=1<<1;//  TIM3时钟使能
	TIM3->ARR=arr;     //  设定计数器自动重新装载 10=1ms 10000=1s
	TIM3->PSC=psc;     //  预分频器7200，得到10Khz的计数时钟
	TIM3->DIER|=1<<0;  //  允许更新中断
	TIM3->DIER|=1<<6;  //  允许触发中断
	TIM3->CR1|=0x01;   //  使能定时器3
	Tim3_NVIC_Config();//中断分组
}

void TIM_Init(void)
{
	Tim2_init(10,7199);
	Tim3_init(2999,7199);
}

