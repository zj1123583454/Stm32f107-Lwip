#include "spi.h"

#ifndef NULL
        #define NULL ((void *) 0L)
#endif

#define SPI_SS_N_L	GPIOA->BRR=(1<<4)
#define SPI_SS_N_H	GPIOA->BSRR=(1<<4)

unsigned char SPIx_ReadWriteByte(unsigned char TxData);

//这里针是对SPI1的初始化
void SPIx_Init(void)
{	 
	RCC->APB2ENR|=1<<2;       //PORTA时钟使能 	 
	RCC->APB2ENR|=1<<12;      //SPI1时钟使能 
	/***********************/	   
	GPIOA->CRL	&=0XFFF0FFFF;
	GPIOA->CRL	|=0X00030000;
	GPIOA->ODR	|=1<<4;
	GPIOA->BSRR	|=1<<4;
	/***********************/	
	//这里只针对SPI口初始化
	GPIOA->CRL&=0X000FFFFF; 
	GPIOA->CRL|=0XBBB00000;//PA5.6.7复用 	    
	GPIOA->ODR|=0X7<<5;    //PA5.6.7上拉
		
	SPI1->CR1|=0<<10;//全双工模式	
	SPI1->CR1|=1<<9; //软件nss管理
	SPI1->CR1|=1<<8;  

	SPI1->CR1|=1<<2; //SPI主机
	SPI1->CR1|=0<<11;//8bit数据格式	
	
	SPI1->CR1|=0<<1; //CPOL=0时空闲模式下SCK为0 
	SPI1->CR1|=0<<0; //第一个时钟的上升沿,CPHA=0 CPOL=0
	
	SPI1->CR1|=7<<3; //Fsck=Fcpu/256
	SPI1->CR1|=0<<7; //MSBfirst   
	SPI1->CR1|=1<<6; //SPI设备使能
	SPIx_ReadWriteByte(0xff);//启动传输		 
}

//SPI 速度设置函数
//SpeedSet:
//SPI_SPEED_2   2分频   (SPI 36M@sys 72M)
//SPI_SPEED_8   8分频   (SPI 9M@sys 72M)
//SPI_SPEED_16  16分频  (SPI 4.5M@sys 72M)
//SPI_SPEED_256 256分频 (SPI 281.25K@sys 72M)
void SPIx_SetSpeed(unsigned char SpeedSet)
{
	SPI1->CR1&=0XFFC7;//Fsck=Fcpu/256
	if(SpeedSet==SPI_SPEED_2)//二分频
	{
		SPI1->CR1|=0<<3;//Fsck=Fpclk/2=36Mhz	
	}else if(SpeedSet==SPI_SPEED_8)//八分频 
	{
		SPI1->CR1|=2<<3;//Fsck=Fpclk/8=9Mhz	
	}else if(SpeedSet==SPI_SPEED_16)//十六分频
	{
		SPI1->CR1|=3<<3;//Fsck=Fpclk/16=4.5Mhz
	}else			 	 //256分频
	{
		SPI1->CR1|=7<<3; //Fsck=Fpclk/256=281.25Khz 低速模式
	}
	SPI1->CR1|=1<<6; //SPI设备使能	  
}


unsigned char SPIx_ReadWriteByte(unsigned char TxData)
{		
	unsigned int retry=0;				 
	while((SPI1->SR&1<<1)==0)//佃'y�??�????	
	{
		retry++;
		if(retry>500)return 0;
	}			  
	SPI1->DR=TxData;	 	  //�??眚???byte 
	retry=0;
	while((SPI1->SR&1<<0)==0) //佃'y?箨?黻�???byte  
	{
		retry++;
		if(retry>500)return 0;
	}	  						    
	return SPI1->DR;          //返??�?�?�?陏?Y				    
}

// 通过SPI 总线向 THM3060 写入 num 长度个字节
void THM3070_SPI_sendbuff(u8 *buf,u16 num)
{
 	if ((buf == NULL)||(num == 0)) 
		return;

	while(num--)
	{
	 	SPIx_ReadWriteByte(*buf++);
	}  
}

// 通过SPI 总线向 THM3060 读出 num 长度个字节
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
