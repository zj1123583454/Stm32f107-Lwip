#ifndef __INCLUDE_H
	#define __INCLUDE_H 			   

	#define	bool	_Bool
		
	#define	UART_RX_LEN		150
	#define	UART2_RX_LEN	150
	
	#define	LED_L	GPIOB->BRR=(1<<8)
	#define	LED_H	GPIOB->BSRR=(1<<8)

	#define	BUZZER_L	GPIOB->BRR=(1<<9)
	#define	BUZZER_H	GPIOB->BSRR=(1<<9)
	
	
	
	enum
	{
		ZERO=0,


		USBTRIGGER,
		USARTTRIGGER,
	};
//trigger
	typedef	struct
	{
		volatile	bool	tag;
		unsigned	short	int	value;
	}DATATAG;
	
	
	extern	DATATAG	USB_Send_Flag;
	extern	DATATAG	UASRT_Send_Flag;
	
	extern	volatile bool 	Command;
	extern	volatile	bool	buzzer_tag;
	extern	volatile bool	version_tag;
	extern	volatile bool	USB_Iinit_flag;
	extern	volatile bool 	Uasrt1_tx_falg;
	extern	volatile bool 	Uasrt2_tx_falg;
	extern	volatile	unsigned	char	InputSource;
	
	extern	unsigned char uasrt1_rxBuffer[UART_RX_LEN];
	extern	unsigned char uasrt1_txBuffer[10];
	extern	unsigned char uasrt2_rxBuffer[UART_RX_LEN];
	extern	unsigned char uasrt2_txBuffer[UART_RX_LEN];

	extern	void USB_TX(unsigned char *da,unsigned char len);

#endif

