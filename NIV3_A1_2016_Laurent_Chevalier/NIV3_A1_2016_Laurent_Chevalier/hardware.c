/*
 * Hardware.c
 *
 * Created: 29-12-16 12:11:15
 *  Author: Laurent Chevalier
 */ 

#include <avr/io.h>

// Activation des entrées

void initialize_entree (void){
	
	PORTC |= (1<<PORTC0) | (1<<PORTC1);//Pull-Up activated (I2C)
}