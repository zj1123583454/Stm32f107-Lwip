#ifndef __SECURE_H__
#define __SECURE_H__   

#define	RX_FRAME_H	GPIOC->BSRR=(1<<6)
#define	RX_FRAME_L	GPIOC->BRR=	(1<<6)

#define	SDAT_H		GPIOB->BSRR=(1<<7)
#define	SDAT_L		GPIOB->BRR=	(1<<7)

#define	SCLK_H		GPIOB->BSRR=(1<<6)
#define	SCLK_L		GPIOB->BRR=	(1<<6)

#define	SCLK			(GPIOB->IDR&(1<<6))
#define	SDAT			(GPIOB->IDR&(1<<7))

#define	TX_FRAME		(GPIOC->IDR&(1<<7))

extern	void init_i2c(void);
extern	unsigned char  read_sec(unsigned char  * dat);
extern	void  write_sec(unsigned char * dat,unsigned short len);
	
void delay_nop(void);

#endif
