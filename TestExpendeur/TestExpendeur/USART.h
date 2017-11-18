// USART.h

#ifndef _USART_H_
#define _USART_H_


//DEFINE
#define MAXDATA 150
#define SIZE 5

//PROTOTYPE FONCTIONS EXTERNES
void Usart_Tx1(char data);
void Usart_String_Tx1(char datastr[]);
void Usart_String_Tx1_2D (volatile char datastr[SIZE][MAXDATA]);
void USART_INIT_9600_RX_INT (void);	//Pour ATMEGA1284


#endif /* _USART_H */
