/*
 * NIV3_A1_2016_Laurent_Chevalier.c
 *
 * Created: 29-12-16 12:11:15
 * Author : Laurent Chevalier
 */ 

#include <avr/io.h>
#include <string.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "hardware.h"
#include "i2c_routines.h"
#include "EEPROM_routines.h"
#include "EEPROM_read.h"
#include "EEPROM_save.h"
#include "USART.h"
#include "main.h"

volatile unsigned char USARTReception;
volatile char bufRS232[MAXBUFRS232];
volatile unsigned char idxbufRS232 = 0;
unsigned char datatosave[128];


int main(void)
{
	unsigned char choix;
	//Initialisation des I/O
	initialize_entree ();
	//Initialisation de l'USART
	USART_Init_19200();
	//Initialisation de l'I2C
	twi_init();
	Usart_Tx_String("Bienvenue dans le programme de test EEPROM via USART 19200 baudrate");
    while (1) 
    {
		Usart_Tx_String("\rVoici le menu:\r");
		Usart_Tx_String("1 : Read EEPROM\r");
		Usart_Tx_String("2 : Write EEPROM\r");
		Usart_Tx_String("Votre choix: ");
		choix=Usart_Rx();
		Usart_Tx(choix);

		switch(choix)
		{
			case '1':
				Usart_Tx_String("\rVoici les données présentes aux 128 premiers bytes de l'EEPROM:\r");
				EEPROM_read_datatosave();
				Usart_Tx_String("\rDonnees:\r");
				Usart_Tx_String(datatosave);
				
			break;
			case '2':
				strcpy(datatosave,"bonjour comment allez vous ? Bien merci");
				EEPROM_save_datatosave();
				Usart_Tx_String("\rDonnées enregistrés !\r");
				
			break;
			
			default:
				Usart_Tx_String("\rChoix incorrect\r");
			
		}
		
		
    }
}

