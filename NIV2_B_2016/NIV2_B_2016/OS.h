#ifndef __OS_H
#define __OS_H

//**********************************************************
//********** FONCTIONS POUR LE MOTEUR OS *******************
//**********************************************************

//Initialisation OS
void OSInitialiser(void);

//Enregistrer des fonctions callback liées au temps
//Retourne un ID associé à l'enregistrement
unsigned char OSEnregistrerCB_TIMER(void(*ptFonction)(void), unsigned int temps); 

//Enregistrer la fonction liée a l'appui sur un bouton (non liée au temps)
//Retourne un ID associé à l'enregistrement
void OSEnregistrerCB_Button(void(*ptFonction)(volatile unsigned char*));

//Enregistrer la fonction liée a la réception d'un trame USART (non liée au temps)
//Retourne un ID associé à l'enregistrement
void OSEnregistrerCB_USART_RX(void(*ptFonction)(volatile char*));

//Retirer des fonctions callback liées au temps, prend l'ID du CallBack comme argument
void OSRetirerCB_TIMER(unsigned char IDCB);

//Retirer la fonction liée a l'appui sur une bouton, prend l'ID de la fonction comme argument
void OSRetirerCB_Button(void);

//Retirer la fonction liée a la réception d'un trame USART, prend l'ID de la fonction comme argument
void OSRetirerCB_USART_RX(void);

//Démarrage de la boucle principale
void OSStart(void);

//Fonction qui recherche l'état suivant par rapport à l'état actuel et une nouvelle entrée (stimuli)
unsigned char StateMachine(char state, unsigned char stimuli);

#endif //__OS_H
