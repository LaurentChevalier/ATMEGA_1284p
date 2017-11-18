/*
 * EEPROM_routines.c
 *
 * Created: 18/12/2016 16:58:59
 *  Author: Laurent
 */ 

#include <avr/pgmspace.h>
#include "EEPROM_routines.h"
#include "USART.h"
#include "i2c_routines.h"

unsigned char data_array[128];
//******************************************************************
//Function to read given number of bytes from EEPROM 
//******************************************************************
unsigned char EEPROM_read(unsigned char highAddress, unsigned char lowAddress, unsigned char totalChar)
{
   unsigned char errorStatus, i, data;
   
   errorStatus = i2c_start();
   if(errorStatus == 1)
   {
	 Usart_Tx_String("i2c start failed..");
   	 i2c_stop();
	 return(1);
   } 
   
   errorStatus = i2c_sendAddress(EEPROM_W);
   
   if(errorStatus == 1)
   {
	 Usart_Tx_String("EEPROM sendAddress1 failed..");
	 i2c_stop();
	 return(1);
   } 
   
   errorStatus = i2c_sendData(highAddress);
   if(errorStatus == 1)
   {
	 Usart_Tx_String("EEPROM write-1 failed..");
	 i2c_stop();
	 return(1);
   } 
   
 
   errorStatus = i2c_sendData(lowAddress);
   if(errorStatus == 1)
   {
	 Usart_Tx_String("EEPROM write-2 failed..");
	 i2c_stop();
	 return(1);
   } 
   
   errorStatus = i2c_repeatStart();
   if(errorStatus == 1)
   {
	 Usart_Tx_String("i2c repeat-start failed..");
	 i2c_stop();
	 return(1);
   } 
   
   errorStatus = i2c_sendAddress(EEPROM_R);
   if(errorStatus == 1)
   {
	 Usart_Tx_String("EEPROM sendAddress2 failed..");
	 i2c_stop();
	 return(1);
   } 
   
   for(i=0;i<totalChar;i++)
   {
      if(i == (totalChar-1))  	 //no Acknowledge after receiving the last byte
	   	  data = i2c_receiveData_NACK();
	  else
	  	  data = i2c_receiveData_ACK();
		  
   	  if(data == ERROR_CODE)
   	  {
			Usart_Tx_String("EEPROM receive failed..");
			i2c_stop();
	   		return(1);
   	  }
	   
	   if((i%16) == 0) 
	   //Usart_Tx_String("EEPROM ROUTINE _data: \n");
	   //Usart_Tx(data);
	   data_array[i]=data;
	   
   }
   
   i2c_stop();
   
   return(0);
}
//******************************************************************
//Function to write a character to EEPROM 
//******************************************************************
unsigned char EEPROM_write(unsigned char highAddress, unsigned char lowAddress, unsigned char numberofbytes)
{
   unsigned char errorStatus, i; //data;
   
   errorStatus = i2c_start();
   if(errorStatus == 1)
   {
	 Usart_Tx_String("i2c start failed..");
   	 i2c_stop();
	 return(1);
   } 
   
   errorStatus = i2c_sendAddress(EEPROM_W);
   
   if(errorStatus == 1)
   {
	 Usart_Tx_String("EEPROM sendAddress1 failed..");
	 i2c_stop();
	 return(1);
   } 
   
   errorStatus = i2c_sendData(highAddress);
   if(errorStatus == 1)
   {
	 Usart_Tx_String("EEPROM write-1 failed..");
	 i2c_stop();
	 return(1);
   } 
   
 
   errorStatus = i2c_sendData(lowAddress);
   if(errorStatus == 1)
   {
	 Usart_Tx_String("EEPROM write-2 failed..");
	 i2c_stop();
	 return(1);
   } 
   
   for(i=0;i<numberofbytes;i++){
   
	  errorStatus = i2c_sendData(data_array[i]);
	  //Usart_Tx_String("EEPROM write data Successful..");
   	  if(errorStatus == 1)
   	  {
			Usart_Tx_String("EEPROM write data failed..");
			i2c_stop();
	   		return(1);
   	  }
   
   }
   
   i2c_stop();
   //Usart_Tx_String("EEPROM write data SUCESSFUL..\n");
   return(0);
}

