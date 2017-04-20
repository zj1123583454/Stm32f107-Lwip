#ifndef __SPI_H
#define __SPI_H

	#include "sys.h"
	
	// SPI�����ٶ����� 
	#define SPI_SPEED_2   0
	#define SPI_SPEED_8   1
	#define SPI_SPEED_16  2
	#define SPI_SPEED_256 3
																						  
	extern	void SPIx_Init(void);			 //��ʼ��SPI��
	extern	void THM3070_SPI_sendbuff(u8 *buf,u16 num);
	extern	void THM3070_SPI_revbuff(u8 *buf,u16 num);
	extern	void THM3070_SPI_framestart(void);
	extern	void THM3070_SPI_frameend(void);
		 
#endif

