//��ȫģ�����ݽ��շ��ͳ���,���� I2C �ӿ�ģʽ//
//�������Ϊʾ������,����Щ�źŵ��ж�δ�ӳ�ʱ�ж�
	 
#include "stm32f10x.h"                  // Device header
#include "secure.h"
#include "delay.h"
#include "stm32f10x_gpio.h"
void delay_nop(void)
{
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
}

void init_i2c(void)
{
RX_FRAME_L;
SCLK_H;   
SDAT_H;
}

extern unsigned char  read_sec(unsigned char  * dat)
{
	unsigned char len,temp;
	len =0;
	// �ȴ���������
	while(TX_FRAME==0);
	while (SCLK);
	// ��ʼ��������,��������ݽϿ�,���Բ���ÿ��bit ˳�����,δ����ѭ���ķ���
	while (TX_FRAME)
   {
		temp =0x00;			
		{ 			
			while(!SCLK); 			
			if (SDAT)
				temp = temp | 0x80;
			while(SCLK)
			{
				if (!TX_FRAME) goto retn;
			}
		}
		{    
			while(!SCLK);//while(!SCLK); 			
			if (SDAT)
				temp = temp | 0x40;
			while(SCLK)
			{
				if (!TX_FRAME) goto retn;
			}
		}
		{    
			while(!(SCLK)); 			
			if (SDAT)
				temp = temp | 0x20;
			while(SCLK)
			{
				if (!TX_FRAME) goto retn;
			}
		}
		{    
			while(!(SCLK)); 			
			if (SDAT)
				temp = temp | 0x10;
			while(SCLK)
			{
				if (!TX_FRAME) goto retn;
			}
		}	
		{    
			while(!(SCLK)); 			
			if (SDAT)
				temp = temp | 0x08;
			while(SCLK)
			{
				if (!TX_FRAME) goto retn;
			}
		}	
		{    
			while(!(SCLK)); 			
			if (SDAT)
				temp = temp | 0x04;
			while(SCLK)
			{
				if (!TX_FRAME) goto retn;
			}
		}			
	   {    
			while(!(SCLK)); 			
			if (SDAT)
				temp = temp | 0x02;
			while(SCLK)
			{
				if (!TX_FRAME) goto retn;
			}
		}	
		{    
			while(!(SCLK)); 			
			if (SDAT)
				temp = temp | 0x01;
			while(SCLK)
			{
				if (!TX_FRAME) goto retn;
			}
		}
		delay_nop();
		SDAT_L;//SDAT =0;
		while(!(SCLK));
		*dat =temp;
		while(SCLK)
		{
			if (!TX_FRAME) goto retn;
		}	
		SDAT_H;//SDAT =1; 	
		dat++;
		len++;
   }
retn:
   SDAT_H;//SDAT =1;SCLK =1;
	SCLK_H;
   return len;
}


// 	Send data To Secure Module
extern void  write_sec(unsigned char * dat,unsigned short len)
{
	unsigned char temp,i,bak;

	// ��ʼ��������
	RX_FRAME_H;

	delay_nop();
	SDAT_L;
	delay_nop();
	SCLK_L;
	while (len--)
	{
		bak =*dat;
		temp =0x80;	
		for (i=0;i<8;i++)
		{    
			if (bak & temp)
			{
				SDAT_H;
			}
			else
			{
				SDAT_L;
			}
			temp >>= 1;		
			SCLK_H;
			delay_nop();
			SCLK_L;
			delay_nop();				
		}
		SDAT_H;
		delay_nop();
		SCLK_H;
		delay_nop();
		SCLK_L;
		dat++;	
	}
	SCLK_H;
	SDAT_H;
	RX_FRAME_L;
}
