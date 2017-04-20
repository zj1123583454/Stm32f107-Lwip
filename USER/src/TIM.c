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
//	RCC->APB1ENR|=1<<0;//  TIM2ʱ��ʹ��
//	TIM2->ARR=arr;     //  �趨�������Զ�����װ�� 10=1ms 10000=1s
//	TIM2->PSC=psc;     //  Ԥ��Ƶ��7200���õ�10Khz�ļ���ʱ��
//	TIM2->DIER|=1<<0;  //  ��������ж�
//	TIM2->DIER|=1<<6;  //  �������ж�
//	TIM2->CR1|=0x01;   //  ʹ�ܶ�ʱ��2
//	Tim2_NVIC_Config();//�жϷ���
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , DISABLE);		/*�ȹرյȴ�ʹ��*/ 
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		/* ����TIM2CLK Ϊ 72MHZ */
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
    //TIM_DeInit(TIM2);
	
	/* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
  TIM_TimeBaseStructure.TIM_Period=1;
	
    /* �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж� */
	  /* ʱ��Ԥ��Ƶ��Ϊ72 */
  TIM_TimeBaseStructure.TIM_Prescaler= (36000-1);
	
		/* ���ⲿʱ�ӽ��в�����ʱ�ӷ�Ƶ,����û���õ� */
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);				//�����ʱ����־λ
	
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);			//��ʱ��2�жϿ���
		
  TIM_Cmd(TIM2, ENABLE);			
		
	Tim2_NVIC_Config();//�жϷ���
    
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , DISABLE);		/*�ȹرյȴ�ʹ��*/  

}


void Tim3_init(unsigned short int arr,unsigned short int psc)
{
	RCC->APB1ENR|=1<<1;//  TIM3ʱ��ʹ��
	TIM3->ARR=arr;     //  �趨�������Զ�����װ�� 10=1ms 10000=1s
	TIM3->PSC=psc;     //  Ԥ��Ƶ��7200���õ�10Khz�ļ���ʱ��
	TIM3->DIER|=1<<0;  //  ��������ж�
	TIM3->DIER|=1<<6;  //  �������ж�
	TIM3->CR1|=0x01;   //  ʹ�ܶ�ʱ��3
	Tim3_NVIC_Config();//�жϷ���
}

void TIM_Init(void)
{
	Tim2_init(10,7199);
	Tim3_init(2999,7199);
}

