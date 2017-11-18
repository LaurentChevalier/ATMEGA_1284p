/*
 * Expender.c
 *
 * Created: 16-12-16 12:08:59
 *  Author: dbeck
 */

#include "USART.h"
#include "Expender.h"
#include "SPI.h"

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char expPortA;
unsigned char expPortB;

void ExpenderSetA (char BIT, char state)
{
	char i;
	i = 0b00000000;
	//Masquage Port A
	if (state)
	{
		i |= (1<< BIT);
		expPortA |= i;
	}
	else
	{
		i |= ~(1<<BIT);
		expPortA &= i;
	}
	cbiBF(PORTCSEXPENDER,BITCSEXPENDER);
	//Adresse
	i = 0b01000000;
	i = SPI_MasterTransmit(i);
	//Registre
	SPI_MasterTransmit('\x12');
	//Bit
	SPI_MasterTransmit(expPortA);
	sbiBF(PORTCSEXPENDER,BITCSEXPENDER);
}

void ExpenderSetB (char BIT, char state)
{
	char i;
	i = 0b00000000;
	//Masquage Port B
	if (state)
	{
		i |= (1<< BIT);
		expPortB |= i;
	}
	else
	{
		i |= ~(1<<BIT);
		expPortB &= i;
	}
	cbiBF(PORTCSEXPENDER,BITCSEXPENDER);
	//Adresse
	i = 0b01000000;
	i = SPI_MasterTransmit(i);
	//Registre
	SPI_MasterTransmit('\x13');
	//Bit
	SPI_MasterTransmit(expPortB);
	sbiBF(PORTCSEXPENDER,BITCSEXPENDER);
}

void ExpenderSetPort (char PORT, char BIT)
{
	char i;
	cbiBF(PORTCSEXPENDER,BITCSEXPENDER);
	//Adresse
	i = 0b01000000;
	i = SPI_MasterTransmit(i);
	//Registre
	SPI_MasterTransmit(PORT);
	//Bit
	SPI_MasterTransmit(BIT);
	sbiBF(PORTCSEXPENDER,BITCSEXPENDER);
}

char ExpenderGet (char PORT, char BIT)
{
	char i;
	char data;
	cbiBF(PORTCSEXPENDER,BITCSEXPENDER);
	//Adresse
	i = 0b01000001;
	SPI_MasterTransmit(i);
	//Registre
	SPI_MasterTransmit(PORT);
	//Bit
	data = SPI_MasterTransmit(0b00000000);
	sbiBF(PORTCSEXPENDER,BITCSEXPENDER);
	return data;
}

void ExpenderInit ()
{
	expPortA = 0b00000000;
	expPortB = 0b00000000;
	ExpenderSetPort('\x0A',0b00001000);		//HAEN = 1, prend en compte A0,A1,A2
	ExpenderSetPort('\x0A',0b00001000);		//HAEN = 1, prend en compte A0,A1,A2
	ExpenderSetPort('\x04',0b00000000);		//pas d'interruptions
	ExpenderSetPort('\x05',0b00000000);		//pas d'interruptions
	ExpenderSetPort('\x0C',0b00000000);		//Pas de Pull-Up sur le Port A
	ExpenderSetPort('\x0D',0b00000000);		//Pas de Pull-Up sur le Port B
	ExpenderSetPort('\x00',0b00000000);		//Port A en Output
	ExpenderSetPort('\x01',0b00000000);		//Port B en Output
	ExpenderSetPort('\x12',0b00000000);		//Port A set a 0
	ExpenderSetPort('\x13',0b00000000);		//Port B set a 0
}