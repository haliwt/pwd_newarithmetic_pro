#include "eeprom.h"






static void EEPROM_EraseData(void);


/******************************************************************************
	*
	*Function Name ：void EEPROM_EraseData(uint32_t start, uint32_t NumberSectors)         
	*Function：from EEPROM  erase data 
	*Input Ref: Address：                       
	*           *Buffer： to save data                    
	*           len： to read data length                         
	*Return ：NO 
	*
*******************************************************************************/
static void EEPROM_EraseData(void)
{
  // uint8_t i;

//   HAL_FLASHEx_DATAEEPROM_Unlock();
//   for(i=0;i<0x7F;i++){
//
//	 HAL_FLASHEx_DATAEEPROM_Erase(DATA_EEPROM_START_ADDR + i);
//
//   }
//	HAL_FLASHEx_DATAEEPROM_Lock();

	   uint8_t t;	
	   HAL_FLASHEx_DATAEEPROM_Unlock(); 	 
	   for(t = 0;t <0x80;t++)  
	   {  
		   HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE,DATA_EEPROM_BASE + t, 0);	
	   }  
	   HAL_FLASHEx_DATAEEPROM_Unlock();  



}



/******************************************************************************
	*
	*Function Name ：void EEPROM_Read_Byte(uint16_t Addr,uint8_t *Buffer,uint16_t Length)                    
	*Function：from EEPROM read data 
	*Input Ref: Address：                       
	*           *Buffer： to save data                    
	*           len： to read data length                         
	*Return ：NO 
	*
*******************************************************************************/
void EEPROM_Read_Byte(uint32_t Addr,uint8_t *Buffer,uint8_t Length)
{
   uint8_t *wAddr;  
   // HAL_FLASHEx_DATAEEPROM_Unlock();
    wAddr=(uint8_t *)(DATA_EEPROM_BASE+Addr);  
    while(Length--){  
        *Buffer++=*wAddr++;  
       
    } 
	//HAL_FLASHEx_DATAEEPROM_Lock();

}

/****************************************************************************************************
	*
	*Function Name :void EEPROM_Write_Byte(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite) 
	*Function : To stm32l010f4 to write data form EEPROM 
	*Input Ref: WriteAddr ->to write address ,*pBuffer ->to write data ,
				NumTowrie -> data of length
	*Return Ref :NO
	*
*****************************************************************************************************/
void EEPROM_Write_Byte(uint32_t WriteAddr,uint8_t *pBuffer,uint8_t NumToWrite)  
{  
    uint8_t t;  
    HAL_FLASHEx_DATAEEPROM_Unlock();      
    for(t = 0;t < NumToWrite;t++)  
    {  
        HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE,DATA_EEPROM_BASE + WriteAddr + t,*(pBuffer + t));  
    }  
    HAL_FLASHEx_DATAEEPROM_Unlock();  
}  



/****************************************************************************
*
*Function Name:void ClearEEPRO_Data(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void ClearEEPRO_Data(void)
{

    EEPROM_EraseData();
    HAL_Delay(100);
}










