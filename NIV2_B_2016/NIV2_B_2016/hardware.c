/*
 * Hardware.c
 *
 * Created: 28-11-16 11:11:07
 *  Author: clare
 */ 

#include <avr/io.h>

// Activation des sorties

void initialize_sortie (void){
	
	DDRB = 0b00001111;
	PORTB = 0b11110000;
	//DDRC |= (1<<DDC0) | (1<<DDC1) | (1<<DDC2) | (1<<DDC3);	//Mise en output (low colonnes)
	DDRD |= (1<<DDD7) | (1<<DDD6);
	PORTD &=(0<<PORTD7)&~(0<<PORTD6);
}

// Activation des entrées

void initialize_entree (void){
	
	PORTB |= (1<<PORTB4) | (1<<PORTB5) | (1<<PORTB6) | (1<<PORTB7);	//Pull-Up activated
	PORTC |= (1<<PORTC0) | (1<<PORTC1);//Pull-Up activated (I2C)
}