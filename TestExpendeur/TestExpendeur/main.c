/*
 * TestExpendeur.c
 *
 * Created: 06-12-16 09:26:22
 * Author : dbeck
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "Main.h"
#include "CallBack.h"
#include "TIMERS.h"
#include "USART.h"
#include "Expender.h"
#include "SPI.h"

unsigned char CB_TEST;
unsigned char counter;

//Adresse MCP23S17	0100 000

int main(void)
{
	sbiBF(DDRB,DDB0);
	sbiBF(PORTB,PORTB0);
	sbiBF(DDRB,DDB4);
	sbiBF(PORTB,PORTB4);
	sbiBF(DDRD,DDD5);
	sbiBF(PORTD,PORTD5);
	Callbacks_Init();
	SPI_MasterInit();
	USART_INIT_9600_RX_INT();
	TIMER2_Init_1ms();
	ExpenderInit();
	sei();
	char i;
	i = 0b00000000;
	i |= (1<< 2);
	Usart_Tx1(i);
	ExpenderSetA(GPA5,1);
	ExpenderSetA(GPA6,1);
	ExpenderSetA(GPA5,0);
	ExpenderSetA(GPA6,0);
	ExpenderSetB(GPB0,1);
	ExpenderSetB(5,1);
	
    /* Replace with your application code */
	CB_TEST = CallBacks_Reccord_Timer(Test,5000);
    while (1)
    {
		//CallBacks_Start();
		
    }
}

void Test (void)
{
	counter ++;
	if (counter == 1){
		
	}
	if (counter == 2){
		
	}
}