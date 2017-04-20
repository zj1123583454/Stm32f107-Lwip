#include "stm32f10x.h"                  // Device header
#include "thm3070.h"

u16 FWT = 2000;

//control pin

#define STANDBY_L		GPIOB->BRR=(1<<0)
#define STANDBY_H		GPIOB->BSRR=(1<<0)

#define MOD0_L		GPIOB->BRR=(1<<1)
#define MOD0_H 	GPIOB->BSRR=(1<<1)

u8 test;

// ͨ�� SPI ���߶� address �Ĵ�����ֵ 
u8 thm3070_read_reg(u8 addr)
{
	u8 temp_buff[1];
	
	THM3070_SPI_framestart();
	temp_buff[0] = addr & 0x7F;	
	THM3070_SPI_sendbuff(temp_buff,1);
	THM3070_SPI_revbuff(temp_buff,1);
	THM3070_SPI_frameend();
	return(temp_buff[0]);
}

// ͨ�� SPI ����д address �Ĵ�����ֵ
void thm3070_write_reg(u8 addr,u8 content)
{
	u8 temp_buff[2];
	temp_buff[0] = addr | 0x80;
	temp_buff[1] = content;
	THM3070_SPI_framestart();
	THM3070_SPI_sendbuff(temp_buff,2);
	THM3070_SPI_frameend();
}

void THM_SetFWT(u32 ulFWT)
{
	u32 fwt = ulFWT+1; 
	thm3070_write_reg(FWTH, fwt>>16);
	thm3070_write_reg(FWTM, fwt>>8);
	thm3070_write_reg(FWTL, fwt&0xFF);
}

void THM_ChangeProtBaud(u8 prot, u8 sndbaud, u8 rcvbaud)
{
    thm3070_write_reg( PSEL, prot | sndbaud | rcvbaud );
}

unsigned	char	buffer[1]={0};
//thm3070��ʼ��
void thm3070_Init(void)
{
	u16 i;
	STANDBY_L;
	MOD0_L;
	
	for (i=0;i<10000;i++);
	for (i=0;i<10000;i++);
	SPIx_Init();
	for (i=0;i<10000;i++);
	for (i=0;i<10000;i++);
	
	
//	thm3070_write_reg(DP1,0xc0);
//	thm3070_write_reg(DP0,0x60);
//	thm3070_write_reg(DN1,0x7f);
//	thm3070_write_reg(DN0,0x20);
	
	thm3070_write_reg(DP1,0xff);
	thm3070_write_reg(DP0,0x50);
	thm3070_write_reg(DN1,0x7f);
	thm3070_write_reg(DN0,0x20);
	
        
	THM_SetFWT(0x5);
	THM_ChangeProtBaud(TYPE_B,SND_BAUD_106K,RCV_BAUD_106K);	
	thm3070_write_reg(CONTROL_TX,0x64);   //Force 10% module  ����
}

// SPI ģʽ������������,���ݴ��ڻ����� buffer �У�����ֵΪ�յ�����
u16 thm3070_read_buff(u8 *buffer)
{
	u8 temp;
	u16 num = 0;
	
	while (1)	
	{ 
		temp = thm3070_read_reg(RSTAT);   
		if (temp)
		{
			break;
		}
   }    
	
	if(temp&0x01)
	{		    
		//���㳤��	
    	num = (u16)thm3070_read_reg(RSCL)+ ((u16)(thm3070_read_reg(RSCH))<<8);
		if(num==0)
			return (num); 
		temp = 0x00;              //��ȡ DAT_REG�Ĵ�������
		THM3070_SPI_framestart();	
		THM3070_SPI_sendbuff(&temp,1);       //���Ͷ�ȡ����
		THM3070_SPI_revbuff(buffer,num); //��ȡ����
		THM3070_SPI_frameend();		
	}
	else
	{
		num = 0;				
	}
	return num;
}

// ���������ӳ���		 
void thm3070_send_buff(u8 *buffer,u16 num)
{
	u8 temp;	
	thm3070_write_reg(SCNTL,0x5);	 //PTRCLR =1,CARRYON =1
	thm3070_write_reg(SCNTL,0x01);    //PTRCLR=0;
        
	temp = DATA | 0x80;			                                //д���ݼĴ������� 	
	                        
	THM3070_SPI_framestart();
	
	THM3070_SPI_sendbuff(&temp,1);
	THM3070_SPI_sendbuff(buffer,num);	                                    //д������	
	
	THM3070_SPI_frameend();
	
	thm3070_write_reg(SCNTL, 0x03);                                  // SEND =1 ����ʼ����
	while(!thm3070_read_reg(TXFIN));
}

//����Ƶ
void thm3070_open_RF(void)
{
	u16 i;  	
	thm3070_write_reg(CONTROL_TX,0x64);
	for (i=0;i<60000;i++);
}
	
//�ر���Ƶ
void thm3070_close_RF(void)
{
	u16 i;  	
	thm3070_write_reg(CONTROL_TX,0x65);
	for (i=0;i<60000;i++);	
}
