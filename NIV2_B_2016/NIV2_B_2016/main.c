// INCLUDE
#include "Main.h"
#include "OS.h"
#define F_CPU 8000000UL 
#include <util/delay.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include "lcd_driver_KS0107.h"
#include "lcd_graphics.h"
#include "HELHa_glcd.h"
#include "hardware.h"
#include "i2c_routines.h"
#include "EEPROM_routines.h"
#include "EEPROM_read.h"

// CONSTANTES
// VARIABLES
unsigned char IDCB_Switch_Led;	// mémorisation de l'identificateur créé lors de l'enregistrement de la Callback Switch_Led
unsigned char IDCB_Clignotement_heure;
unsigned char IDCB_Clignotement_date;
unsigned char IDCB_Clignotement_bp;
unsigned char IDCB_Clignotement_ti;
unsigned char IDCB_Clignotement_consigne;
unsigned char IDCB_Desactivation_boutton;
uint8_t menuStrings[5][15] = {"Automatique\0","Manuel\0","Parametres\0","Pizza\0","Exit\0"};
unsigned char hour[6]={0,0,0,0,0,0};
unsigned char date[8]={0,1,0,1,2,0,0,0};
unsigned char consigne[3]={0,0,0};
unsigned char out[3]={0,0,0};
unsigned char alarme_high[3]={0,0,0};
unsigned char alarme_low[3]={0,0,0};
unsigned char bp[3]={0,0,0};
unsigned char ti[5]={0,0,0,0,0};
unsigned char td[5]={0,0,0,0,0};
unsigned char te[5]={0,0,0,0,0};
unsigned char out0[3]={0,0,0};
unsigned char hysteresis_high[3]={0,0,0};
unsigned char hysteresis_low[3]={0,0,0};
unsigned char recurrence_a[90]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char recurrence_b[90]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char automatique=0;						
unsigned char position=0;
unsigned char capteur=0;
unsigned char sortie=0;
int consigne_int=0;
int out_int=0;
int alarme_high_int=0;
int alarme_low_int=0;
int bp_int=0;
int ti_int=0;
int td_int=0;
int te_int=0;
int out0_int=0;
int hysteresis_high_int=0;
int hysteresis_low_int=0;
extern volatile unsigned char Button;
extern volatile unsigned char Previous_Button;
//usart
extern volatile char bufRS232[MAXBUFRS232];
extern volatile unsigned char USARTReception;

void wait_100x_ms(int ms) { uint8_t i; for (i=0;i<ms;i++) _delay_ms(100); }


//****************** FONCTION PRINCIPALE *****************
int main (void)
{
	
	//Initialisation I/O 
	  initialize_entree();
	  initialize_sortie();
	  
	//Initialisation TWI 
	  twi_init();
	
	//Initilisation LCD
	LCD_init();
	
	LCD_clr();
	LCD_drawBMP((uint8_t*)HELHa_glcd_bmp, 12, 12,HELHa_GLCD_WIDTH,HELHa_GLCD_HEIGHT);
	_delay_ms(2000);
	
	LCD_clr();
	LCD_setCursorXY(15,0);
	LCD_puts ((uint8_t*)"The Regulator");
	LCD_setCursorXY(45,0);
	LCD_invertPage(0,10,100);
	LCD_setCursorXY(3,20);
	LCD_puts ((uint8_t*)"CODED by:");
	LCD_setCursorXY(0,25);
	LCD_puts ((uint8_t*)"Beck.D  Chevalier.L\n");
	LCD_puts ((uint8_t*)"Clarembaux.L  Croix.A\n");
	LCD_puts ((uint8_t*)"Delbart.B  Maerten.G\n");
	LCD_puts ((uint8_t*)"      Pauwels.A");
	_delay_ms(3000);
	
	//Initialisation interruption clavier
	PCICR |= (1<<PCIE1);
	PCMSK1 |= (1<<PCINT12) | (1<<PCINT13) | (1<<PCINT14) | (1<<PCINT15) ;
	
	// Initialisation de l'OS (appel des Callbacks)
	OSInitialiser();

	// Initialisation des Callbacks
 	IDCB_Switch_Led = OSEnregistrerCB_TIMER(Switch_Led, 500);
		
	OSStart();

 	//N'arrive jamais ici
	return 0;
}

void Switch_Led(void)
{
	 PINC |= (1<<PINC7);
}

void Desactivation_boutton(void)
{
	if(PINB==0b11110000)
	{
		PCICR |=(1<<PCIE1);
		OSRetirerCB_TIMER(IDCB_Desactivation_boutton);		
	}

}

void clignotementheure(void)
{
		switch(position-1)
		{
			case 0: LCD_invertPage(2,0,4);
			break;
			case 1: LCD_invertPage(2,6,10);
			break;
			case 2: LCD_invertPage(2,18,22);
			break;
			case 3: LCD_invertPage(2,24,28);
			break;
			case 4: LCD_invertPage(2,36,40);
			break;
			case 5: LCD_invertPage(2,42,46);
			break;
		}
}

void clignotementdate(void)
{
	switch(position-1)
	{
		case 0: LCD_invertPage(2,0,4);
		break;
		case 1: LCD_invertPage(2,6,10);
		break;
		case 2: LCD_invertPage(2,18,22);
		break;
		case 3: LCD_invertPage(2,24,28);
		break;
		case 4: LCD_invertPage(2,36,40);
		break;
		case 5: LCD_invertPage(2,42,46);
		break;
		case 6: LCD_invertPage(2,48,52);
		break;
		case 7: LCD_invertPage(2,54,58);
		break;
		
	}
}

void clignotementbp(void){
	
	switch(position-1)
	{
		case 0: LCD_invertPage(2,0,4);
		break;
		case 1: LCD_invertPage(2,6,10);
		break;
		case 2: LCD_invertPage(2,12,16);
		break;
		
	}
	
}
void clignotementti(void){
	
	switch(position-1)
	{
		case 0: LCD_invertPage(2,0,4);
		break;
		case 1: LCD_invertPage(2,6,10);
		break;
		case 2: LCD_invertPage(2,12,16);
		break;
		case 3: LCD_invertPage(2,18,22);
		break;
		case 4: LCD_invertPage(2,24,28);
		break;
		
		
	}
	
}


void clignotementconsigne(void){
	
	switch(position-1)
	{
		case 0: LCD_invertPage(2,0,4);
		break;
		case 1: LCD_invertPage(2,12,16);
		break;
		case 2: LCD_invertPage(2,18,22);
		break;
		
	}
	
}

char Fct_menu(char input)
{
			 LCD_clr();
			 switch(automatique)
			 {
				 case 0:
					LCD_setCursorXY(45,0);
					LCD_puts ((uint8_t*)"MENU");
					LCD_setCursorXY(3,15);
					LCD_puts ((uint8_t*)"1.Automatique");
					LCD_setCursorXY(3,30);
					LCD_puts ((uint8_t*)"2.Manuel");
					LCD_setCursorXY(3,30);
					LCD_invertPage(3,1,80);
					LCD_setCursorXY(3,45);
					LCD_puts ((uint8_t*)"3.Parmetres");			 
				 break;
				 case 1: 
					LCD_setCursorXY(45,0);
					LCD_puts ((uint8_t*)"MENU");
					LCD_setCursorXY(3,15);
					LCD_puts ((uint8_t*)"1.Automatique");
					LCD_setCursorXY(3,15);
					LCD_invertPage(1,1,80);
					LCD_setCursorXY(3,30);
					LCD_puts ((uint8_t*)"2.Manuel");
					LCD_setCursorXY(3,45);
					LCD_puts ((uint8_t*)"3.Parmetres");
				break;
			 }
		     LCD_setCursorXY(3,60);
		     LCD_puts ((uint8_t*)"");
			
			 return ST_MENU;
}

char Fct_auto(char input)
{
	automatique=1;
	EEPROM_read_consigne();
	char buffer[20];
	LCD_clr();
	LCD_setCursorXY(45,0);
	LCD_puts ((uint8_t*)"CONSIGNE");
	LCD_setCursorXY(0,20);
	itoa(consigne[0],buffer,10);
	LCD_puts (buffer);
	LCD_puts ((uint8_t*)".");
	itoa(consigne[1],buffer,10);
	LCD_puts (buffer);
	itoa(consigne[2],buffer,10);
	LCD_puts (buffer);
	LCD_setCursorXY(3,40);
	LCD_puts ((uint8_t*)" A : Reglage");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)" B : BACK");
	
	return ST_AUTO;
}

char Fct_auto_consigne_change(char input)
{
	input=Previous_Button;
	char buffer[20];
	itoa(input,buffer,10);
	Usart_Tx_String(buffer);
	Usart_Tx_String("\n");
	if(position!=0)
	{
		consigne[position-1]=input-1;
	}
	else IDCB_Clignotement_consigne = OSEnregistrerCB_TIMER(clignotementconsigne,500);
	LCD_clr();
	LCD_setCursorXY(10,0);
	LCD_puts ((uint8_t*)"Entrer la consigne:");
	LCD_setCursorXY(0,20);
	itoa(consigne[0],buffer,10);
	LCD_puts (buffer);
	LCD_puts ((uint8_t*)".");
	itoa(consigne[1],buffer,10);
	LCD_puts (buffer);
	itoa(consigne[2],buffer,10);
	LCD_puts (buffer);
	
	position++;
	if(position==4)
	{
		position=0;
		EEPROM_save_consigne();
		consigne_int = (int)consigne[2]+(10*((int)consigne[1]))+(100*((int)consigne[0]));
		itoa(consigne_int,buffer,10);
		Usart_Tx_String("Valeur consigne: ");
		Usart_Tx_String(buffer);
		Usart_Tx_String("\n");
		
		OSRetirerCB_TIMER(IDCB_Clignotement_consigne);
		return FCT_AUTO;
	}
	else return ST_AUTO_CONSIGNE_CHANGE;
	
	
}

char Fct_manu(char input)
{
	automatique=0;
	LCD_clr();
	LCD_setCursorXY(45,0);
	LCD_puts ((uint8_t*)"MANU");
	LCD_setCursorXY(3,10);
	LCD_puts ((uint8_t*)"1.Identification");
	LCD_setCursorXY(3,20);
	LCD_puts ((uint8_t*)"2.Out");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)" B : BACK");
	
	return ST_MANU;
}

char Fct_identification(char input)
{
	LCD_clr();
	LCD_setCursorXY(25,0);
	LCD_puts ((uint8_t*)"Identification");
	LCD_setCursorXY(3,10);
	LCD_puts ((uint8_t*)"COMING SOON ... BY USART");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)" B : BACK");
	return ST_IDENTIFICATION;
}

char Fct_out(char input)
{
	EEPROM_read_out();
	char buffer[20];
	LCD_clr();
	LCD_setCursorXY(45,0);
	LCD_puts ((uint8_t*)"OUT");
	LCD_setCursorXY(0,20);
	itoa(out[0],buffer,10);
	LCD_puts (buffer);
	LCD_puts ((uint8_t*)".");
	itoa(out[1],buffer,10);
	LCD_puts (buffer);
	itoa(out[2],buffer,10);
	LCD_puts (buffer);
	LCD_setCursorXY(3,40);
	LCD_puts ((uint8_t*)" A : Reglage");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)" B : BACK");
	return ST_OUT;
}


char Fct_out_change(char input)
{
	input=Previous_Button;
	
	char buffer[20];
	itoa(input,buffer,10);
	Usart_Tx_String(buffer);
	Usart_Tx_String("\n");
	if(position!=0)
	{
		out[position-1]=input-1;
	}
	else IDCB_Clignotement_consigne = OSEnregistrerCB_TIMER(clignotementconsigne,500);
	LCD_clr();
	LCD_setCursorXY(10,0);
	LCD_puts ((uint8_t*)"Enter OUT Value:");
	LCD_setCursorXY(0,20);
	itoa(out[0],buffer,10);
	LCD_puts (buffer);
	LCD_puts ((uint8_t*)".");
	itoa(out[1],buffer,10);
	LCD_puts (buffer);
	itoa(out[2],buffer,10);
	LCD_puts (buffer);
	
	position++;
	if(position==4)
	{
		position=0;
		EEPROM_save_out();
		out_int = (int)out[2]+(10*((int)out[1]))+(100*((int)out[0]));
		itoa(out_int,buffer,10);
		Usart_Tx_String("Valeur OUT: ");
		Usart_Tx_String(buffer);
		Usart_Tx_String("\n");
		
		OSRetirerCB_TIMER(IDCB_Clignotement_consigne);
		return FCT_OUT;
	}
	else return ST_OUT_CHANGE;
}


char Fct_parameters(char input)
{

	LCD_clr();
	LCD_setCursorXY(25,0);
	LCD_puts ((uint8_t*)"PARAMETRES");
	LCD_setCursorXY(0,10);
	LCD_puts ((uint8_t*)"1.Capteur\n");
	//LCD_setCursorXY(3,20);
	LCD_puts ((uint8_t*)"2.Sortie\n");
	//LCD_setCursorXY(3,30);
	LCD_puts ((uint8_t*)"3.Alarme\n");
	//LCD_setCursorXY(3,40);
	LCD_puts ((uint8_t*)"4.Reglage regulateur\n");
	//LCD_setCursorXY(3,50);
	LCD_puts ((uint8_t*)"5.Date/heure\n");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)"B: BACK");
	return ST_PARAMETERS;
}

char Fct_capteur (char input){
	LCD_clr();
	LCD_setCursorXY(25,0);
	LCD_puts ((uint8_t*)"CHOIX CAPTEUR");
	switch(capteur){
		case 0:
			LCD_setCursorXY(3,10);
			LCD_puts ((uint8_t*)"1.Temperature");
			LCD_setCursorXY(3,20);
			LCD_puts ((uint8_t*)"2.Luminosite");
			LCD_setCursorXY(3,30);
			LCD_puts ((uint8_t*)"3.Humidite");
			LCD_setCursorXY(3,35);
			LCD_puts ((uint8_t*)"4.ADC");
		break;
		case 1:
			LCD_setCursorXY(3,10);
			LCD_puts ((uint8_t*)"1.Temperature");
			LCD_setCursorXY(3,10);
			LCD_invertPage(1,1,80);
			LCD_setCursorXY(3,20);
			LCD_puts ((uint8_t*)"2.Luminosite");
			LCD_setCursorXY(3,30);
			LCD_puts ((uint8_t*)"3.Humidite");
			LCD_setCursorXY(3,35);
			LCD_puts ((uint8_t*)"4.ADC");
		break;
		case 2:
			LCD_setCursorXY(3,10);
			LCD_puts ((uint8_t*)"1.Temperature");
			LCD_setCursorXY(3,20);
			LCD_puts ((uint8_t*)"2.Luminosite");
			LCD_setCursorXY(3,20);
			LCD_invertPage(2,1,80);
			LCD_setCursorXY(3,30);
			LCD_puts ((uint8_t*)"3.Humidite");
			LCD_setCursorXY(3,35);
			LCD_puts ((uint8_t*)"4.ADC");
		break;
		case 3:
			LCD_setCursorXY(3,10);
			LCD_puts ((uint8_t*)"1.Temperature");
			LCD_setCursorXY(3,20);
			LCD_puts ((uint8_t*)"2.Luminosite");
			LCD_setCursorXY(3,30);
			LCD_puts ((uint8_t*)"3.Humidite");
			LCD_setCursorXY(3,30);
			LCD_invertPage(3,1,80);
			LCD_setCursorXY(3,35);
			LCD_puts ((uint8_t*)"4.ADC");
		break;
		case 4:
			LCD_setCursorXY(3,10);
			LCD_puts ((uint8_t*)"1.Temperature");
			LCD_setCursorXY(3,20);
			LCD_puts ((uint8_t*)"2.Luminosite");
			LCD_setCursorXY(3,30);
			LCD_puts ((uint8_t*)"3.Humidite");
			LCD_setCursorXY(3,35);
			LCD_puts ((uint8_t*)"4.ADC");
			LCD_setCursorXY(3,35);
			LCD_invertPage(4,1,80);
		break;
		
	}
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)" B : BACK");
	return ST_CAPTEUR;
}

char Fct_temperature(char input)
{
	capteur=1;
	LCD_clr();
	LCD_setCursorXY(15,0);
	LCD_puts ((uint8_t*)"Capteur choisi:");
	LCD_setCursorXY(3,10);
	LCD_puts ((uint8_t*)"Temperature");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)"B: BACK");
	return ST_TEMPERATURE;
	
}

char Fct_luminosite(char input)
{
	capteur=2;
	LCD_clr();
	LCD_setCursorXY(15,0);
	LCD_puts ((uint8_t*)"Capteur choisi:");
	LCD_setCursorXY(3,10);
	LCD_puts ((uint8_t*)"Luminosite");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)"B: BACK");
	return ST_LUMINOSITE;
}

char Fct_humidite(char input)
{
	capteur=3;
	LCD_clr();
	LCD_setCursorXY(15,0);
	LCD_puts ((uint8_t*)"Capteur choisi:");
	LCD_setCursorXY(3,10);
	LCD_puts ((uint8_t*)"Humidite");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)"B: BACK");
	return ST_HUMIDITE;
}

char Fct_adc(char input)
{
	capteur=4;
	LCD_clr();
	LCD_setCursorXY(15,0);
	LCD_puts ((uint8_t*)"Capteur choisi:");
	LCD_setCursorXY(3,10);
	LCD_puts ((uint8_t*)"ADC");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)"B: BACK");
	return ST_ADC;
}


char Fct_output(char input)
{
	LCD_clr();
	LCD_setCursorXY(45,0);
	LCD_puts ((uint8_t*)"SORTIE");
	switch(sortie){
		case 0:
			LCD_setCursorXY(3,10);
			LCD_puts ((uint8_t*)"1.PWM");
			LCD_setCursorXY(3,20);
			LCD_puts ((uint8_t*)"2.Relais");
			LCD_setCursorXY(3,30);
			LCD_puts ((uint8_t*)"3.Analogique");
		break;
		case 1:
			LCD_setCursorXY(3,10);
			LCD_puts ((uint8_t*)"1.PWM");
			LCD_setCursorXY(3,10);
			LCD_invertPage(1,1,80);
			LCD_setCursorXY(3,20);
			LCD_puts ((uint8_t*)"2.Relais");
			LCD_setCursorXY(3,30);
			LCD_puts ((uint8_t*)"3.Analogique");
		break;
		case 2:
			LCD_setCursorXY(3,10);
			LCD_puts ((uint8_t*)"1.PWM");
			LCD_setCursorXY(3,20);
			LCD_puts ((uint8_t*)"2.Relais");
			LCD_setCursorXY(3,20);
			LCD_invertPage(2,1,80);
			LCD_setCursorXY(3,30);
			LCD_puts ((uint8_t*)"3.Analogique");
		break;
		case 3:
			LCD_setCursorXY(3,10);
			LCD_puts ((uint8_t*)"1.PWM");
			LCD_setCursorXY(3,20);
			LCD_puts ((uint8_t*)"2.Relais");
			LCD_setCursorXY(3,30);
			LCD_puts ((uint8_t*)"3.Analogique");
			LCD_setCursorXY(3,30);
			LCD_invertPage(3,1,80);
		break;
	}
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)" B : BACK");
	return ST_OUTPUT;
}

char Fct_pwm(char input)
{
	sortie=1;
	LCD_clr();
	LCD_setCursorXY(15,0);
	LCD_puts ((uint8_t*)"Sortie choisie:");
	LCD_setCursorXY(3,10);
	LCD_puts ((uint8_t*)"PWM");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)"B: BACK");
	return ST_PWM;
}

char Fct_relais(char input)
{
	sortie=2;
	LCD_clr();
	LCD_setCursorXY(15,0);
	LCD_puts ((uint8_t*)"Sortie choisie:");
	LCD_setCursorXY(3,10);
	LCD_puts ((uint8_t*)"Relais");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)"B: BACK");
	return ST_RELAIS;
}

char Fct_analogique(char input)
{
	sortie=3;
	LCD_clr();
	LCD_setCursorXY(15,0);
	LCD_puts ((uint8_t*)"Sortie choisie:");
	LCD_setCursorXY(3,10);
	LCD_puts ((uint8_t*)"Analogique");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)"B: BACK");
	return ST_ANALOGIQUE;
}



char Fct_alarme(char input)
{
	LCD_clr();
	LCD_setCursorXY(45,0);
	LCD_puts ((uint8_t*)"ALARME");
	LCD_setCursorXY(3,10);
	LCD_puts ((uint8_t*)"1.Valeur haute");
	LCD_setCursorXY(3,20);
	LCD_puts ((uint8_t*)"2.Valeur basse");
	LCD_setCursorXY(3,30);
	LCD_puts ((uint8_t*)"3.STOP");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)" B : BACK");
	return ST_ALARM;
}

char Fct_alarme_high(char input)
{
	EEPROM_read_alarme_high();
	char buffer[20];
	LCD_clr();
	LCD_setCursorXY(45,0);
	LCD_puts ((uint8_t*)"SET High");
	LCD_setCursorXY(0,20);
	itoa(alarme_high[0],buffer,10);
	LCD_puts (buffer);
	itoa(alarme_high[1],buffer,10);
	LCD_puts (buffer);
	itoa(alarme_high[2],buffer,10);
	LCD_puts (buffer);
	LCD_puts ((uint8_t*)"%");
	LCD_setCursorXY(3,40);
	LCD_puts ((uint8_t*)" A : Reglage");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)" B : BACK");
	return ST_ALARME_HIGH;
}

char Fct_alarme_high_change(char input)
{
	input=Previous_Button;
	
	char buffer[20];
	itoa(input,buffer,10);
	Usart_Tx_String(buffer);
	Usart_Tx_String("\n");
	if(position!=0)
	{
		alarme_high[position-1]=input-1;
	}
	else IDCB_Clignotement_bp = OSEnregistrerCB_TIMER(clignotementbp,500);
	LCD_clr();
	LCD_setCursorXY(10,0);
	LCD_puts ((uint8_t*)"Alarm HIGH Value:");
	LCD_setCursorXY(0,20);
	itoa(alarme_high[0],buffer,10);
	LCD_puts (buffer);
	itoa(alarme_high[1],buffer,10);
	LCD_puts (buffer);
	itoa(alarme_high[2],buffer,10);
	LCD_puts (buffer);
	LCD_puts ((uint8_t*)"%");
	
	position++;
	if(position==4)
	{
		position=0;
		EEPROM_save_alarme_high();
		alarme_high_int = (int)alarme_high[2]+(10*((int)alarme_high[1]))+(100*((int)alarme_high[0]));
		itoa(alarme_high_int,buffer,10);
		Usart_Tx_String("Alarm HIGH Value: ");
		Usart_Tx_String(buffer);
		Usart_Tx_String("%");
		Usart_Tx_String("\n");
		
		OSRetirerCB_TIMER(IDCB_Clignotement_bp);
		return FCT_ALARME_HIGH;
	}
	else return ST_ALARME_HIGH_CHANGE;
	
	
}


char Fct_alarme_low(char input)
{
	EEPROM_read_alarme_low();
	char buffer[20];
	LCD_clr();
	LCD_setCursorXY(45,0);
	LCD_puts ((uint8_t*)"SET Low");
	LCD_setCursorXY(0,20);
	itoa(alarme_low[0],buffer,10);
	LCD_puts (buffer);
	itoa(alarme_low[1],buffer,10);
	LCD_puts (buffer);
	itoa(alarme_low[2],buffer,10);
	LCD_puts (buffer);
	LCD_puts ((uint8_t*)"%");
	LCD_setCursorXY(3,40);
	LCD_puts ((uint8_t*)" A : Reglage");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)" B : BACK");
	return ST_ALARME_LOW;
}


char Fct_alarme_low_change(char input)
{
	input=Previous_Button;
	
	char buffer[20];
	itoa(input,buffer,10);
	Usart_Tx_String(buffer);
	Usart_Tx_String("\n");
	if(position!=0)
	{
		alarme_low[position-1]=input-1;
	}
	else IDCB_Clignotement_bp = OSEnregistrerCB_TIMER(clignotementbp,500);
	LCD_clr();
	LCD_setCursorXY(10,0);
	LCD_puts ((uint8_t*)"Alarm LOW Value:");
	LCD_setCursorXY(0,20);
	itoa(alarme_low[0],buffer,10);
	LCD_puts (buffer);
	itoa(alarme_low[1],buffer,10);
	LCD_puts (buffer);
	itoa(alarme_low[2],buffer,10);
	LCD_puts (buffer);
	LCD_puts ((uint8_t*)"%");
	
	position++;
	if(position==4)
	{
		position=0;
		EEPROM_save_alarme_low();
		alarme_low_int = (int)alarme_low[2]+(10*((int)alarme_low[1]))+(100*((int)alarme_low[0]));
		itoa(alarme_low_int,buffer,10);
		Usart_Tx_String("Valeur alarme basse: ");
		Usart_Tx_String(buffer);
		Usart_Tx_String("%");
		Usart_Tx_String("\n");
		
		OSRetirerCB_TIMER(IDCB_Clignotement_bp);
		return FCT_ALARME_LOW;
	}
	else return ST_ALARME_LOW_CHANGE;
	
	
}


char Fct_alarme_stop(char input)
{
	LCD_clr();
	LCD_setCursorXY(45,0);
	LCD_puts ((uint8_t*)"ALARME:");
	LCD_setCursorXY(3,20);
	LCD_puts ((uint8_t*)" Arretee");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)" B : BACK");
	return ST_ALARME_STOP;
}


char Fct_reg_settings(char input)
{
	EEPROM_read_recurrence_a();
	LCD_clr();
	LCD_setCursorXY(10,0);
	LCD_puts ((uint8_t*)"REGLAGE REGULATEUR");
	LCD_setCursorXY(3,10);
	LCD_puts ((uint8_t*)"1.Recurrence");
	LCD_setCursorXY(3,20);
	LCD_puts ((uint8_t*)"2.PID");
	LCD_setCursorXY(3,30);
	LCD_puts ((uint8_t*)"3.Hysteresis");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)" B : BACK");
	return ST_REG_SETTINGS;
}

char Fct_recurrence(char input)
{
	EEPROM_read_recurrence_b();
	LCD_clr();
	LCD_setCursorXY(35,0);
	LCD_puts ((uint8_t*)"RECURRENCE");
	LCD_setCursorXY(0,10);
	LCD_puts ((uint8_t*)" 1 : Reglage A USART");
	LCD_setCursorXY(0,20);
	LCD_puts ((uint8_t*)" 2 : Reglage B USART");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)" B : BACK");
	Usart_Tx_String("\nParamètres A actuels : \n");
	Usart_Tx_String(recurrence_a);
	Usart_Tx_String("\nParamètres B actuels : \n");
	Usart_Tx_String(recurrence_b);
	Usart_Tx_String("\nPour modifier les coefficients A, appuyer sur 1, puis entrer les paramètres sous la forme:\n");
	Usart_Tx_String("00.00000,00.00000,00.00000,00.00000,00.00000,00.00000,00.00000,00.00000,00.00000,00.00000\n");
	Usart_Tx_String("correspondant aux paramètres: a0,a1,a2,a3,a4,a5,a6,a7,a8,a9\n");
	Usart_Tx_String("\nPour modifier les coefficients B, appuyer sur , puis entrer les paramètres sous la forme:\n");
	Usart_Tx_String("00.00000,00.00000,00.00000,00.00000,00.00000,00.00000,00.00000,00.00000,00.00000,00.00000\n");
	Usart_Tx_String("correspondant aux paramètres: b0,b1,b2,b3,b4,b5,b6,b8,b9\n");
	
	return ST_RECURRENCE;
	
}

char Fct_recurrence_change_a(char input)
{
	static unsigned char First = TRUE;
	if(First)
	{
		Usart_Tx_String("Introduiser les paramètres:\n");
		LCD_clr();
		LCD_setCursorXY(35,0);
		LCD_puts ((uint8_t*)"RECURRENCE");
		LCD_setCursorXY(0,10);
		LCD_puts ((uint8_t*)"Introduisez A's usart");
		First=FALSE;
	}
	if(USARTReception)
	{
		strcpy(recurrence_a,bufRS232);
		EEPROM_save_recurrence_a();
		Usart_Tx_String("Paramètres enregistrés !\n");
		USARTReception=FALSE;
		First=TRUE;
		return FCT_RECURRENCE;
	}
	else
	{
		return FCT_RECURRENCE_CHANGE_A;
	}
}

char Fct_recurrence_change_b(char input)
{
	static unsigned char First = TRUE;
	if(First)
	{
		Usart_Tx_String("Introduiser les paramètres:\n");
		LCD_clr();
		LCD_setCursorXY(35,0);
		LCD_puts ((uint8_t*)"RECURRENCE");
		LCD_setCursorXY(0,10);
		LCD_puts ((uint8_t*)"Introduisez B's usart");
		First=FALSE;
	}
	if(USARTReception)
	{
		strcpy(recurrence_b,bufRS232);
		EEPROM_save_recurrence_b();
		Usart_Tx_String("Paramètres enregistrés !\n");
		USARTReception=FALSE;
		First=TRUE;
		return FCT_RECURRENCE;
	}
	else
	{
		return FCT_RECURRENCE_CHANGE_B;
	}
}

char Fct_pid(char input)
{
	LCD_clr();
	LCD_setCursorXY(15,0);
	LCD_puts ((uint8_t*)"PID PARAMETERS");
	LCD_setCursorXY(0,10);
	LCD_puts ((uint8_t*)"1.BP\n");
	LCD_puts ((uint8_t*)"2.Ti\n");
	LCD_puts ((uint8_t*)"3.Td\n");
	LCD_puts ((uint8_t*)"4.Te\n");
	LCD_puts ((uint8_t*)"5.OUT0\n");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)" B : BACK");
	return ST_PID;
}

char Fct_pid_bp(char input)
{
	EEPROM_read_bp();
	char buffer[20];
	LCD_clr();
	LCD_setCursorXY(2,0);
	LCD_puts ((uint8_t*)"Bande Proportionnelle");
	LCD_setCursorXY(0,20);
	itoa(bp[0],buffer,10);
	LCD_puts (buffer);
	itoa(bp[1],buffer,10);
	LCD_puts (buffer);
	itoa(bp[2],buffer,10);
	LCD_puts (buffer);
	LCD_puts ((uint8_t*)"%");
	LCD_setCursorXY(3,40);
	LCD_puts ((uint8_t*)" A : Reglage");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)" B : BACK");	
	return ST_PID_BP;
}

char Fct_pid_bp_change(char input)
{
	input=Previous_Button;
	
	char buffer[20];
	itoa(input,buffer,10);
	Usart_Tx_String(buffer);
	Usart_Tx_String("\n");
	if(position!=0)
	{
		bp[position-1]=input-1;
	}
	else IDCB_Clignotement_bp = OSEnregistrerCB_TIMER(clignotementbp,500);
	LCD_clr();
	LCD_setCursorXY(2,0);
	LCD_puts ((uint8_t*)"Bande Proportionnelle:");
	LCD_setCursorXY(0,20);
	itoa(bp[0],buffer,10);
	LCD_puts (buffer);
	itoa(bp[1],buffer,10);
	LCD_puts (buffer);
	itoa(bp[2],buffer,10);
	LCD_puts (buffer);
	LCD_puts ((uint8_t*)"%");
	
	position++;
	if(position==4)
	{
		position=0;
		EEPROM_save_bp();
		bp_int = (int)bp[2]+(10*((int)bp[1]))+(100*((int)bp[0]));
		itoa(bp_int,buffer,10);
		Usart_Tx_String("Bande Proportionnelle:");
		Usart_Tx_String(buffer);
		Usart_Tx_String(" %");
		Usart_Tx_String("\n");
		
		OSRetirerCB_TIMER(IDCB_Clignotement_bp);
		return FCT_PID_BP;
	}
	else return ST_PID_BP_CHANGE;
	
	
}



char Fct_pid_ti(char input)
{
	EEPROM_read_ti();
	char buffer[20];
	LCD_clr();
	LCD_setCursorXY(2,0);
	LCD_puts ((uint8_t*)"Constante integration");
	LCD_setCursorXY(0,20);
	itoa(ti[0],buffer,10);
	LCD_puts (buffer);
	itoa(ti[1],buffer,10);
	LCD_puts (buffer);
	itoa(ti[2],buffer,10);
	LCD_puts (buffer);
	itoa(ti[3],buffer,10);
	LCD_puts (buffer);
	itoa(ti[4],buffer,10);
	LCD_puts (buffer);
	LCD_setCursorXY(3,40);
	LCD_puts ((uint8_t*)" A : Reglage");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)" B : BACK");
	return ST_PID_TI;
}


char Fct_pid_ti_change(char input)
{
	input=Previous_Button;
	
	char buffer[20];
	itoa(input,buffer,10);
	Usart_Tx_String(buffer);
	Usart_Tx_String("\n");
	if(position!=0)
	{
		ti[position-1]=input-1;
	}
	else IDCB_Clignotement_ti = OSEnregistrerCB_TIMER(clignotementti,500);
	LCD_clr();
	LCD_setCursorXY(2,0);
	LCD_puts ((uint8_t*)"Constante integration:");
	LCD_setCursorXY(0,20);
	itoa(ti[0],buffer,10);
	LCD_puts (buffer);
	itoa(ti[1],buffer,10);
	LCD_puts (buffer);
	itoa(ti[2],buffer,10);
	LCD_puts (buffer);
	itoa(ti[3],buffer,10);
	LCD_puts (buffer);
	itoa(ti[4],buffer,10);
	LCD_puts (buffer);
	
	
	position++;
	if(position==6)
	{
		position=0;
		EEPROM_save_ti();
		ti_int = (int)ti[4]+(10*((int)ti[3]))+(100*((int)ti[2]))+(1000*((int)ti[1]))+(10000*((int)ti[0]));
		itoa(ti_int,buffer,10);
		Usart_Tx_String("Constante integration:");
		Usart_Tx_String(buffer);
		Usart_Tx_String("\n");
		
		OSRetirerCB_TIMER(IDCB_Clignotement_ti);
		return FCT_PID_TI;
	}
	else return ST_PID_TI_CHANGE;
	
	
}


char Fct_pid_td(char input)
{
	EEPROM_read_td();
	char buffer[20];
	LCD_clr();
	LCD_setCursorXY(5,0);
	LCD_puts ((uint8_t*)"Constante derivation");
	LCD_setCursorXY(0,20);
	itoa(td[0],buffer,10);
	LCD_puts (buffer);
	itoa(td[1],buffer,10);
	LCD_puts (buffer);
	itoa(td[2],buffer,10);
	LCD_puts (buffer);
	itoa(td[3],buffer,10);
	LCD_puts (buffer);
	itoa(td[4],buffer,10);
	LCD_puts (buffer);
	LCD_setCursorXY(3,40);
	LCD_puts ((uint8_t*)" A : Reglage");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)" B : BACK");
	return ST_PID_TD;
}


char Fct_pid_td_change(char input)
{
	input=Previous_Button;
	
	char buffer[20];
	itoa(input,buffer,10);
	Usart_Tx_String(buffer);
	Usart_Tx_String("\n");
	if(position!=0)
	{
		td[position-1]=input-1;
	}
	else IDCB_Clignotement_ti = OSEnregistrerCB_TIMER(clignotementti,500);
	LCD_clr();
	LCD_setCursorXY(5,0);
	LCD_puts ((uint8_t*)"Constante derivation:");
	LCD_setCursorXY(0,20);
	itoa(td[0],buffer,10);
	LCD_puts (buffer);
	itoa(td[1],buffer,10);
	LCD_puts (buffer);
	itoa(td[2],buffer,10);
	LCD_puts (buffer);
	itoa(td[3],buffer,10);
	LCD_puts (buffer);
	itoa(td[4],buffer,10);
	LCD_puts (buffer);
	
	
	position++;
	if(position==6)
	{
		position=0;
		EEPROM_save_td();
		td_int = (int)td[4]+(10*((int)td[3]))+(100*((int)td[2]))+(1000*((int)td[1]))+(10000*((int)td[0]));
		itoa(td_int,buffer,10);
		Usart_Tx_String("Constante derivation:");
		Usart_Tx_String(buffer);
		Usart_Tx_String("\n");
		
		OSRetirerCB_TIMER(IDCB_Clignotement_ti);
		return FCT_PID_TD;
	}
	else return ST_PID_TD_CHANGE;
	
	
}


char Fct_pid_te(char input)
{
	EEPROM_read_te();
	char buffer[20];
	LCD_clr();
	LCD_setCursorXY(5,0);
	LCD_puts ((uint8_t*)"Periode echantillon");
	LCD_setCursorXY(0,20);
	itoa(te[0],buffer,10);
	LCD_puts (buffer);
	itoa(te[1],buffer,10);
	LCD_puts (buffer);
	itoa(te[2],buffer,10);
	LCD_puts (buffer);
	itoa(te[3],buffer,10);
	LCD_puts (buffer);
	itoa(te[4],buffer,10);
	LCD_puts (buffer);
	LCD_setCursorXY(3,40);
	LCD_puts ((uint8_t*)" A : Reglage");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)" B : BACK");
	return ST_PID_TE;
}


char Fct_pid_te_change(char input)
{
	input=Previous_Button;
	
	char buffer[20];
	itoa(input,buffer,10);
	Usart_Tx_String(buffer);
	Usart_Tx_String("\n");
	if(position!=0)
	{
		te[position-1]=input-1;
	}
	else IDCB_Clignotement_ti = OSEnregistrerCB_TIMER(clignotementti,500);
	LCD_clr();
	LCD_setCursorXY(5,0);
	LCD_puts ((uint8_t*)"Periode echantillon:");
	LCD_setCursorXY(0,20);
	itoa(te[0],buffer,10);
	LCD_puts (buffer);
	itoa(te[1],buffer,10);
	LCD_puts (buffer);
	itoa(te[2],buffer,10);
	LCD_puts (buffer);
	itoa(te[3],buffer,10);
	LCD_puts (buffer);
	itoa(te[4],buffer,10);
	LCD_puts (buffer);
	
	
	position++;
	if(position==6)
	{
		position=0;
		EEPROM_save_te();
		te_int = (int)te[4]+(10*((int)te[3]))+(100*((int)te[2]))+(1000*((int)te[1]))+(10000*((int)te[0]));
		itoa(te_int,buffer,10);
		Usart_Tx_String("Periode echantillon:");
		Usart_Tx_String(buffer);
		Usart_Tx_String("\n");
		
		OSRetirerCB_TIMER(IDCB_Clignotement_ti);
		return FCT_PID_TE;
	}
	else return ST_PID_TE_CHANGE;
	
	
}


char Fct_pid_out0(char input)
{
	EEPROM_read_out0();
	char buffer[20];
	LCD_clr();
	LCD_setCursorXY(5,0);
	LCD_puts ((uint8_t*)"Commande residuelle");
	LCD_setCursorXY(0,20);
	itoa(out0[0],buffer,10);
	LCD_puts (buffer);
	LCD_puts ((uint8_t*)".");
	itoa(out0[1],buffer,10);
	LCD_puts (buffer);
	itoa(out0[2],buffer,10);
	LCD_puts (buffer);
	LCD_setCursorXY(3,40);
	LCD_puts ((uint8_t*)" A : Reglage");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)" B : BACK");
	return ST_PID_OUT0;
}


char Fct_pid_out0_change(char input)
{
	input=Previous_Button;
	
	char buffer[20];
	itoa(input,buffer,10);
	Usart_Tx_String(buffer);
	Usart_Tx_String("\n");
	if(position!=0)
	{
		out0[position-1]=input-1;
	}
	else IDCB_Clignotement_consigne = OSEnregistrerCB_TIMER(clignotementconsigne,500);
	LCD_clr();
	LCD_setCursorXY(5,0);
	LCD_puts ((uint8_t*)"Commande residuelle:");
	LCD_setCursorXY(0,20);
	itoa(out0[0],buffer,10);
	LCD_puts (buffer);
	LCD_puts ((uint8_t*)".");
	itoa(out0[1],buffer,10);
	LCD_puts (buffer);
	itoa(out0[2],buffer,10);
	LCD_puts (buffer);
	
	
	position++;
	if(position==4)
	{
		position=0;
		EEPROM_save_out0();
		out0_int = (int)out0[2]+(10*((int)out0[1]))+(100*((int)out0[0]));
		itoa(te_int,buffer,10);
		Usart_Tx_String("Commande residuelle:");
		Usart_Tx_String(buffer);
		Usart_Tx_String("\n");
		
		OSRetirerCB_TIMER(IDCB_Clignotement_consigne);
		return FCT_PID_OUT0;
	}
	else return ST_PID_OUT0_CHANGE;
	
	
}


char Fct_hysteresis(char input)
{
	LCD_clr();
	LCD_setCursorXY(1,0);
	LCD_puts ((uint8_t*)"HYSTERESIS PARAMETERS");
	LCD_setCursorXY(3,10);
	LCD_puts ((uint8_t*)"1.SET HIGH");
	LCD_setCursorXY(3,20);
	LCD_puts ((uint8_t*)"2.SET LOW");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)" B : BACK");
	return ST_HYSTERESIS;
}

char Fct_hysteresis_high(char input)
{
	EEPROM_read_hysteresis_high();
	char buffer[20];
	LCD_clr();
	LCD_setCursorXY(45,0);
	LCD_puts ((uint8_t*)"SET HIGH");
	LCD_setCursorXY(0,20);
	itoa(hysteresis_high[0],buffer,10);
	LCD_puts (buffer);
	LCD_puts ((uint8_t*)".");
	itoa(hysteresis_high[1],buffer,10);
	LCD_puts (buffer);
	itoa(hysteresis_high[2],buffer,10);
	LCD_puts (buffer);
	LCD_setCursorXY(3,40);
	LCD_puts ((uint8_t*)" A : Reglage");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)" B : BACK");
	return ST_HYSTERESIS_HIGH;
}


char Fct_hysteresis_high_change(char input)
{
	input=Previous_Button;
	
	char buffer[20];
	itoa(input,buffer,10);
	Usart_Tx_String(buffer);
	Usart_Tx_String("\n");
	if(position!=0)
	{
		hysteresis_high[position-1]=input-1;
	}
	else IDCB_Clignotement_consigne = OSEnregistrerCB_TIMER(clignotementconsigne,500);
	LCD_clr();
	LCD_setCursorXY(35,0);
	LCD_puts ((uint8_t*)"SET HIGH:");
	LCD_setCursorXY(0,20);
	itoa(hysteresis_high[0],buffer,10);
	LCD_puts (buffer);
	LCD_puts ((uint8_t*)".");
	itoa(hysteresis_high[1],buffer,10);
	LCD_puts (buffer);
	itoa(hysteresis_high[2],buffer,10);
	LCD_puts (buffer);
	
	
	position++;
	if(position==4)
	{
		position=0;
		EEPROM_save_hysteresis_high();
		hysteresis_high_int = (int)hysteresis_high[2]+(10*((int)hysteresis_high[1]))+(100*((int)hysteresis_high[0]));
		itoa(hysteresis_high_int,buffer,10);
		Usart_Tx_String("Hysteresis haut:");
		Usart_Tx_String(buffer);
		Usart_Tx_String("\n");
		
		OSRetirerCB_TIMER(IDCB_Clignotement_consigne);
		return FCT_HYSTERESIS_HIGH;
	}
	else return ST_HYSTERESIS_HIGH_CHANGE;
	
	
}


char Fct_hysteresis_low(char input)
{
	EEPROM_read_hysteresis_low();
	char buffer[20];
	LCD_clr();
	LCD_setCursorXY(45,0);
	LCD_puts ((uint8_t*)"SET LOW");
	LCD_setCursorXY(0,20);
	itoa(hysteresis_low[0],buffer,10);
	LCD_puts (buffer);
	LCD_puts ((uint8_t*)".");
	itoa(hysteresis_low[1],buffer,10);
	LCD_puts (buffer);
	itoa(hysteresis_low[2],buffer,10);
	LCD_puts (buffer);
	LCD_setCursorXY(3,40);
	LCD_puts ((uint8_t*)" A : Reglage");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)" B : BACK");
	return ST_HYSTERESIS_LOW;
}


char Fct_hysteresis_low_change(char input)
{
	input=Previous_Button;
	
	char buffer[20];
	itoa(input,buffer,10);
	Usart_Tx_String(buffer);
	Usart_Tx_String("\n");
	if(position!=0)
	{
		hysteresis_low[position-1]=input-1;
	}
	else IDCB_Clignotement_consigne = OSEnregistrerCB_TIMER(clignotementconsigne,500);
	LCD_clr();
	LCD_setCursorXY(35,0);
	LCD_puts ((uint8_t*)"SET LOW:");
	LCD_setCursorXY(0,20);
	itoa(hysteresis_low[0],buffer,10);
	LCD_puts (buffer);
	LCD_puts ((uint8_t*)".");
	itoa(hysteresis_low[1],buffer,10);
	LCD_puts (buffer);
	itoa(hysteresis_low[2],buffer,10);
	LCD_puts (buffer);
	
	
	position++;
	if(position==4)
	{
		position=0;
		EEPROM_save_hysteresis_low();
		hysteresis_low_int = (int)hysteresis_low[2]+(10*((int)hysteresis_low[1]))+(100*((int)hysteresis_low[0]));
		itoa(hysteresis_low_int,buffer,10);
		Usart_Tx_String("Hysteresis bas:");
		Usart_Tx_String(buffer);
		Usart_Tx_String("\n");
		
		OSRetirerCB_TIMER(IDCB_Clignotement_consigne);
		return FCT_HYSTERESIS_LOW;
	}
	else return ST_HYSTERESIS_LOW_CHANGE;
	
	
}



char Fct_time_date(char input)
{
	LCD_clr();
	LCD_setCursorXY(10,0);
	char buffer[20];
	LCD_puts ((uint8_t*)"REGLAGE DATE HEURE");
	LCD_setCursorXY(0,20);
	itoa(hour[0],buffer,10);
	LCD_puts (buffer);
	itoa(hour[1],buffer,10);
	LCD_puts (buffer);
	LCD_puts ((uint8_t*)":");
	itoa(hour[2],buffer,10);
	LCD_puts (buffer);
	itoa(hour[3],buffer,10);
	LCD_puts (buffer);
	LCD_puts ((uint8_t*)":");
	itoa(hour[4],buffer,10);
	LCD_puts (buffer);
	itoa(hour[5],buffer,10);
	LCD_puts (buffer);
	
	LCD_setCursorXY(0,30);
	itoa(date[0],buffer,10);
	LCD_puts (buffer);
	itoa(date[1],buffer,10);
	LCD_puts (buffer);
	LCD_puts ((uint8_t*)"/");
	itoa(date[2],buffer,10);
	LCD_puts (buffer);
	itoa(date[3],buffer,10);
	LCD_puts (buffer);
	LCD_puts ((uint8_t*)"/");
	itoa(date[4],buffer,10);
	LCD_puts (buffer);
	itoa(date[5],buffer,10);
	LCD_puts (buffer);
	itoa(date[6],buffer,10);
	LCD_puts (buffer);
	itoa(date[7],buffer,10);
	LCD_puts (buffer);
	LCD_setCursorXY(3,40);
	LCD_puts ((uint8_t*)" 1 : Reglage HEURE");
	LCD_setCursorXY(3,50);
	LCD_puts ((uint8_t*)" 2 : Reglage DATE");
	LCD_setCursorXY(3,60);
	LCD_puts ((uint8_t*)" B : BACK");
	return ST_TIME_DATE;
}

char Fct_time_change(char input)
{
	input=Previous_Button;
	
	char buffer[20];
	itoa(input,buffer,10);
	Usart_Tx_String(buffer); 
	Usart_Tx_String("\n"); 
	if(position!=0)
	{
		hour[position-1]=input-1;
	}
	else IDCB_Clignotement_heure = OSEnregistrerCB_TIMER(clignotementheure,500);
	LCD_clr();
	LCD_setCursorXY(10,0);
	LCD_puts ((uint8_t*)"Entrer l'heure:");
	LCD_setCursorXY(0,20);
	itoa(hour[0],buffer,10);
	LCD_puts (buffer);
	itoa(hour[1],buffer,10);
	LCD_puts (buffer);
	LCD_puts ((uint8_t*)":");
	itoa(hour[2],buffer,10);
	LCD_puts (buffer);
	itoa(hour[3],buffer,10);
	LCD_puts (buffer);
	LCD_puts ((uint8_t*)":");
	itoa(hour[4],buffer,10);
	LCD_puts (buffer);
	itoa(hour[5],buffer,10);
	LCD_puts (buffer);
	
	position++;
	if(position==7)
	{
		position=0;
		OSRetirerCB_TIMER(IDCB_Clignotement_heure);
		return FCT_TIME_DATE;
	} 
	else return ST_TIME_CHANGE;
}

char Fct_date_change(char input)
{
	input=Previous_Button;
	
	char buffer[20];
	itoa(input,buffer,10);
	Usart_Tx_String(buffer);
	Usart_Tx_String("\n");
	if(position!=0)
	{
		date[position-1]=input-1;
	}
	else IDCB_Clignotement_date = OSEnregistrerCB_TIMER(clignotementdate,500);
	LCD_clr();
	LCD_setCursorXY(10,0);
	LCD_puts ((uint8_t*)"Entrer la date:");
	LCD_setCursorXY(0,20);
	itoa(date[0],buffer,10);
	LCD_puts (buffer);
	itoa(date[1],buffer,10);
	LCD_puts (buffer);
	LCD_puts ((uint8_t*)"/");
	itoa(date[2],buffer,10);
	LCD_puts (buffer);
	itoa(date[3],buffer,10);
	LCD_puts (buffer);
	LCD_puts ((uint8_t*)"/");
	itoa(date[4],buffer,10);
	LCD_puts (buffer);
	itoa(hour[5],buffer,10);
	LCD_puts (buffer);
	itoa(date[6],buffer,10);
	LCD_puts (buffer);
	itoa(hour[7],buffer,10);
	LCD_puts (buffer);
	
	position++;
	if(position==9)
	{
		position=0;
		OSRetirerCB_TIMER(IDCB_Clignotement_date);
		return FCT_TIME_DATE;
	}
	else return ST_DATE_CHANGE;
}