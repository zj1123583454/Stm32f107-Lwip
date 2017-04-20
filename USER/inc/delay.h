#ifndef __DELAY_H
#define __DELAY_H 	
#include "stm32f10x.h"

	void delay_init(unsigned char SYSCLK);
	void delay_ms(unsigned short nms);
	void delay_us(unsigned int nus);
	void Delay(unsigned int nCount);
	void Delay_ms(uint32_t time);

#endif
