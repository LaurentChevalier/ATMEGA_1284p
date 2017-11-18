// OS
#include "OS.h"
#include "Menu.h"
#include "Main.h"
#include "TIMERS.h"
//#include "USART.h"		// NOT USED
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

//Variables pour CallBack Chrono
void (*MaCB[MAXCALLBACKCHRONO])(void);
unsigned int TempsCB[MAXCALLBACKCHRONO];
volatile unsigned int TickCB[MAXCALLBACKCHRONO];

//Variables pour CallBack Button (Appui sur un bouton)
void(*MaCBButton)(volatile unsigned char*);

//Variables pour Gestion Touches
volatile unsigned char Button;
volatile unsigned char Previous_Button;
char IDCB_ENABLE_INTERRUPT_BP = 0;

extern unsigned char IDCB_Desactivation_boutton;
// PROTOTYPE FONCTIONS INTERNES
void ENABLE_INTERRUPT_BP(void);

//Variables pour CallBack USART (r�ception d'un string)
void(*MaCBUSART)(volatile char*);
volatile unsigned char USARTReception;
volatile char bufRS232[MAXBUFRS232];
volatile unsigned char idxbufRS232 = 0;

//Variables pour la machine d'�tats
unsigned char state;  // holds the current state, according to "menu.h"
char Message_LCD[17];

// ****************  OSInitialiser ******************************
// Initialise l'OS: initialise les variables et d�marre le Timer
// ****************************************************************
void OSInitialiser(void)
{
	unsigned char i;
	//Initialisation pour variables CallBack Chrono
	for (i=0; i<MAXCALLBACKCHRONO; i++)
	{
		MaCB[i] = 0;
		TempsCB[i] = 0;
	}

	//Initialisation pour variable Button
	MaCBButton = 0;
	
	//Initialisation pour variables CallBack USART
	MaCBUSART = 0;
	USARTReception = 0;
	
}

// ****************  EnregistrerFonctionDeRappel ******************************
// Sauve l'adresse de la fonction � rappeler. Lorsque le nombre d'interruptions
// aura atteint temps millisecondes, le syst�me rappellera la fonction
// *************************************************************************
unsigned char OSEnregistrerCB_TIMER(void(*ptFonction)(void), unsigned int tps)
{
	unsigned int i=1; //Attention ,on commence � 1 (IDCB = 0 --> callback non enregistr�e)
	while (MaCB[i]!=0 && i<MAXCALLBACKCHRONO) i++;
	//S'il reste de la place on enregistre et on retourne 0 (op�ration r�ussie)
	if (i<MAXCALLBACKCHRONO)
	{
		MaCB[i] = ptFonction;
		TempsCB[i] = tps;
		TickCB[i] = 0; //Initialiser le compteur � 0;
		return i; // ID du call back
	}
	else return 255; //Il n'y a plus de place pour enregistrer un callback
}

// **************** Enregistrer CallBack USART1 ****************************
// Sauve l'adresse de la fonction � rappeler
// *************************************************************************
void OSEnregistrerCB_USART_RX(void(*ptFonction)(volatile char*))
{
	//Sauver l'adresse de la fonction pour rappel
	MaCBUSART = ptFonction;
}

// ****************  Retirer fonction de rappel ******************************
// Lib�re l'emplacement de la callback
// *************************************************************************
void OSRetirerCB_TIMER(unsigned char IDCB)
{
	if ((IDCB >=0) && IDCB<MAXCALLBACKCHRONO)
	{
		MaCB[IDCB] = 0;
		TempsCB[IDCB] = 0;
	}
}

// ****************  Retirer fonction de rappel USART1 **********************

void OSRetirerCB_USART_RX(void)
{
	MaCBUSART = 0;
}

// ****************  Boucle principale de l'OS ******************************
// Boucle infinie qui attend des �v�nement li�s aux interruptions pour
// appeler les fonctions enregistr�es
// *************************************************************************
void OSStart()
{
	// Pour CALLBACKS
	unsigned char idx;
	
	// Pour STATES MACHINE
	unsigned char nextstate;
	PGM_P statetext; // cha�ne de texte sauvegard� dans la m�moire programme
	char (*pStateFunc)(char); // pointeur d'une fonction
	unsigned char input = NONE;
	unsigned char i, j;
	
	// Initialisation des variables qui concernent la machine d'�tats
	state = NULL;
	nextstate = FCT_MENU;
	statetext = NULL;
	pStateFunc = NULL;

	//Cr�ation, configuration et d�marrage de Timer pour g�n�rer une interruption toutes les mS
	TIMER1_Init_1ms();
	
	// Configuration de l'usart
	USART_Init_19200();
	
	// Initialisation des interruptions, on autorise toutes les interruptions
	// Pour les interruptions particuli�res, voir chaque fonction
	sei();
	Usart_Tx_String("Demarrage OS \n");
	
	

	//Boucle principale de l'OS d'o� on ne sort jamais
	while(1)
	{
		// Check les conditions pour rappeler les fonctions li�es au temps
		for (idx = 1; idx < MAXCALLBACKCHRONO; idx++)
		{
			if (MaCB[idx]) //Si on a l'adresse d'une fonction CB � cet index
			//Si on est arriv� au nombre de mS demand�, on appelle la fonction
			if (TickCB[idx] >= TempsCB[idx])
			{
				TickCB[idx] = 0;
				MaCB[idx]();  //Rappel de la fonction enregistr�e!
			}
		}
		
		// Check si r�ception USART
		/*if (USARTReception)
		{
			USARTReception = 0;
			if (MaCBUSART) MaCBUSART(bufRS232); //Rappel de la fonction enregistr�e!
		}*/
		
		// State Machine
		if (statetext)
		{
			//Afficher_LCD(statetext);
			//lcd_clrscr(); lcd_puts(strcpy_P(Message_LCD, statetext));
			//Usart_Tx_String(strcpy_P(Message_LCD, statetext));
			statetext = NULL;
		}

		// Read buttons
		input = Button;
		if(Button !=NONE)Previous_Button=input;
		Button = NONE;
		
		// When in this state, we must call the state function
		if (pStateFunc)
		{
			nextstate = pStateFunc(input);
		}
		else
		{
			if (input != NONE)
			{
				nextstate = StateMachine(state, input);
				Usart_Tx_String("Appui sur bouton \n");
			}
		}
		if (nextstate != state)  // il y a changement d'�tat
		{
			Usart_Tx_String("Changement d'etat \n");
			state = nextstate; // l'�tat est maintenant le nouveau �tat de la s�quence d�finie dans main.h
			for (i=0; (j=pgm_read_byte(&Menu_State[i].state)); i++)
			{
				if (j == state)
				{
					statetext =  (PGM_P) pgm_read_word(&Menu_State[i].pText);
					pStateFunc = (PGM_VOID_P) pgm_read_word(&Menu_State[i].pFunc);
					break;
				}
			}
		}
	}
}

unsigned char StateMachine(char state, unsigned char stimuli)
{
	Usart_Tx_String("Dans la fonction state machine \n");
	unsigned char nextstate = state;    // Default stay in same state
	unsigned char i, j;
	for (i=0; ( j=pgm_read_byte(&menu_nextstate[i].state) ); i++ )
	{
		if ( j == state &&
		pgm_read_byte(&menu_nextstate[i].input) == stimuli)
		{
			// This is the one!
			Usart_Tx_String("This is the one! \n");
			nextstate = pgm_read_byte(&menu_nextstate[i].nextstate);
			break;
		}
	}
	return nextstate;
}

// Routines INTERRUPTIONS

// ISR ...

//Interruption TIMER1
ISR(TIMER1_OVF_vect)
{
	// R�initialisation TIMER1
	// POUR 1 MHz
	//TCNT1H = 0xFC;
	//TCNT1L = 0x17;
	// POUR 8 MHz
	TCNT1H = 0xE0;
	TCNT1L = 0xC0;
	// Incr�menter tous les ticks
	unsigned char i;
	for (i = 0; i < MAXCALLBACKCHRONO; i++) TickCB[i]++;
}

//Interruption Touches
ISR (PCINT1_vect){
	PCICR &=~(1<<PCIE1);
	//IDCB_Desactivation_boutton = OSEnregistrerCB_TIMER(Desactivation_boutton, 500);

	//Button = NONE;
	
	/*Check 1st Column */
	
	cbiBF(PORTB,0);
	sbiBF(PORTB,1);
	sbiBF(PORTB,2);
	sbiBF(PORTB,3);
	if(~PINB & 0b10000000)  Button=BOUTON_7;
	if(~PINB & 0b01000000)  Button=BOUTON_4;
	if(~PINB & 0b00100000)  Button=BOUTON_1;
	if(~PINB & 0b00010000)	Button=BOUTON_etoile;

	/*Check 2st Column */
	sbiBF(PORTB,0);
	cbiBF(PORTB,1);
	if(~PINB & 0b10000000)	Button=BOUTON_8;
	if(~PINB & 0b10000000)	Button=BOUTON_8;
	if(~PINB & 0b01000000)  Button=BOUTON_5;
	if(~PINB & 0b00100000)  Button=BOUTON_2;
	if(~PINB & 0b00010000)  Button=BOUTON_0;
	
	/*Check 3st Column */
	sbiBF(PORTB,1);
	cbiBF (PORTB,2);
	if(~PINB & 0b10000000)	Button=BOUTON_9;
	if(~PINB & 0b10000000)	Button=BOUTON_9;
	if(~PINB & 0b01000000)  Button=BOUTON_6;
	if(~PINB & 0b00100000)  Button=BOUTON_3;
	if(~PINB & 0b00010000)  Button=BOUTON_dieze;
	
	/*Check 4st Column */
	sbiBF(PORTB,2);
	cbiBF (PORTB,3);
	if(~PINB & 0b10000000)	Button=BOUTON_A;
	if(~PINB & 0b10000000)	Button=BOUTON_A;
	if(~PINB & 0b01000000)  Button=BOUTON_B;
	if(~PINB & 0b00100000)  Button=BOUTON_C;
	if(~PINB & 0b00010000)  Button=BOUTON_D;
	
	/*Port � z�ro */
	cbiBF (PORTB, 0);
	cbiBF (PORTB, 1);
	cbiBF (PORTB, 2);
	//cbiBF (PORTB, 3);
	IDCB_Desactivation_boutton = OSEnregistrerCB_TIMER(Desactivation_boutton, 50);
}

// *************************
// INTERRUPTION USART en RX (TERMINAL PC)
// *************************

ISR(USART0_RX_vect)
{
	bufRS232[idxbufRS232] = UDR0;		 //Lire le registre de r�ception, le charger dans le buffer
	if ((bufRS232[idxbufRS232]=='\r') || (bufRS232[idxbufRS232]==0))
	{
		bufRS232[idxbufRS232] = 0;
		USARTReception = TRUE;
		idxbufRS232 = 0;
		//Transmettre retour chariot ('\r' + '\n' pour Win32 !!!)
		Usart_Tx('\r');
		Usart_Tx('\n');
		Usart_Tx('>');  // Transmettre un prompt
	}
	else
	{
		//Transmettre le caract�re en retour
		Usart_Tx(bufRS232[idxbufRS232]);
		//Si on arrive au maximum du buffer, remettre � z�ro
		if (++idxbufRS232 >= MAXBUFRS232) idxbufRS232 = 0;
	}
}