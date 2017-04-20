#include "usb_lib.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "stm32f10x_it.h"

u8	EPindex;
DEVICE_INFO *pInformation;
/*  Points to the DEVICE_PROP structure of current device */
/*  The purpose of this register is to speed up the execution */
DEVICE_PROP *pProperty;
/*  Temporary save the state of Rx & Tx status. */
/*  Whenever the Rx or Tx state is changed, its value is saved */
/*  in this variable first and will be set to the EPRB or EPRA */
/*  at the end of interrupt process */
u16	SaveState ;
u16  wInterrupt_Mask;
DEVICE_INFO	Device_Info;
USER_STANDARD_REQUESTS  *pUser_Standard_Requests;

void used_as_USB_pull_up(void)
{
	RCC->APB2ENR|=1<<2;//打开PA口时钟
	
	GPIOA->CRH&=0xfffffff0;
	GPIOA->CRH|=0x00000003;
	GPIOA->ODR|=1<<8;
}

void USB_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	#ifdef  VECT_TAB_RAM  
	/* Set the Vector Table base location at 0x20000000 */ 
	NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
	#else  /* VECT_TAB_FLASH */
	/* Set the Vector Table base location at 0x08000000 */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
	#endif 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);

	//NVIC_InitStructure.NVIC_IRQChannel =USB_LP_CAN1_RX0_IRQHandler;   //change USB_LP_CAN1_RX0_IROn
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


/*******************************************************************************
* Function Name  : USB_Init
* Description    : USB system initialization
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USB_Init(void)
{
	pInformation = &Device_Info;

	used_as_USB_pull_up();

	USB_NVIC_Config();
	pInformation->ControlState = 2;

	pProperty = &Device_Property;

	pUser_Standard_Requests = &User_Standard_Requests;

	/* Initialize devices one by one */
	pProperty->Init();
}
