#ifndef FLASH_OP_H
#define FLASH_OP_H

	#define In_Addr0     0x0800A800 //�洢�������ַ
	#define In_Addr1     0x0800B800 //Һ��������Ϣ
	#define In_Addr2     0x0800C000 //���� ����
	
	void Readflash(u32 In_addr,unsigned int len,unsigned char *dat);
	void Writeflash(u8 Erasenumber,unsigned char le,unsigned char *Data);


#endif 

