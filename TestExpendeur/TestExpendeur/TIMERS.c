//FONCTIONS TIMER0


//INCLUDE
#include "TIMERS.h"
#include "Main.h"
#include "CallBack.h"

#include <avr/io.h>
#include <avr/interrupt.h>

//DECLARATION DES VARIABLES GLOGALES


//PROTOTYPE FONCTIONS INTERNES


//CONTENU FONCTIONS EXTERNES


void TIMER2_Init_1ms(void)
{
	sbiBF(TCCR2A,WGM21);		
	sbiBF(TCCR2B,CS21);			//Timer 1MHz -> presc 8
	//sbiBF(TCCR2B, CS22);		//Timer 8MHz -> presc 64
	OCR2A = 125;
	sbiBF(TIMSK2,OCIE2A);
}



//CONTENU FONCTIONS INTERNES
