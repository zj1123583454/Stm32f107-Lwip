#include "spi.h"

#ifndef NULL
        #define NULL ((void *) 0L)
#endif

#define SPI_SS_N_L	GPIOA->BRR=(1<<4)
#define SPI_SS_N_H	GPIOA->BSRR=(1<<4)

unsigned char SPIx_ReadWriteByte(unsigned char TxData);

//�������Ƕ�SPI1�ĳ�ʼ��
void SPIx_Init(void)
{	 
	RCC->APB2ENR|=1<<2;       //PORTAʱ��ʹ�� 	 
	RCC->APB2ENR|=1<<12;      //SPI1ʱ��ʹ�� 
	/***********************/	   
	GPIOA->CRL	&=0XFFF0FFFF;
	GPIOA->CRL	|=0X00030000;
	GPIOA->ODR	|=1<<4;
	GPIOA->BSRR	|=1<<4;
	/***********************/	
	//����ֻ���SPI�ڳ�ʼ��
	GPIOA->CRL&=0X000FFFFF; 
	GPIOA->CRL|=0XBBB00000;//PA5.6.7���� 	    
	GPIOA->ODR|=0X7<<5;    //PA5.6.7����
		
	SPI1->CR1|=0<<10;//ȫ˫��ģʽ	
	SPI1->CR1|=1<<9; //���nss����
	SPI1->CR1|=1<<8;  

	SPI1->CR1|=1<<2; //SPI����
	SPI1->CR1|=0<<11;//8bit���ݸ�ʽ	
	
	SPI1->CR1|=0<<1; //CPOL=0ʱ����ģʽ��SCKΪ0 
	SPI1->CR1|=0<<0; //��һ��ʱ�ӵ�������,CPHA=0 CPOL=0
	
	SPI1->CR1|=7<<3; //Fsck=Fcpu/256
	SPI1->CR1|=0<<7; //MSBfirst   
	SPI1->CR1|=1<<6; //SPI�豸ʹ��
	SPIx_ReadWriteByte(0xff);//��������		 
}

//SPI �ٶ����ú���
//SpeedSet:
//SPI_SPEED_2   2��Ƶ   (SPI 36M@sys 72M)
//SPI_SPEED_8   8��Ƶ   (SPI 9M@sys 72M)
//SPI_SPEED_16  16��Ƶ  (SPI 4.5M@sys 72M)
//SPI_SPEED_256 256��Ƶ (SPI 281.25K@sys 72M)
void SPIx_SetSpeed(unsigned char SpeedSet)
{
	SPI1->CR1&=0XFFC7;//Fsck=Fcpu/256
	if(SpeedSet==SPI_SPEED_2)//����Ƶ
	{
		SPI1->CR1|=0<<3;//Fsck=Fpclk/2=36Mhz	
	}else if(SpeedSet==SPI_SPEED_8)//�˷�Ƶ 
	{
		SPI1->CR1|=2<<3;//Fsck=Fpclk/8=9Mhz	
	}else if(SpeedSet==SPI_SPEED_16)//ʮ����Ƶ
	{
		SPI1->CR1|=3<<3;//Fsck=Fpclk/16=4.5Mhz
	}else			 	 //256��Ƶ
	{
		SPI1->CR1|=7<<3; //Fsck=Fpclk/256=281.25Khz ����ģʽ
	}
	SPI1->CR1|=1<<6; //SPI�豸ʹ��	  
}


unsigned char SPIx_ReadWriteByte(unsigned char TxData)
{		
	unsigned int retry=0;				 
	while((SPI1->SR&1<<1)==0)//��'y�??�????	
	{
		retry++;
		if(retry>500)return 0;
	}			  
	SPI1->DR=TxData;	 	  //�??��???byte 
	retry=0;
	while((SPI1->SR&1<<0)==0) //��'y?��?���???byte  
	{
		retry++;
		if(retry>500)return 0;
	}	  						    
	return SPI1->DR;          //��??�?�?�?�y?Y				    
}

// ͨ��SPI ������ THM3060 д�� num ���ȸ��ֽ�
void THM3070_SPI_sendbuff(u8 *buf,u16 num)
{
 	if ((buf == NULL)||(num == 0)) 
		return;

	while(num--)
	{
	 	SPIx_ReadWriteByte(*buf++);
	}  
}

// ͨ��SPI ������ THM3060 ���� num ���ȸ��ֽ�
void THM3070_SPI_revbuff(u8 *buf,u16 num)
{
	if ((buf== NULL)||(num ==0)) 
		return;

	while(num--)
	{
		*buf++ = SPIx_ReadWriteByte(0);	
	}
}

void THM3070_SPI_framestart(void)
{
	SPI_SS_N_L;
}

void THM3070_SPI_frameend(void)
{
	SPI_SS_N_H;
}
