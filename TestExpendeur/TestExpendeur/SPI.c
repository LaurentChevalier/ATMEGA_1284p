/*
 * SPI.c
 *
 * Created: 16-12-16 14:30:55
 *  Author: dbeck
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "SPI.h"

void SPI_MasterInit(void)
{
	/* Set MOSI and SCK output, all others input */
	sbiBF(DDRB,DDB5);
	sbiBF(DDRB,DDB7);
	/* Enable SPI, Master, set clock rate fck/1 */
	//SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	SPCR = (1<<SPE)|(1<<MSTR);
	//Data Mode 0
}
char SPI_MasterTransmit(char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)))	//SPIF set a 1 quand transmission terminée
	;
	return SPDR;
}