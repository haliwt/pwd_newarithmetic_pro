#ifndef __EEPROM_H_
#define __EEPROM_H_
#include "main.h"


#define DATA_EEPROM_START_ADDR     			0x08080000   //start address
#define USER_DATA_EEPROM_ADDR(x)			(DATA_EEPROM_START_ADDR + x)	//customer of address
#define DATA_EEPROM_BYTE_SIZE				0x007F   // 128 bytes				// eeprom capacity 
#define DATA_EEPROM_END_ADDR     	        DATA_EEPROM_START_ADDR + DATA_EEPROM_BYTE_SIZE  // end of address
#define iEEPROM_CHECK_NUM 				    2



void EEPROM_Read_Byte(uint32_t Addr,uint8_t *Buffer,uint8_t Length);

void EEPROM_Write_Byte(uint32_t WriteAddr,uint8_t *pBuffer,uint8_t NumToWrite)  ;


//void EEPROM_EraseData(void);

void ClearEEPRO_Data(void);


#endif 


