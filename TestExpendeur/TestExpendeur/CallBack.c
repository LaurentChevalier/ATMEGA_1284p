/*
 * CallBack.c
 *
 * Created: 22-09-16 11:14:04
 *  Author: dbeck
 */ 

#include "CallBack.h"
#include "Main.h"
#include "TIMERS.h"

#include <avr/io.h>
#include <avr/interrupt.h>

void (*My_CB[MAX])(void);
unsigned int time_CB[MAX];
volatile unsigned int TICK_CB[MAX];
unsigned char tmp_int;

extern volatile unsigned char receiveState;


void Callbacks_Init(void)
{
	unsigned char i;
	
	for(i=0 ; i < MAX ; i++)
	{
		My_CB [i] = 0;
		time_CB [i] = 0;
	}
}

unsigned char CallBacks_Reccord_Timer(void(*pt_Function)(void), unsigned int Time)
{
	unsigned int i = 0;
	
	while (My_CB[i] != 0 && i < MAX)
	i++;
	
	if (i < MAX)
	{
		My_CB[i] = pt_Function;
		time_CB[i] = Time;
		TICK_CB[i] = 0;
		return i;
	}
	else
		return 255;
}

void Callbacks_Remove_Timer (unsigned char ID_CB)
{
	if (ID_CB >= 0 && ID_CB < MAX)
	{
		My_CB[ID_CB] = 0;
		time_CB [ID_CB] = 0;
		
	}
}

void CallBacks_Start (void)
{
	unsigned char idx;
	
	TIMER2_Init_1ms();
	
	
	
	while (1)
	{
		for (idx = 0; idx < MAX; idx++)
		{
			if (My_CB[idx] && TICK_CB[idx] >= time_CB[idx])
			{
				TICK_CB[idx] = 0;
				My_CB[idx]();
			}
		}
	}
}

//****************************************
//  ROUTINE INTERRUPTIONS
//****************************************

//Timer2
ISR(TIMER2_COMPA_vect)
{
	//tbiBF(PORTB,PORTB0);
 	for (tmp_int = 0; tmp_int < MAX; tmp_int ++)
 		TICK_CB[tmp_int]++;
}


