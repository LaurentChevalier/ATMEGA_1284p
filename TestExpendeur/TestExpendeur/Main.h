// Main.h

#ifndef _main_h_
#define _main_h_

//****************************************
//  CONSIGNES ET OBJECTIFS DU PROGRAMME
//****************************************

/*

Objectifs:
Utilisation du TIMER1 (16 bits) pour générer une interruption toutes les 2ms
Utilisation de l'entrée INT0 en interruption externe
Gestion des ports I/O
Gestion des interruptions et de la boucle infinie

Consignes du programme -> Par l'utilisation de CallBack
1. Clignotement de la LED à 1 Hertz 
2. Si bouton poussoir appuyé alors activation relais pendant 3 sec et changement de clignotement de 1 Hz à 10 Hz


*/


// DEFINE 

// Gestion registre par bit unique
#define sbiBF(port,bit)  (port |= (1<<bit))   //set bit in port
#define cbiBF(port,bit)  (port &= ~(1<<bit))  //clear bit in port
#define tbiBF(port,bit)  (port ^= (1<<bit))


#define TRUE				1
#define FALSE				0


void Test (void);


#endif /* _main.h */
