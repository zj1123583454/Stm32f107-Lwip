#include <stm32f10x.h>
#include "delay.h"
// //Mini STM32������
// //ʹ��SysTick����ͨ����ģʽ���ӳٽ��й���
// //����delay_us,delay_ms
// 	 
static u8  fac_us=0;//us��ʱ������
static u16 fac_ms=0;//ms��ʱ������
// //��ʼ���ӳٺ���
// //SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
// //SYSCLK:ϵͳʱ��
void delay_init(unsigned char SYSCLK)
{
	SysTick->CTRL&=0xfffffffb;//bit2���,ѡ���ⲿʱ��  HCLK/8
	fac_us=SYSCLK/8;		    
	fac_ms=(u16)fac_us*1000;
}								    
//��ʱnms
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��72M������,nms<=1864 
void delay_ms(unsigned short nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           //��ռ�����
	SysTick->CTRL=0x01 ;          //��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	  	    
}

//��ʱnus
//nusΪҪ��ʱ��us��.		    								   
void delay_us(unsigned int nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //ʱ�����	  		 
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL=0x01 ;      //��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	 
}
void Delay(unsigned int nCount)
{
  for(; nCount != 0; nCount--);
}

void Delay_ms(uint32_t time)
{        
			 u16 i=0;      
			 while(time--)    
				 {        
					 i=12000;  //????       
					 while(i--);         
					} 
}
