#include <string.h>
#include "sys.h"
#include "gpiox.h"
#include "TIMINIT.H"
#include "delay.h"
#include "uasrt.h"
#include "secure.h"
#include "include.h"
#include "stm32f10x_usart.h"
#include "stm32_eth.h"
#include "netconf.h"
#include "main.h"
#include "usart.h"
#include "init.h"
#include "lwip/tcp.h"
#include "TCPClient.h"
#include "stm32f107.h"

#define SYSTEMTICK_PERIOD_MS  10
#define Date_Len	200

__IO uint32_t LocalTime = 0; /* this variable is used to create a time reference incremented by 10ms */
void System_Periodic_Handle(void);

extern uint8_t TCP_ClientFlag;
extern uint8_t RX_Flag;
extern uint8_t RX_buffer[Date_Len];

uint8_t buf_1[Date_Len]={0};
uint8_t buf[Date_Len]={0};
uint8_t buf_2[Date_Len]={0};
uint8_t leng=0,leng_1=0;
uint8_t leng_2=0;
uint8_t IT_Begin=0;

struct tcp_pcb *Tcp_write=NULL;

int main(void)
{
#ifdef DEBUG
	debug();
#endif
	System_Setup();       
	LwIP_Init();													 			//LWIP ��ʼ��  ����IP��
	GPIO_Config();															//����IIC
	init_i2c();
	Delay(90000);                               //
	IT_Begin=22;                                //���г�ʼ��������־ �˱�־ʹ�� ��ʱ���TCP�Ƿ�Ͽ�
	Tcp_write=tcp_echoclient_connect();					//����TCPͨ�� �������ӵ�������
	while(1)
	{	
					if(TX_FRAME)																				 //�����ȫģ���ȡʹ��
					{		
						leng = read_sec(buf);										//��ȡ��ȫģ�鷵�ص���Ϣ �浽buf ���ҷ������ݳ���	
						leng_1 = DataPackage(buf_1,buf,leng); 			       //��װҪ���͵�����
						tcp_write(Tcp_write,buf_1,leng_1,1);
						tcp_output(Tcp_write);			
					}				
					tcp_recv(Tcp_write,tcp_echoclient_recv);               //����Socket������
					if(RX_Flag)
					{
						//memset(buf_2,0,Date_Len);
						leng_2=DataUnPackage(buf_2,RX_buffer);               
						buf_2[leng_2] = 0x00;																 //	����CRCУ��λ
						leng_2 += 1;
						write_sec(buf_2,leng_2);
						RX_Flag=0;
					}
 }
}
//------------------------------------------------------------------------------------
void My_Error(uint8_t * info)
{
	printf("%s\n\r",info);
}

/**
  * @brief  Updates the system local time
  * @param  None
  * @retval None
  */
void Time_Update(void)
{
  LocalTime += SYSTEMTICK_PERIOD_MS;
}

/**
  * @brief  Handles the periodic tasks of the system
  * @param  None
  * @retval None
  */
void System_Periodic_Handle(void)
{
  /* LwIP periodic services are done here */
  LwIP_Periodic_Handle(LocalTime);
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif


