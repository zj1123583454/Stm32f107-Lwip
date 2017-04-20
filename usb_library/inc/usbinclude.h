#ifndef	USBINCLUDE_H
#define	USBINCLUDE_H


#define     __IO    volatile                  /*!< defines 'read / write' permissions   */
	
#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef __cplusplus
typedef enum {FALSE = 0, TRUE = !FALSE} bool;
#endif

    /* exact-width unsigned integer types */
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;


//typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

		
		typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;
		
		
#endif
