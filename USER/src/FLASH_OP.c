#include "stm32f10x.h"
#include "stm32f10x_flash.h"
#include "FLASH_OP.h"

#if !defined (STM32_DK_128K) &&  !defined (STM32_EK)
 //#define USE_STM3210B_EVAL
 #define STM32_EK
#endif

/* Define the STM32F10x hardware depending on the used evaluation board */
#ifdef STM32_DK_128K
  #define FLASH_PAGE_SIZE    ((u16)0x400) //1024  1K
#elif defined STM32_EK
  #define FLASH_PAGE_SIZE    ((u16)0x800) //2048   2K
#endif /* USE_STM3210B_EVAL */

//u32 *p=(u32 *)0x08008000; //定义指针指向要传送的数据的地址
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

u32 StartAddr[3]={0x0800A800,0x0800B800,0x0800C000};  //要写入Flash的数据的首地址--FLASH起始地址
u32 EndAddr[3]={0x0800AFFF,0x0800BFFF,0x080C7FF};  //要写入Flash的数据的末地址--FLASH结束地址 

volatile FLASH_Status FLASHStatus;
volatile TestStatus MemoryProgramStatus;

u32 FlashAddress=0x00;//Flash的内部地址	 

u8  Erasenumber=3;//需要擦除的页码1,2,3。。。
vu32 NbrOfPage = 0x00; //要擦除的页面数量


void Readflash(u32 In_addr,unsigned int len,unsigned char *dat)
{
	unsigned char ii=0;
	u32 *p=(u32 *)In_addr; //定义指针指向要传送的数据的地址
	for(ii=0;ii<len;ii++)
	{
		*dat=*p;
	    dat++;p++;
	} 
}

/*******************************************************************************
* Function Name  : Writeflash
* Description    : 写函数 把数据从CPU写到FLASH中
*                
* Input          : u8 Erasenumber,u32 *Data，输入要擦除的页面和要写入的数据的地址
* Output         : None
* Return         : None
*******************************************************************************/
void Writeflash(u8 Erasenumber,unsigned char le,unsigned char *Data)//u32 *p)
{
    unsigned char k;
	FLASHStatus = FLASH_COMPLETE;
    MemoryProgramStatus = PASSED; 

    /* Unlock the Flash Program Erase controller */
    FLASH_Unlock();	//FLASH解锁

    /* Clear All pending flags */
    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);//清标志位
	
//擦除后写数据		
//*******************************************************************************  
    switch(Erasenumber)
	{
		case 1://一次擦除1页
				/* Define the number of page to be erased *///定义要擦出的页面的数量
				NbrOfPage = (EndAddr[0] - StartAddr[0]) / FLASH_PAGE_SIZE;
				/* Erase the FLASH pages *///页面擦除子程序
				FLASHStatus = FLASH_ErasePage(StartAddr[0] + (FLASH_PAGE_SIZE * NbrOfPage)); 
				//写数据
				FlashAddress = StartAddr[0];
				for(k=0;k<le;k++)
				{	
					FLASHStatus = FLASH_ProgramWord(FlashAddress, (unsigned int)*Data);
					FlashAddress+=4;	Data++;					
				}
				break;
		case 2://一次擦除1页
				/* Define the number of page to be erased *///定义要擦出的页面的数量
				NbrOfPage = (EndAddr[1] - StartAddr[1]) / FLASH_PAGE_SIZE;
				/* Erase the FLASH pages *///页面擦除子程序
				FLASHStatus = FLASH_ErasePage(StartAddr[1] + (FLASH_PAGE_SIZE * NbrOfPage)); 
				//写数据
				FlashAddress = StartAddr[1];
				for(k=0;k<le;k++)
				{	
					FLASHStatus = FLASH_ProgramWord(FlashAddress, (unsigned int)*Data);
					FlashAddress+=4;	Data++;					
				}
				break;
		case 3://一次擦除1页
				/* Define the number of page to be erased *///定义要擦出的页面的数量
				NbrOfPage = (EndAddr[2] - StartAddr[2]) / FLASH_PAGE_SIZE;
				/* Erase the FLASH pages *///页面擦除子程序
				FLASHStatus = FLASH_ErasePage(StartAddr[2] + (FLASH_PAGE_SIZE * NbrOfPage)); 
				//写数据
				FlashAddress = StartAddr[2];
				for(k=0;k<le;k++)
				{	
					FLASHStatus = FLASH_ProgramWord(FlashAddress, (unsigned int)*Data);
					FlashAddress+=4;	Data++;					
				}
				break;
		default:
				break;
	}
	FLASH_Lock();
}
