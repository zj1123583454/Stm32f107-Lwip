#include "stm32f10x.h"                  // Device header
#include "thm3070.h"

u16 FWT = 2000;

//control pin

#define STANDBY_L		GPIOB->BRR=(1<<0)
#define STANDBY_H		GPIOB->BSRR=(1<<0)

#define MOD0_L		GPIOB->BRR=(1<<1)
#define MOD0_H 	GPIOB->BSRR=(1<<1)

u8 test;

// 通过 SPI 总线读 address 寄存器的值 
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

// 通过 SPI 总线写 address 寄存器的值
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
//thm3070初始化
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
	thm3070_write_reg(CONTROL_TX,0x64);   //Force 10% module  开场
}

// SPI 模式读出接收数据,数据存在缓冲区 buffer 中，返回值为收到数据
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
		//计算长度	
    	num = (u16)thm3070_read_reg(RSCL)+ ((u16)(thm3070_read_reg(RSCH))<<8);
		if(num==0)
			return (num); 
		temp = 0x00;              //读取 DAT_REG寄存器命令
		THM3070_SPI_framestart();	
		THM3070_SPI_sendbuff(&temp,1);       //发送读取命令
		THM3070_SPI_revbuff(buffer,num); //读取数据
		THM3070_SPI_frameend();		
	}
	else
	{
		num = 0;				
	}
	return num;
}

// 发送数据子程序		 
void thm3070_send_buff(u8 *buffer,u16 num)
{
	u8 temp;	
	thm3070_write_reg(SCNTL,0x5);	 //PTRCLR =1,CARRYON =1
	thm3070_write_reg(SCNTL,0x01);    //PTRCLR=0;
        
	temp = DATA | 0x80;			                                //写数据寄存器命令 	
	                        
	THM3070_SPI_framestart();
	
	THM3070_SPI_sendbuff(&temp,1);
	THM3070_SPI_sendbuff(buffer,num);	                                    //写入数据	
	
	THM3070_SPI_frameend();
	
	thm3070_write_reg(SCNTL, 0x03);                                  // SEND =1 ，开始发送
	while(!thm3070_read_reg(TXFIN));
}

//打开射频
void thm3070_open_RF(void)
{
	u16 i;  	
	thm3070_write_reg(CONTROL_TX,0x64);
	for (i=0;i<60000;i++);
}
	
//关闭射频
void thm3070_close_RF(void)
{
	u16 i;  	
	thm3070_write_reg(CONTROL_TX,0x65);
	for (i=0;i<60000;i++);	
}
