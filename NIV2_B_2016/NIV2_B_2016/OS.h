#ifndef __OS_H
#define __OS_H

//**********************************************************
//********** FONCTIONS POUR LE MOTEUR OS *******************
//**********************************************************

//Initialisation OS
void OSInitialiser(void);

//Enregistrer des fonctions callback li�es au temps
//Retourne un ID associ� � l'enregistrement
unsigned char OSEnregistrerCB_TIMER(void(*ptFonction)(void), unsigned int temps); 

//Enregistrer la fonction li�e a l'appui sur un bouton (non li�e au temps)
//Retourne un ID associ� � l'enregistrement
void OSEnregistrerCB_Button(void(*ptFonction)(volatile unsigned char*));

//Enregistrer la fonction li�e a la r�ception d'un trame USART (non li�e au temps)
//Retourne un ID associ� � l'enregistrement
void OSEnregistrerCB_USART_RX(void(*ptFonction)(volatile char*));

//Retirer des fonctions callback li�es au temps, prend l'ID du CallBack comme argument
void OSRetirerCB_TIMER(unsigned char IDCB);

//Retirer la fonction li�e a l'appui sur une bouton, prend l'ID de la fonction comme argument
void OSRetirerCB_Button(void);

//Retirer la fonction li�e a la r�ception d'un trame USART, prend l'ID de la fonction comme argument
void OSRetirerCB_USART_RX(void);

//D�marrage de la boucle principale
void OSStart(void);

//Fonction qui recherche l'�tat suivant par rapport � l'�tat actuel et une nouvelle entr�e (stimuli)
unsigned char StateMachine(char state, unsigned char stimuli);

#endif //__OS_H
