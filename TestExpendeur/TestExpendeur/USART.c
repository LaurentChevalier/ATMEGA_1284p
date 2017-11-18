//FONCTIONS USART


//INCLUDE
#include "USART.h"
#include "Main.h"

#include <avr/io.h>
#include <avr/interrupt.h>

//DECLARATION DES VARIABLES GLOGALES


//PROTOTYPE FONCTIONS INTERNES


//CONTENU FONCTIONS EXTERNES

void Usart_Tx1(char data)
{
	while ( !( UCSR1A & (1<<UDRE1)) )
	;
	UDR1 = data;
	//UDR0 = 'A';
}

void Usart_String_Tx1 (char datastr[])
{
	int i = 0;
	while(datastr[i] != 0)
		{
			Usart_Tx1(datastr[i]);
			i++;
		}
}

 void Usart_String_Tx1_2D (volatile char datastr[SIZE][MAXDATA])
 {
	int i = 0;
	while(datastr[0][i] != 0)
	{
		Usart_Tx1(datastr[0][i]);
		i++;
	}
 }

void USART_INIT_9600_RX_INT (void)	//Pour ATMEGA 1284 9600bps
{
	//Clock 1MHz
	UBRR1 = 12;
	//Clock 8MHz
	//UBRR1 = 103;
	sbiBF(UCSR1A,U2X1);
	sbiBF(UCSR1B,RXCIE1);
	sbiBF(UCSR1B,RXEN1);
	sbiBF(UCSR1B,TXEN1);
	sbiBF(UCSR1C,UCSZ10);
	sbiBF(UCSR1C,UCSZ11);
}
//CONTENU FONCTIONS INTERNES

