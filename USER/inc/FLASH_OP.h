#ifndef FLASH_OP_H
#define FLASH_OP_H

	#define In_Addr0     0x0800A800 //存储机器码地址
	#define In_Addr1     0x0800B800 //液晶配置信息
	#define In_Addr2     0x0800C000 //背光 出厂
	
	void Readflash(u32 In_addr,unsigned int len,unsigned char *dat);
	void Writeflash(u8 Erasenumber,unsigned char le,unsigned char *Data);


#endif 

