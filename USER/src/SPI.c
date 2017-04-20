#include "spi.h"

#ifndef NULL
        #define NULL ((void *) 0L)
#endif

#define SPI_SS_N_L	GPIOA->BRR=(1<<4)
#define SPI_SS_N_H	GPIOA->BSRR=(1<<4)

unsigned char SPIx_ReadWriteByte(unsigned char TxData);

//ÕâÀïÕëÊÇ¶ÔSPI1µÄ³õÊ¼»¯
void SPIx_Init(void)
{	 
	RCC->APB2ENR|=1<<2;       //PORTAÊ±ÖÓÊ¹ÄÜ 	 
	RCC->APB2ENR|=1<<12;      //SPI1Ê±ÖÓÊ¹ÄÜ 
	/***********************/	   
	GPIOA->CRL	&=0XFFF0FFFF;
	GPIOA->CRL	|=0X00030000;
	GPIOA->ODR	|=1<<4;
	GPIOA->BSRR	|=1<<4;
	/***********************/	
	//ÕâÀïÖ»Õë¶ÔSPI¿Ú³õÊ¼»¯
	GPIOA->CRL&=0X000FFFFF; 
	GPIOA->CRL|=0XBBB00000;//PA5.6.7¸´ÓÃ 	    
	GPIOA->ODR|=0X7<<5;    //PA5.6.7ÉÏÀ­
		
	SPI1->CR1|=0<<10;//È«Ë«¹¤Ä£Ê½	
	SPI1->CR1|=1<<9; //Èí¼þnss¹ÜÀí
	SPI1->CR1|=1<<8;  

	SPI1->CR1|=1<<2; //SPIÖ÷»ú
	SPI1->CR1|=0<<11;//8bitÊý¾Ý¸ñÊ½	
	
	SPI1->CR1|=0<<1; //CPOL=0Ê±¿ÕÏÐÄ£Ê½ÏÂSCKÎª0 
	SPI1->CR1|=0<<0; //µÚÒ»¸öÊ±ÖÓµÄÉÏÉýÑØ,CPHA=0 CPOL=0
	
	SPI1->CR1|=7<<3; //Fsck=Fcpu/256
	SPI1->CR1|=0<<7; //MSBfirst   
	SPI1->CR1|=1<<6; //SPIÉè±¸Ê¹ÄÜ
	SPIx_ReadWriteByte(0xff);//Æô¶¯´«Êä		 
}

//SPI ËÙ¶ÈÉèÖÃº¯Êý
//SpeedSet:
//SPI_SPEED_2   2·ÖÆµ   (SPI 36M@sys 72M)
//SPI_SPEED_8   8·ÖÆµ   (SPI 9M@sys 72M)
//SPI_SPEED_16  16·ÖÆµ  (SPI 4.5M@sys 72M)
//SPI_SPEED_256 256·ÖÆµ (SPI 281.25K@sys 72M)
void SPIx_SetSpeed(unsigned char SpeedSet)
{
	SPI1->CR1&=0XFFC7;//Fsck=Fcpu/256
	if(SpeedSet==SPI_SPEED_2)//¶þ·ÖÆµ
	{
		SPI1->CR1|=0<<3;//Fsck=Fpclk/2=36Mhz	
	}else if(SpeedSet==SPI_SPEED_8)//°Ë·ÖÆµ 
	{
		SPI1->CR1|=2<<3;//Fsck=Fpclk/8=9Mhz	
	}else if(SpeedSet==SPI_SPEED_16)//Ê®Áù·ÖÆµ
	{
		SPI1->CR1|=3<<3;//Fsck=Fpclk/16=4.5Mhz
	}else			 	 //256·ÖÆµ
	{
		SPI1->CR1|=7<<3; //Fsck=Fpclk/256=281.25Khz µÍËÙÄ£Ê½
	}
	SPI1->CR1|=1<<6; //SPIÉè±¸Ê¹ÄÜ	  
}


unsigned char SPIx_ReadWriteByte(unsigned char TxData)
{		
	unsigned int retry=0;				 
	while((SPI1->SR&1<<1)==0)//µè'y·??í????	
	{
		retry++;
		if(retry>500)return 0;
	}			  
	SPI1->DR=TxData;	 	  //·??íò???byte 
	retry=0;
	while((SPI1->SR&1<<0)==0) //µè'y?óê?íêò???byte  
	{
		retry++;
		if(retry>500)return 0;
	}	  						    
	return SPI1->DR;          //·µ??ê?µ?µ?êy?Y				    
}

// Í¨¹ýSPI ×ÜÏßÏò THM3060 Ð´Èë num ³¤¶È¸ö×Ö½Ú
void THM3070_SPI_sendbuff(u8 *buf,u16 num)
{
 	if ((buf == NULL)||(num == 0)) 
		return;

	while(num--)
	{
	 	SPIx_ReadWriteByte(*buf++);
	}  
}

// Í¨¹ýSPI ×ÜÏßÏò THM3060 ¶Á³ö num ³¤¶È¸ö×Ö½Ú
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
