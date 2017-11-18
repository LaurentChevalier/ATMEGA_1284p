/*
 * CallBack.h
 *
 * Created: 22-09-16 11:14:24
 *  Author: dbeck
 */ 


#ifndef CALLBACK_H_
#define CALLBACK_H_

#define MAX 10

/* Initialisation des callbacks */

void Callbacks_Init(void);
unsigned char CallBacks_Reccord_Timer (void(*pt_Function)(void), unsigned int Time);
void Callbacks_Remove_Timer (unsigned char ID_CB);
void CallBacks_Start (void);

#endif /* CALLBACK_H_ */