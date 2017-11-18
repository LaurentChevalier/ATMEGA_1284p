/*
 * main.h
 *
 * Created: 29-12-16 12:31:14
 *  Author: Laurent Chevalier
 */ 


#ifndef MAIN_H_
#define MAIN_H_

// DEFINE 
#define sbiBF(port,bit)  (port |= (1<<bit))   //set bit in port
#define cbiBF(port,bit)  (port &= ~(1<<bit))  //clear bit in port
#define tbiBF(port,bit)  (port ^= (1<<bit))   //Toggle bit in port
#define TRUE				1
#define FALSE				0
#define NULL				0
#define MAXBUFRS232			128



#endif /* MAIN_H_ */