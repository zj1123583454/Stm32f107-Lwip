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

//u32 *p=(u32 *)0x08008000; //����ָ��ָ��Ҫ���͵����ݵĵ�ַ
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

u32 StartAddr[3]={0x0800A800,0x0800B800,0x0800C000};  //Ҫд��Flash�����ݵ��׵�ַ--FLASH��ʼ��ַ
u32 EndAddr[3]={0x0800AFFF,0x0800BFFF,0x080C7FF};  //Ҫд��Flash�����ݵ�ĩ��ַ--FLASH������ַ 

volatile FLASH_Status FLASHStatus;
volatile TestStatus MemoryProgramStatus;

u32 FlashAddress=0x00;//Flash���ڲ���ַ	 

u8  Erasenumber=3;//��Ҫ������ҳ��1,2,3������
vu32 NbrOfPage = 0x00; //Ҫ������ҳ������


void Readflash(u32 In_addr,unsigned int len,unsigned char *dat)
{
	unsigned char ii=0;
	u32 *p=(u32 *)In_addr; //����ָ��ָ��Ҫ���͵����ݵĵ�ַ
	for(ii=0;ii<len;ii++)
	{
		*dat=*p;
	    dat++;p++;
	} 
}

/*******************************************************************************
* Function Name  : Writeflash
* Description    : д���� �����ݴ�CPUд��FLASH��
*                
* Input          : u8 Erasenumber,u32 *Data������Ҫ������ҳ���Ҫд������ݵĵ�ַ
* Output         : None
* Return         : None
*******************************************************************************/
void Writeflash(u8 Erasenumber,unsigned char le,unsigned char *Data)//u32 *p)
{
    unsigned char k;
	FLASHStatus = FLASH_COMPLETE;
    MemoryProgramStatus = PASSED; 

    /* Unlock the Flash Program Erase controller */
    FLASH_Unlock();	//FLASH����

    /* Clear All pending flags */
    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);//���־λ
	
//������д����		
//*******************************************************************************  
    switch(Erasenumber)
	{
		case 1://һ�β���1ҳ
				/* Define the number of page to be erased *///����Ҫ������ҳ�������
				NbrOfPage = (EndAddr[0] - StartAddr[0]) / FLASH_PAGE_SIZE;
				/* Erase the FLASH pages *///ҳ������ӳ���
				FLASHStatus = FLASH_ErasePage(StartAddr[0] + (FLASH_PAGE_SIZE * NbrOfPage)); 
				//д����
				FlashAddress = StartAddr[0];
				for(k=0;k<le;k++)
				{	
					FLASHStatus = FLASH_ProgramWord(FlashAddress, (unsigned int)*Data);
					FlashAddress+=4;	Data++;					
				}
				break;
		case 2://һ�β���1ҳ
				/* Define the number of page to be erased *///����Ҫ������ҳ�������
				NbrOfPage = (EndAddr[1] - StartAddr[1]) / FLASH_PAGE_SIZE;
				/* Erase the FLASH pages *///ҳ������ӳ���
				FLASHStatus = FLASH_ErasePage(StartAddr[1] + (FLASH_PAGE_SIZE * NbrOfPage)); 
				//д����
				FlashAddress = StartAddr[1];
				for(k=0;k<le;k++)
				{	
					FLASHStatus = FLASH_ProgramWord(FlashAddress, (unsigned int)*Data);
					FlashAddress+=4;	Data++;					
				}
				break;
		case 3://һ�β���1ҳ
				/* Define the number of page to be erased *///����Ҫ������ҳ�������
				NbrOfPage = (EndAddr[2] - StartAddr[2]) / FLASH_PAGE_SIZE;
				/* Erase the FLASH pages *///ҳ������ӳ���
				FLASHStatus = FLASH_ErasePage(StartAddr[2] + (FLASH_PAGE_SIZE * NbrOfPage)); 
				//д����
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
