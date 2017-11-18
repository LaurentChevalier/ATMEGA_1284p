/*
 * USART.h
 *
 * Created: 24-11-16 17:14:03
 *  Author: Laurent Chevalier
 */ 


#ifndef USART_H_
#define USART_H_



//PROTOTYPE FONCTIONS EXTERNES
void Usart_Tx(char data);
void Usart_Tx_String(char *String);
void USART_Init_19200(void);
void USART_Delay(void);
unsigned char Usart_Rx(void);




#endif /* USART_H_ */