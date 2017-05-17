/**
  ******************************************************************************
  * @file    stm32f107.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11/20/2009
  * @brief   This file contains all the functions prototypes for the STM32F107 
  *          file.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F107_H
#define __STM32F107_H

#ifdef __cplusplus
 extern "C" {
#endif

#define BEGIN				22
/* Includes ------------------------------------------------------------------*/
#include "misc.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"


void System_Setup(void);
void Iwdg_Init(void);
unsigned char checksum(unsigned short	int	LenG,unsigned char *ap);
int DataUnPackage(unsigned char* Dst,unsigned char* Src);
int DataPackage(unsigned char* Dst,unsigned char* Src,int SrcLength);
#ifdef __cplusplus
}
#endif

#endif /* __STM32F10F107_H */


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
