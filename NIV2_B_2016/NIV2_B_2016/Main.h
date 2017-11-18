#ifndef _main_h_
#define _main_h_

//****************************************
//  CONSIGNES ET OBJECTIFS DU PROGRAMME
//****************************************

// DEFINE 

// Gestion registre par bit unique
#define sbiBF(port,bit)  (port |= (1<<bit))   //set bit in port
#define cbiBF(port,bit)  (port &= ~(1<<bit))  //clear bit in port
#define tbiBF(port,bit)  (port ^= (1<<bit))   //Toggle bit in port
#define TRUE				1
#define FALSE				0
#define NULL				0  

//Définit le nombre maximal de callback de type Chrono
#define	MAXCALLBACKCHRONO		10
#define MAXBUFRS232				100

// Liste des états 
#define FCT_MENU					 10
#define ST_MENU						 11
#define FCT_AUTO					 20
#define ST_AUTO						 21
#define FCT_MANU					 22
#define ST_MANU					     23
#define FCT_PARAMETERS				 24
#define ST_PARAMETERS				 25
#define FCT_CAPTEUR					 28
#define ST_CAPTEUR					 29
#define FCT_OUTPUT					 30
#define ST_OUTPUT					 31
#define FCT_ALARM					 32
#define ST_ALARM					 33
#define FCT_REG_SETTINGS			 34
#define ST_REG_SETTINGS				 35
#define FCT_TIME_DATE				 36
#define ST_TIME_DATE			     37
#define ST_TIME_CHANGE				 38
#define FCT_TIME_CHANGE				 39
#define ST_DATE_CHANGE				 40
#define FCT_DATE_CHANGE				 41
#define ST_AUTO_CONSIGNE_CHANGE		 42
#define FCT_AUTO_CONSIGNE_CHANGE	 43
#define ST_IDENTIFICATION			 44
#define FCT_IDENTIFICATION			 45
#define ST_OUT						 46
#define FCT_OUT						 47
#define ST_RECURRENCE				 48
#define FCT_RECURRENCE				 49 
#define ST_PID						 50
#define FCT_PID						 51
#define ST_HYSTERESIS				 52
#define FCT_HYSTERESIS				 53
#define ST_HYSTERESIS_HIGH			 54
#define FCT_HYSTERESIS_HIGH			 55
#define ST_HYSTERESIS_LOW			 56
#define FCT_HYSTERESIS_LOW			 57
#define ST_PID_BP					 60
#define FCT_PID_BP					 61
#define ST_PID_TI					 62
#define FCT_PID_TI					 63
#define ST_PID_TD					 64
#define FCT_PID_TD					 65
#define ST_PID_TE					 66
#define FCT_PID_TE					 67
#define ST_PID_OUT0					 68
#define FCT_PID_OUT0				 69
#define ST_OUT_CHANGE				 70
#define FCT_OUT_CHANGE				 71
#define ST_TEMPERATURE				 72
#define FCT_TEMPERATURE				 73
#define ST_LUMINOSITE				 74
#define FCT_LUMINOSITE				 75
#define ST_HUMIDITE					 76
#define FCT_HUMIDITE				 77
#define ST_ADC						 78
#define FCT_ADC						 79
#define ST_PWM						 80
#define FCT_PWM						 81
#define ST_RELAIS					 82
#define FCT_RELAIS					 83
#define ST_ANALOGIQUE				 84
#define FCT_ANALOGIQUE				 85
#define ST_ALARME_HIGH				 86
#define FCT_ALARME_HIGH				 87
#define ST_ALARME_LOW				 88
#define FCT_ALARME_LOW				 89
#define ST_ALARME_STOP				 90
#define FCT_ALARME_STOP				 91
#define ST_ALARME_HIGH_CHANGE		 92
#define FCT_ALARME_HIGH_CHANGE		 93
#define ST_ALARME_LOW_CHANGE		 94
#define FCT_ALARME_LOW_CHANGE		 95
#define ST_PID_BP_CHANGE			 96
#define	FCT_PID_BP_CHANGE			 97
#define	ST_PID_TI_CHANGE			 98
#define FCT_PID_TI_CHANGE			 99
#define	ST_PID_TD_CHANGE			 100
#define FCT_PID_TD_CHANGE			 101
#define ST_PID_TE_CHANGE			 102
#define FCT_PID_TE_CHANGE			 103
#define ST_PID_OUT0_CHANGE			 104
#define FCT_PID_OUT0_CHANGE			 105
#define ST_HYSTERESIS_HIGH_CHANGE	 106
#define FCT_HYSTERESIS_HIGH_CHANGE	 107
#define	ST_HYSTERESIS_LOW_CHANGE	 108
#define FCT_HYSTERESIS_LOW_CHANGE	 109
#define ST_RECURRENCE_CHANGE_A     	 110
#define FCT_RECURRENCE_CHANGE_A      111
#define ST_RECURRENCE_CHANGE_B     	 112
#define FCT_RECURRENCE_CHANGE_B      113

enum{NONE,BOUTON_0,BOUTON_1,BOUTON_2,BOUTON_3,BOUTON_4,BOUTON_5,BOUTON_6,BOUTON_7,BOUTON_8,BOUTON_9,BOUTON_A,BOUTON_B,BOUTON_C,BOUTON_D,BOUTON_etoile,BOUTON_dieze};	// Used with the button variable
enum {OFF, ON};

// DECLARATION DES FONCTIONS

// CALLBACKS
void Switch_Led(void);
void clignotementheure(void);
void clignotementdate(void);
void clignotementconsigne(void);
void clignotementbp(void);
void clignotementti(void);
void Desactivation_boutton(void);

// STATE MACHINE

char Fct_menu(char input);
char Fct_auto(char input);
char Fct_manu(char input);
char Fct_parameters(char input);
char Fct_capteur (char input);
char Fct_output(char input);
char Fct_alarme(char input);
char Fct_reg_settings(char input);
char Fct_time_date(char input);
char Fct_time_change(char input);
char Fct_date_change(char input);
char Fct_auto_consigne_change(char input);
char Fct_identification(char input);
char Fct_out(char input);
char Fct_recurrence(char input);
char Fct_recurrence_change_a(char input);
char Fct_recurrence_change_b(char input);
char Fct_pid(char input);
char Fct_hysteresis(char input);
char Fct_hysteresis_high(char input);
char Fct_hysteresis_low(char input);
char Fct_pid_bp(char input);
char Fct_pid_ti(char input);
char Fct_pid_td(char input);
char Fct_pid_te(char input);
char Fct_pid_out0(char input);
char Fct_out_change(char input);
char Fct_temperature(char input);
char Fct_luminosite(char input);
char Fct_humidite(char input);
char Fct_adc(char input);
char Fct_pwm(char input);
char Fct_relais(char input);
char Fct_analogique(char input);
char Fct_alarme_high(char input);
char Fct_alarme_low(char input);
char Fct_alarme_stop(char input);
char Fct_alarme_high_change(char input);
char Fct_alarme_low_change(char input);
char Fct_pid_bp_change(char input);
char Fct_pid_ti_change(char input);
char Fct_pid_td_change(char input);
char Fct_pid_te_change(char input);
char Fct_pid_out0_change(char input);
char Fct_hysteresis_high_change(char input);
char Fct_hysteresis_low_change(char input);

#endif /* _main.h */
