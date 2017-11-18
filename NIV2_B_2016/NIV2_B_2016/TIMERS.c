//FONCTIONS TIMER

//INCLUDE
#include "TIMERS.h"
#include "Main.h"
#include <avr/io.h>

//DECLARATION DES VARIABLES GLOGALES

//PROTOTYPE FONCTIONS INTERNES

//CONTENU FONCTIONS EXTERNES

void TIMER1_Init_1ms(void)
{
	//En mode compteur le registre TCCR1A = 0x00
	//fOSC = 1 Mhz
	//Si diviseur par 1 -> 1000000/1 = 1000 Khz
	// Une période = 1µS
	// Si je compte jusque 1000 --> 1000 X 1µs = 1 ms

	//fOSC = 8 Mhz
	//Si diviseur par 1 -> 8000000/1 = 8000 Khz
	// Une période = 0.125µS
	// Si je compte jusque 8000 --> 8000 X 0.125µs = 1 ms
	
	TCCR1A = 0x00;
	TCCR1B |= (0<<CS12)|(0<<CS11)|(1<<CS10);
	// Pour fOSC = 1 MHZ --> Valeur initiale du compteur = 65536 - 1000 = 64536
	TCNT1H = 0xFC;
	TCNT1L = 0x17;
	// Pour fOSC = 8 MHZ --> Valeur initiale du compteur = 65536 - 8000 = 57536
	//TCNT1H = 0xE0;
	//TCNT1L = 0xC0;
	// Autorisation de l'interruption en cas d'overflow
	TIMSK1 = (1<<TOIE1);

}



//CONTENU FONCTIONS INTERNES
