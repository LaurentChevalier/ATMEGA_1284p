/*
 * Expender.h
 *
 * Created: 16-12-16 12:10:27
 *  Author: dbeck
 */ 


#ifndef EXPENDER_H_
#define EXPENDER_H_

// DEFINE

// Gestion registre par bit unique
#define sbiBF(port,bit)  (port |= (1<<bit))   //set bit in port
#define cbiBF(port,bit)  (port &= ~(1<<bit))  //clear bit in port
#define tbiBF(port,bit)  (port ^= (1<<bit))


#define TRUE				1
#define FALSE				0

//define du CS du MCP23S17
#define PORTCSEXPENDER		PORTB
#define BITCSEXPENDER		PORTB4

//define des ports
#define GPA0	0
#define GPA1	1
#define GPA2	2
#define GPA3	3
#define GPA4	4
#define GPA5	5
#define GPA6	6
#define GPA7	7

#define GPB0	0
#define GPB1	1
#define GPB2	2
#define GPB3	3
#define GPB4	4
#define GPB5	5
#define GPB6	6
#define GPB7	7

void ExpenderSetA (char BIT, char state);
void ExpenderSetB (char BIT, char state);
void ExpenderSetPort (char PORT, char BIT);
char ExpenderGet (char PORT, char BIT);
void ExpenderInit (void);

#endif /* EXPENDER_H_ */