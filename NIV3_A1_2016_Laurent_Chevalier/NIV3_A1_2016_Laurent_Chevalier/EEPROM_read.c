/*
 * EEPROM_read.c
 *
 * Created: 19-12-16 13:53:50
 *  Author: Laurent
 */ 

#include <avr/pgmspace.h>
#include <string.h>
#include "EEPROM_routines.h"
#include "EEPROM_read.h"

extern unsigned char data_array[128];
extern unsigned char datatosave[128];

void EEPROM_read_datatosave(void)
{
	EEPROM_read(0,0,3);
	strcpy(datatosave,data_array);
	
}

