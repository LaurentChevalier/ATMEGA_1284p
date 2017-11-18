/*
 * EEPROM_save.c
 *
 * Created: 19-12-16 13:49:08
 *  Author: Laurent
 */ 

#include <avr/pgmspace.h>
#include <string.h>
#include "EEPROM_routines.h"
#include "EEPROM_save.h"

extern unsigned char data_array[128];
extern unsigned char datatosave[128];

void EEPROM_save_datatosave(void)
{
	strcpy(data_array,datatosave);
	EEPROM_write(0,0,128);
}



