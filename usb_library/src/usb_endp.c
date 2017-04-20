#include <string.h>
#include "usb_lib.h"
#include "usb_istr.h"
#include "usb_desc.h"
#include "FLASH_OP.h"
#include "include.h"
#include "uasrt.h"
#include "delay.h"

volatile bool Command=0;
volatile bool USB_Received_Flag=0;

volatile unsigned char DataLen=0;

unsigned char USB_Send_Buffer[64];
unsigned char USB_Receive_Buffer[64];

unsigned char	version[64]={
										0xAA,0xAA,0xAA,0x96,0x69,0x00,0x25,0x00,0x00,0x90,
										0xc4,0x02,0xed,0xfd,0x3e,0xb1,0xbb,0xb0,0x97,0x52,0x31,0x53,0x11,0x67,0xff,0xee,
										0xc4,0x02,0xed,0xfd,0x3e,0xb1,0xbb,0xb0,0xff,0xff,0xff,0x97,0x52,0x31,0x53,0x11,
										0x67,0x5b,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
										0x00,0x00,0x00,0x00,0x00,0x00,
									};


void USB_TX(unsigned char *da,unsigned char len)
{
	UserToPMABufferCopy(da, GetEPTxAddr(ENDP1), len);
	SetEPTxCount(ENDP1, len);
	SetEPTxValid(ENDP1);
}

unsigned char CRC_JiaoYan(unsigned char len, unsigned char *da)
{
	unsigned char checksum=0,i;
	for(i=0;i<len;i++)
	{
		checksum^=*(da+i);
	}
	return checksum;
}

/*******************************************************************************
* Function Name  : EP1_IN_Callback.
* Description    : EP1 IN Callback Routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP1_IN_Callback(void)
{

}

/*******************************************************************************
* Function Name  : EP2_OUT_Callback.
* Description    : EP2 OUT Callback Routine.
* Input          : None.
* Output         : None.
* Return         : None.  
*******************************************************************************/
void EP1_OUT_Callback(void)
{
	bool	flag=0;
	DataLen=0;
	DataLen = GetEPRxCount(ENDP1); //获取收到的长度
	PMAToUserBufferCopy(USB_Receive_Buffer, ENDP1_RXADDR, 64);
  	SetEPRxStatus(ENDP1, EP_RX_VALID);
	USB_Received_Flag=((DataLen==0x3F)||DataLen==0x0a)?1:0;
	
	if(USB_Received_Flag)
	{
		USB_Received_Flag=0;
		
		if((USB_Receive_Buffer[0]==0xAA)&&(USB_Receive_Buffer[1]==0xAA)&&(USB_Receive_Buffer[2]==0xAA)&&(USB_Receive_Buffer[7]==0x88)&&(USB_Receive_Buffer[8]==0x05)&&(USB_Receive_Buffer[9]==0x8E))
		{
			USB_TX(version,64);
		}
		else	if((USB_Receive_Buffer[0]==0xAA)&&(USB_Receive_Buffer[1]==0xAA)&&(USB_Receive_Buffer[2]==0xAA)&&(USB_Receive_Buffer[7]==0x12)&&(USB_Receive_Buffer[8]==0xFF)&&(USB_Receive_Buffer[9]==0xEE))
		{
			flag=1;
		}
		else	if((USB_Receive_Buffer[0]==0xAA)&&(USB_Receive_Buffer[1]==0xAA)&&(USB_Receive_Buffer[2]==0xAA)&&(USB_Receive_Buffer[7]==0x11)&&(USB_Receive_Buffer[8]==0xff)&&(USB_Receive_Buffer[9]==0xED))
		{
			flag=1;
		}
		else	if((USB_Receive_Buffer[0]==0xAA)&&(USB_Receive_Buffer[1]==0xAA)&&(USB_Receive_Buffer[2]==0xAA)&&(USB_Receive_Buffer[7]==0x20)&&(USB_Receive_Buffer[8]==0x01)&&(USB_Receive_Buffer[9]==0x22))
		{
			flag=1;
		}
		else	if((USB_Receive_Buffer[0]==0xAA)&&(USB_Receive_Buffer[1]==0xAA)&&(USB_Receive_Buffer[2]==0xAA)&&(USB_Receive_Buffer[7]==0x20)&&(USB_Receive_Buffer[8]==0x02)&&(USB_Receive_Buffer[9]==0x21))
		{
			flag=1;
		}
		else	if((USB_Receive_Buffer[0]==0xAA)&&(USB_Receive_Buffer[1]==0xAA)&&(USB_Receive_Buffer[2]==0xAA)&&(USB_Receive_Buffer[7]==0x30)&&(USB_Receive_Buffer[8]==0x01)&&(USB_Receive_Buffer[9]==0x32))		
		{
			flag=1;
		}
		else
		{
			if((USB_Receive_Buffer[6]==0x0d)&&(USB_Receive_Buffer[9]==0xAA)&&(USB_Receive_Buffer[10]==0xAA)&&(USB_Receive_Buffer[11]==0xAA)&&(USB_Receive_Buffer[16]==0x30)&&(USB_Receive_Buffer[17]==0x10)&&(USB_Receive_Buffer[18]==0x23))
			{
				memcpy(uasrt1_txBuffer,(USB_Receive_Buffer+9),10);
				memset(USB_Receive_Buffer,0x00,64);
				Command=1;
				flag=0;
			}
			else
				Command=0;
		}
		if(flag)
		{
			memcpy(uasrt1_txBuffer,USB_Receive_Buffer,10);
			memset(USB_Receive_Buffer,0x00,64);
			//InputSource=USBTRIGGER;                 //
			Command=1;
			flag=0;
		}
	}
}



