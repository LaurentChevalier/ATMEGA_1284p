/*
 * SPI.h
 *
 * Created: 16-12-16 14:31:03
 *  Author: dbeck
 */ 


#ifndef SPI_H_
#define SPI_H_

// DEFINE

// Gestion registre par bit unique
#define sbiBF(port,bit)  (port |= (1<<bit))   //set bit in port
#define cbiBF(port,bit)  (port &= ~(1<<bit))  //clear bit in port
#define tbiBF(port,bit)  (port ^= (1<<bit))


#define TRUE				1
#define FALSE				0

void SPI_MasterInit(void);
char SPI_MasterTransmit(char cData);

#endif /* SPI_H_ */