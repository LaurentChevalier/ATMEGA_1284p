#ifndef _menu_h_
#define _menu_h_

#include <avr/pgmspace.h>
#include "Main.h"

#ifndef PGM_P
#define PGM_P const rom char *
#endif

typedef struct PROGMEM
{
	unsigned char state;
	unsigned char input;
	unsigned char nextstate;
} MENU_NEXTSTATE;

typedef struct PROGMEM
{
	unsigned char state;
	PGM_P pText;
	char (*pFunc)(char input);
} MENU_STATE;

// Menu text
//const char Txt_START[] PROGMEM 		=	"BONJOUR!";
//const char Txt_RELAY[] PROGMEM		= 	"RELAIS ON/OFF ";
//const char Txt_SWITCH_LED[] PROGMEM =	"CLIGNOT. ON/OFF";

const MENU_NEXTSTATE menu_nextstate[] PROGMEM = {
	//  STATE                       INPUT       NEXT STATE
	// MENUS

	{ST_MENU,                   BOUTON_1,		FCT_AUTO},
	{ST_MENU,                   BOUTON_2,		FCT_MANU},
	{ST_MENU,                   BOUTON_3,		FCT_PARAMETERS},
	
	{ST_AUTO,                   BOUTON_B,		FCT_MENU},
	{ST_AUTO,					BOUTON_A,		FCT_AUTO_CONSIGNE_CHANGE},
		
		{ST_AUTO_CONSIGNE_CHANGE,             BOUTON_0,		FCT_AUTO_CONSIGNE_CHANGE},
		{ST_AUTO_CONSIGNE_CHANGE,             BOUTON_1,		FCT_AUTO_CONSIGNE_CHANGE},
		{ST_AUTO_CONSIGNE_CHANGE,             BOUTON_2,		FCT_AUTO_CONSIGNE_CHANGE},
		{ST_AUTO_CONSIGNE_CHANGE,             BOUTON_3,		FCT_AUTO_CONSIGNE_CHANGE},
		{ST_AUTO_CONSIGNE_CHANGE,             BOUTON_4,		FCT_AUTO_CONSIGNE_CHANGE},
		{ST_AUTO_CONSIGNE_CHANGE,             BOUTON_5,		FCT_AUTO_CONSIGNE_CHANGE},
		{ST_AUTO_CONSIGNE_CHANGE,             BOUTON_6,		FCT_AUTO_CONSIGNE_CHANGE},
		{ST_AUTO_CONSIGNE_CHANGE,             BOUTON_7,		FCT_AUTO_CONSIGNE_CHANGE},
		{ST_AUTO_CONSIGNE_CHANGE,             BOUTON_8,		FCT_AUTO_CONSIGNE_CHANGE},
		{ST_AUTO_CONSIGNE_CHANGE,             BOUTON_9,		FCT_AUTO_CONSIGNE_CHANGE},
		
		
	{ST_MANU,                   BOUTON_B,		FCT_MENU},
	{ST_MANU,                   BOUTON_1,		FCT_IDENTIFICATION},
	{ST_MANU,                   BOUTON_2,		FCT_OUT},
	
		{ST_IDENTIFICATION,                   BOUTON_B,		FCT_MANU},
			
		{ST_OUT,							  BOUTON_B,		FCT_MANU},
		{ST_OUT,							  BOUTON_A,		FCT_OUT_CHANGE},
			
			{ST_OUT_CHANGE,             BOUTON_0,		FCT_OUT_CHANGE},
			{ST_OUT_CHANGE,             BOUTON_1,		FCT_OUT_CHANGE},
			{ST_OUT_CHANGE,             BOUTON_2,		FCT_OUT_CHANGE},
			{ST_OUT_CHANGE,             BOUTON_3,		FCT_OUT_CHANGE},
			{ST_OUT_CHANGE,             BOUTON_4,		FCT_OUT_CHANGE},
			{ST_OUT_CHANGE,             BOUTON_5,		FCT_OUT_CHANGE},
			{ST_OUT_CHANGE,             BOUTON_6,		FCT_OUT_CHANGE},
			{ST_OUT_CHANGE,             BOUTON_7,		FCT_OUT_CHANGE},
			{ST_OUT_CHANGE,             BOUTON_8,		FCT_OUT_CHANGE},
			{ST_OUT_CHANGE,             BOUTON_9,		FCT_OUT_CHANGE},						
				
		
	{ST_PARAMETERS,             BOUTON_B,		FCT_MENU},
	{ST_PARAMETERS,				BOUTON_1,		FCT_CAPTEUR},
	{ST_PARAMETERS,             BOUTON_2,		FCT_OUTPUT},
	{ST_PARAMETERS,             BOUTON_3,		FCT_ALARM},
	{ST_PARAMETERS,             BOUTON_4,		FCT_REG_SETTINGS},
	{ST_PARAMETERS,             BOUTON_5,		FCT_TIME_DATE},	
		
	{ST_CAPTEUR,				BOUTON_B,		FCT_PARAMETERS},
	{ST_CAPTEUR,				BOUTON_1,		FCT_TEMPERATURE},
	{ST_CAPTEUR,				BOUTON_2,		FCT_LUMINOSITE},
	{ST_CAPTEUR,				BOUTON_3,		FCT_HUMIDITE},
	{ST_CAPTEUR,				BOUTON_4,		FCT_ADC},
		
		{ST_TEMPERATURE,				BOUTON_B,		FCT_CAPTEUR},
			
		{ST_LUMINOSITE,					BOUTON_B,		FCT_CAPTEUR},
			
		{ST_HUMIDITE,					BOUTON_B,		FCT_CAPTEUR},
			
		{ST_ADC,						BOUTON_B,		FCT_CAPTEUR},
			
		
	
		
				
	{ST_OUTPUT,                 BOUTON_B,		FCT_PARAMETERS},
	{ST_OUTPUT,                 BOUTON_1,		FCT_PWM},
	{ST_OUTPUT,                 BOUTON_2,		FCT_RELAIS},
	{ST_OUTPUT,                 BOUTON_3,		FCT_ANALOGIQUE},
		
		{ST_PWM,						BOUTON_B,		FCT_OUTPUT},
			
		{ST_RELAIS,					    BOUTON_B,		FCT_OUTPUT},
			
		{ST_ANALOGIQUE,                 BOUTON_B,		FCT_OUTPUT},
	
	
	{ST_ALARM,                  BOUTON_B,		FCT_PARAMETERS},
	{ST_ALARM,                  BOUTON_1,		FCT_ALARME_HIGH},
	{ST_ALARM,                  BOUTON_2,		FCT_ALARME_LOW},
	{ST_ALARM,                  BOUTON_3,		FCT_ALARME_STOP},
	
		{ST_ALARME_HIGH,                  BOUTON_B,		FCT_ALARM},
		{ST_ALARME_HIGH,                  BOUTON_A,		FCT_ALARME_HIGH_CHANGE},
				
			{ST_ALARME_HIGH_CHANGE,             BOUTON_0,		FCT_ALARME_HIGH_CHANGE},
			{ST_ALARME_HIGH_CHANGE,             BOUTON_1,		FCT_ALARME_HIGH_CHANGE},
			{ST_ALARME_HIGH_CHANGE,             BOUTON_2,		FCT_ALARME_HIGH_CHANGE},
			{ST_ALARME_HIGH_CHANGE,             BOUTON_3,		FCT_ALARME_HIGH_CHANGE},
			{ST_ALARME_HIGH_CHANGE,             BOUTON_4,		FCT_ALARME_HIGH_CHANGE},
			{ST_ALARME_HIGH_CHANGE,             BOUTON_5,		FCT_ALARME_HIGH_CHANGE},
			{ST_ALARME_HIGH_CHANGE,             BOUTON_6,		FCT_ALARME_HIGH_CHANGE},
			{ST_ALARME_HIGH_CHANGE,             BOUTON_7,		FCT_ALARME_HIGH_CHANGE},
			{ST_ALARME_HIGH_CHANGE,             BOUTON_8,		FCT_ALARME_HIGH_CHANGE},
			{ST_ALARME_HIGH_CHANGE,             BOUTON_9,		FCT_ALARME_HIGH_CHANGE},									
		
		{ST_ALARME_LOW,					  BOUTON_B,		FCT_ALARM},
		{ST_ALARME_LOW,                   BOUTON_A,		FCT_ALARME_LOW_CHANGE},
		
			{ST_ALARME_LOW_CHANGE,             BOUTON_0,		FCT_ALARME_LOW_CHANGE},
			{ST_ALARME_LOW_CHANGE,             BOUTON_1,		FCT_ALARME_LOW_CHANGE},
			{ST_ALARME_LOW_CHANGE,             BOUTON_2,		FCT_ALARME_LOW_CHANGE},
			{ST_ALARME_LOW_CHANGE,             BOUTON_3,		FCT_ALARME_LOW_CHANGE},
			{ST_ALARME_LOW_CHANGE,             BOUTON_4,		FCT_ALARME_LOW_CHANGE},
			{ST_ALARME_LOW_CHANGE,             BOUTON_5,		FCT_ALARME_LOW_CHANGE},
			{ST_ALARME_LOW_CHANGE,             BOUTON_6,		FCT_ALARME_LOW_CHANGE},
			{ST_ALARME_LOW_CHANGE,             BOUTON_7,		FCT_ALARME_LOW_CHANGE},
			{ST_ALARME_LOW_CHANGE,             BOUTON_8,		FCT_ALARME_LOW_CHANGE},
			{ST_ALARME_LOW_CHANGE,             BOUTON_9,		FCT_ALARME_LOW_CHANGE},
													
				
		
		{ST_ALARME_STOP,                  BOUTON_B,		FCT_ALARM},
			
			
	
	{ST_REG_SETTINGS,           BOUTON_B,		FCT_PARAMETERS},
	{ST_REG_SETTINGS,           BOUTON_1,		FCT_RECURRENCE},
	{ST_REG_SETTINGS,           BOUTON_2,		FCT_PID},
	{ST_REG_SETTINGS,           BOUTON_3,		FCT_HYSTERESIS},
		
		{ST_RECURRENCE,			BOUTON_B,		FCT_REG_SETTINGS},
		{ST_RECURRENCE,			BOUTON_1,		FCT_RECURRENCE_CHANGE_A},
		{ST_RECURRENCE,			BOUTON_2,		FCT_RECURRENCE_CHANGE_B},	
			
		{ST_PID,				BOUTON_B,		FCT_REG_SETTINGS},	
		{ST_PID,				BOUTON_1,		FCT_PID_BP},
		{ST_PID,				BOUTON_2,		FCT_PID_TI},
		{ST_PID,				BOUTON_3,		FCT_PID_TD},
		{ST_PID,				BOUTON_4,		FCT_PID_TE},
		{ST_PID,				BOUTON_5,		FCT_PID_OUT0},
			
			{ST_PID_BP,					BOUTON_B,		FCT_PID},
			{ST_PID_BP,					BOUTON_A,		FCT_PID_BP_CHANGE},
				
				{ST_PID_BP_CHANGE,             BOUTON_0,		FCT_PID_BP_CHANGE},
				{ST_PID_BP_CHANGE,             BOUTON_1,		FCT_PID_BP_CHANGE},
				{ST_PID_BP_CHANGE,             BOUTON_2,		FCT_PID_BP_CHANGE},
				{ST_PID_BP_CHANGE,             BOUTON_3,		FCT_PID_BP_CHANGE},
				{ST_PID_BP_CHANGE,             BOUTON_4,		FCT_PID_BP_CHANGE},
				{ST_PID_BP_CHANGE,             BOUTON_5,		FCT_PID_BP_CHANGE},
				{ST_PID_BP_CHANGE,             BOUTON_6,		FCT_PID_BP_CHANGE},
				{ST_PID_BP_CHANGE,             BOUTON_7,		FCT_PID_BP_CHANGE},
				{ST_PID_BP_CHANGE,             BOUTON_8,		FCT_PID_BP_CHANGE},
				{ST_PID_BP_CHANGE,             BOUTON_9,		FCT_PID_BP_CHANGE},										
				
			{ST_PID_TI,					BOUTON_B,		FCT_PID},
			{ST_PID_TI,					BOUTON_A,		FCT_PID_TI_CHANGE},	
				
				{ST_PID_TI_CHANGE,             BOUTON_0,		FCT_PID_TI_CHANGE},
				{ST_PID_TI_CHANGE,             BOUTON_1,		FCT_PID_TI_CHANGE},
				{ST_PID_TI_CHANGE,             BOUTON_2,		FCT_PID_TI_CHANGE},
				{ST_PID_TI_CHANGE,             BOUTON_3,		FCT_PID_TI_CHANGE},
				{ST_PID_TI_CHANGE,             BOUTON_4,		FCT_PID_TI_CHANGE},
				{ST_PID_TI_CHANGE,             BOUTON_5,		FCT_PID_TI_CHANGE},
				{ST_PID_TI_CHANGE,             BOUTON_6,		FCT_PID_TI_CHANGE},
				{ST_PID_TI_CHANGE,             BOUTON_7,		FCT_PID_TI_CHANGE},
				{ST_PID_TI_CHANGE,             BOUTON_8,		FCT_PID_TI_CHANGE},
				{ST_PID_TI_CHANGE,             BOUTON_9,		FCT_PID_TI_CHANGE},									
				
			{ST_PID_TD,					BOUTON_B,		FCT_PID},
			{ST_PID_TD,					BOUTON_A,		FCT_PID_TD_CHANGE},	
				
				{ST_PID_TD_CHANGE,             BOUTON_0,		FCT_PID_TD_CHANGE},
				{ST_PID_TD_CHANGE,             BOUTON_1,		FCT_PID_TD_CHANGE},
				{ST_PID_TD_CHANGE,             BOUTON_2,		FCT_PID_TD_CHANGE},
				{ST_PID_TD_CHANGE,             BOUTON_3,		FCT_PID_TD_CHANGE},
				{ST_PID_TD_CHANGE,             BOUTON_4,		FCT_PID_TD_CHANGE},
				{ST_PID_TD_CHANGE,             BOUTON_5,		FCT_PID_TD_CHANGE},
				{ST_PID_TD_CHANGE,             BOUTON_6,		FCT_PID_TD_CHANGE},
				{ST_PID_TD_CHANGE,             BOUTON_7,		FCT_PID_TD_CHANGE},
				{ST_PID_TD_CHANGE,             BOUTON_8,		FCT_PID_TD_CHANGE},
				{ST_PID_TD_CHANGE,             BOUTON_9,		FCT_PID_TD_CHANGE},									
			
			{ST_PID_TE,					BOUTON_B,		FCT_PID},
			{ST_PID_TE,					BOUTON_A,		FCT_PID_TE_CHANGE},
				
				{ST_PID_TE_CHANGE,             BOUTON_0,		FCT_PID_TE_CHANGE},
				{ST_PID_TE_CHANGE,             BOUTON_1,		FCT_PID_TE_CHANGE},
				{ST_PID_TE_CHANGE,             BOUTON_2,		FCT_PID_TE_CHANGE},
				{ST_PID_TE_CHANGE,             BOUTON_3,		FCT_PID_TE_CHANGE},
				{ST_PID_TE_CHANGE,             BOUTON_4,		FCT_PID_TE_CHANGE},
				{ST_PID_TE_CHANGE,             BOUTON_5,		FCT_PID_TE_CHANGE},
				{ST_PID_TE_CHANGE,             BOUTON_6,		FCT_PID_TE_CHANGE},
				{ST_PID_TE_CHANGE,             BOUTON_7,		FCT_PID_TE_CHANGE},
				{ST_PID_TE_CHANGE,             BOUTON_8,		FCT_PID_TE_CHANGE},
				{ST_PID_TE_CHANGE,             BOUTON_9,		FCT_PID_TE_CHANGE},										
			
			{ST_PID_OUT0,				BOUTON_B,		FCT_PID},
			{ST_PID_OUT0,				BOUTON_A,		FCT_PID_OUT0_CHANGE},
				
				{ST_PID_OUT0_CHANGE,             BOUTON_0,		FCT_PID_OUT0_CHANGE},
				{ST_PID_OUT0_CHANGE,             BOUTON_1,		FCT_PID_OUT0_CHANGE},
				{ST_PID_OUT0_CHANGE,             BOUTON_2,		FCT_PID_OUT0_CHANGE},
				{ST_PID_OUT0_CHANGE,             BOUTON_3,		FCT_PID_OUT0_CHANGE},
				{ST_PID_OUT0_CHANGE,             BOUTON_4,		FCT_PID_OUT0_CHANGE},
				{ST_PID_OUT0_CHANGE,             BOUTON_5,		FCT_PID_OUT0_CHANGE},
				{ST_PID_OUT0_CHANGE,             BOUTON_6,		FCT_PID_OUT0_CHANGE},
				{ST_PID_OUT0_CHANGE,             BOUTON_7,		FCT_PID_OUT0_CHANGE},
				{ST_PID_OUT0_CHANGE,             BOUTON_8,		FCT_PID_OUT0_CHANGE},
				{ST_PID_OUT0_CHANGE,             BOUTON_9,		FCT_PID_OUT0_CHANGE},
				
			
			
		{ST_HYSTERESIS,			BOUTON_B,		FCT_REG_SETTINGS},		
		{ST_HYSTERESIS,			BOUTON_1,		FCT_HYSTERESIS_HIGH},
		{ST_HYSTERESIS,			BOUTON_2,		FCT_HYSTERESIS_LOW},
			
			{ST_HYSTERESIS_HIGH,		BOUTON_B,		FCT_HYSTERESIS},
			{ST_HYSTERESIS_HIGH,		BOUTON_A,		FCT_HYSTERESIS_HIGH_CHANGE},
				
				{ST_HYSTERESIS_HIGH_CHANGE,             BOUTON_0,		FCT_HYSTERESIS_HIGH_CHANGE},
				{ST_HYSTERESIS_HIGH_CHANGE,             BOUTON_1,		FCT_HYSTERESIS_HIGH_CHANGE},
				{ST_HYSTERESIS_HIGH_CHANGE,             BOUTON_2,		FCT_HYSTERESIS_HIGH_CHANGE},
				{ST_HYSTERESIS_HIGH_CHANGE,             BOUTON_3,		FCT_HYSTERESIS_HIGH_CHANGE},
				{ST_HYSTERESIS_HIGH_CHANGE,             BOUTON_4,		FCT_HYSTERESIS_HIGH_CHANGE},
				{ST_HYSTERESIS_HIGH_CHANGE,             BOUTON_5,		FCT_HYSTERESIS_HIGH_CHANGE},
				{ST_HYSTERESIS_HIGH_CHANGE,             BOUTON_6,		FCT_HYSTERESIS_HIGH_CHANGE},
				{ST_HYSTERESIS_HIGH_CHANGE,             BOUTON_7,		FCT_HYSTERESIS_HIGH_CHANGE},
				{ST_HYSTERESIS_HIGH_CHANGE,             BOUTON_8,		FCT_HYSTERESIS_HIGH_CHANGE},
				{ST_HYSTERESIS_HIGH_CHANGE,             BOUTON_9,		FCT_HYSTERESIS_HIGH_CHANGE},									
				
			{ST_HYSTERESIS_LOW,			BOUTON_B,		FCT_HYSTERESIS},
			{ST_HYSTERESIS_LOW,			BOUTON_A,		FCT_HYSTERESIS_LOW_CHANGE},
				
				{ST_HYSTERESIS_LOW_CHANGE,             BOUTON_0,		FCT_HYSTERESIS_LOW_CHANGE},
				{ST_HYSTERESIS_LOW_CHANGE,             BOUTON_1,		FCT_HYSTERESIS_LOW_CHANGE},
				{ST_HYSTERESIS_LOW_CHANGE,             BOUTON_2,		FCT_HYSTERESIS_LOW_CHANGE},
				{ST_HYSTERESIS_LOW_CHANGE,             BOUTON_3,		FCT_HYSTERESIS_LOW_CHANGE},
				{ST_HYSTERESIS_LOW_CHANGE,             BOUTON_4,		FCT_HYSTERESIS_LOW_CHANGE},
				{ST_HYSTERESIS_LOW_CHANGE,             BOUTON_5,		FCT_HYSTERESIS_LOW_CHANGE},
				{ST_HYSTERESIS_LOW_CHANGE,             BOUTON_6,		FCT_HYSTERESIS_LOW_CHANGE},
				{ST_HYSTERESIS_LOW_CHANGE,             BOUTON_7,		FCT_HYSTERESIS_LOW_CHANGE},
				{ST_HYSTERESIS_LOW_CHANGE,             BOUTON_8,		FCT_HYSTERESIS_LOW_CHANGE},
				{ST_HYSTERESIS_LOW_CHANGE,             BOUTON_9,		FCT_HYSTERESIS_LOW_CHANGE},										
				
		
		
		
	
	{ST_TIME_DATE,              BOUTON_B,		FCT_PARAMETERS},
	{ST_TIME_DATE,              BOUTON_1,		FCT_TIME_CHANGE},
	{ST_TIME_DATE,              BOUTON_2,		FCT_DATE_CHANGE},

			{ST_TIME_CHANGE,             BOUTON_0,		FCT_TIME_CHANGE},
			{ST_TIME_CHANGE,             BOUTON_1,		FCT_TIME_CHANGE},
			{ST_TIME_CHANGE,             BOUTON_2,		FCT_TIME_CHANGE},
			{ST_TIME_CHANGE,             BOUTON_3,		FCT_TIME_CHANGE},
			{ST_TIME_CHANGE,             BOUTON_4,		FCT_TIME_CHANGE},
			{ST_TIME_CHANGE,             BOUTON_5,		FCT_TIME_CHANGE},
			{ST_TIME_CHANGE,             BOUTON_6,		FCT_TIME_CHANGE},
			{ST_TIME_CHANGE,             BOUTON_7,		FCT_TIME_CHANGE},
			{ST_TIME_CHANGE,             BOUTON_8,		FCT_TIME_CHANGE},
			{ST_TIME_CHANGE,             BOUTON_9,		FCT_TIME_CHANGE},
				
			{ST_DATE_CHANGE,             BOUTON_0,		FCT_DATE_CHANGE},
			{ST_DATE_CHANGE,             BOUTON_1,		FCT_DATE_CHANGE},
			{ST_DATE_CHANGE,             BOUTON_2,		FCT_DATE_CHANGE},
			{ST_DATE_CHANGE,             BOUTON_3,		FCT_DATE_CHANGE},
			{ST_DATE_CHANGE,             BOUTON_4,		FCT_DATE_CHANGE},
			{ST_DATE_CHANGE,             BOUTON_5,		FCT_DATE_CHANGE},
			{ST_DATE_CHANGE,             BOUTON_6,		FCT_DATE_CHANGE},
			{ST_DATE_CHANGE,             BOUTON_7,		FCT_DATE_CHANGE},
			{ST_DATE_CHANGE,             BOUTON_8,		FCT_DATE_CHANGE},
			{ST_DATE_CHANGE,             BOUTON_9,		FCT_DATE_CHANGE},	
			
	{0,                        0,          0},
};

const MENU_STATE Menu_State[] PROGMEM = {
	//  STATE                               STATE TEXT                  STATE_FUNC

	// Menu principal
	{FCT_MENU,                          NULL,   		            Fct_menu},
	{ST_MENU,                           NULL,   		            NULL},

	//Auto
	{FCT_AUTO,                          NULL,   		            Fct_auto},
	{ST_AUTO,                           NULL,   		            NULL},
		
		{FCT_AUTO_CONSIGNE_CHANGE,                      NULL,   		            Fct_auto_consigne_change},
		{ST_AUTO_CONSIGNE_CHANGE,                       NULL,   		            NULL},
	
	//Manu	
	{FCT_MANU,                          NULL,   		            Fct_manu},
	{ST_MANU,                           NULL,   		            NULL},
		
		{FCT_IDENTIFICATION,			NULL,						Fct_identification},
		{ST_IDENTIFICATION,			NULL,						NULL},
			
		{FCT_OUT,						NULL,						Fct_out},
		{ST_OUT,						NULL,						NULL},
			
			{FCT_OUT_CHANGE,                      NULL,   		            Fct_out_change},
			{ST_OUT_CHANGE,                       NULL,   		            NULL},

	//Paramètres
	{FCT_PARAMETERS,                    NULL,   		            Fct_parameters},
	{ST_PARAMETERS,                     NULL,   		            NULL},
	
		// Menu paramètres
		
		{FCT_CAPTEUR,						 NULL,						Fct_capteur},
		{ST_CAPTEUR,						 NULL,						NULL},
			
			{FCT_TEMPERATURE,						 NULL,						Fct_temperature},
			{ST_TEMPERATURE,						 NULL,						NULL},
			
			{FCT_LUMINOSITE,						 NULL,						Fct_luminosite},
			{ST_LUMINOSITE,							 NULL,						NULL},
				
			{FCT_HUMIDITE,							 NULL,						Fct_humidite},
			{ST_HUMIDITE,							 NULL,						NULL},
			
			{FCT_ADC,								 NULL,						Fct_adc},
			{ST_ADC,								 NULL,						NULL},
	
		{FCT_OUTPUT,                         NULL,   		            Fct_output},
		{ST_OUTPUT,                          NULL,   		            NULL},
			
			{FCT_PWM,						 NULL,						Fct_pwm},
			{ST_PWM,						 NULL,						NULL},
				
			{FCT_RELAIS,					 NULL,						Fct_relais},
			{ST_RELAIS,						 NULL,						NULL},
				
			{FCT_ANALOGIQUE,				 NULL,						Fct_analogique},
			{ST_ANALOGIQUE,					 NULL,						NULL},

		{FCT_ALARM,                          NULL,   		            Fct_alarme},
		{ST_ALARM,                           NULL,   		            NULL},
			
			{FCT_ALARME_HIGH,                          NULL,   		            Fct_alarme_high},
			{ST_ALARME_HIGH,                           NULL,   		            NULL},
				
				{FCT_ALARME_HIGH_CHANGE,                          NULL,   		            Fct_alarme_high_change},
				{ST_ALARME_HIGH_CHANGE,                           NULL,   		            NULL},
				
			{FCT_ALARME_LOW,                           NULL,   		            Fct_alarme_low},
			{ST_ALARME_LOW,                            NULL,   		            NULL},	
				
				{FCT_ALARME_LOW_CHANGE,                          NULL,   		            Fct_alarme_low_change},
				{ST_ALARME_LOW_CHANGE,                           NULL,   		            NULL},
			
			{FCT_ALARME_STOP,                          NULL,   		            Fct_alarme_stop},
			{ST_ALARME_STOP,                           NULL,   		            NULL},
				

		{FCT_REG_SETTINGS,                   NULL,   		            Fct_reg_settings},
		{ST_REG_SETTINGS,                    NULL,   		            NULL},
			
			{FCT_RECURRENCE,							NULL,						Fct_recurrence},
			{ST_RECURRENCE,								NULL,						NULL},
				
				{FCT_RECURRENCE_CHANGE_A,							NULL,						Fct_recurrence_change_a},
				{ST_RECURRENCE_CHANGE_A,							NULL,						NULL},
				
				{FCT_RECURRENCE_CHANGE_B,							NULL,						Fct_recurrence_change_b},
				{ST_RECURRENCE_CHANGE_B,							NULL,						NULL},
			
			{FCT_PID,									NULL,						Fct_pid},
			{ST_PID,									NULL,						NULL},
				
				
				{FCT_PID_BP,									NULL,						Fct_pid_bp},
				{ST_PID_BP,										NULL,						NULL},
					
					{FCT_PID_BP_CHANGE,                          NULL,   		            Fct_pid_bp_change},
					{ST_PID_BP_CHANGE,                           NULL,   		            NULL},
					
				{FCT_PID_TI,									NULL,						Fct_pid_ti},
				{ST_PID_TI,										NULL,						NULL},
					
					{FCT_PID_TI_CHANGE,                          NULL,   		            Fct_pid_ti_change},
					{ST_PID_TI_CHANGE,                           NULL,   		            NULL},
					
				{FCT_PID_TD,									NULL,						Fct_pid_td},
				{ST_PID_TD,										NULL,						NULL},
					
					{FCT_PID_TD_CHANGE,                          NULL,   		            Fct_pid_td_change},
					{ST_PID_TD_CHANGE,                           NULL,   		            NULL},
					
				{FCT_PID_TE,									NULL,						Fct_pid_te},
				{ST_PID_TE,										NULL,						NULL},
					
					{FCT_PID_TE_CHANGE,                          NULL,   		            Fct_pid_te_change},
					{ST_PID_TE_CHANGE,                           NULL,   		            NULL},
					
				{FCT_PID_OUT0,									NULL,						Fct_pid_out0},
				{ST_PID_OUT0,									NULL,						NULL},
					
					{FCT_PID_OUT0_CHANGE,                        NULL,   		            Fct_pid_out0_change},
					{ST_PID_OUT0_CHANGE,                         NULL,   		            NULL},
					
				
			{FCT_HYSTERESIS,							NULL,						Fct_hysteresis},
			{ST_HYSTERESIS,								NULL,						NULL},
				
				{FCT_HYSTERESIS_HIGH,								NULL,						Fct_hysteresis_high},
				{ST_HYSTERESIS_HIGH,								NULL,						NULL},
					
					{FCT_HYSTERESIS_HIGH_CHANGE,								NULL,						Fct_hysteresis_high_change},
					{ST_HYSTERESIS_HIGH_CHANGE,									NULL,						NULL},
					
				{FCT_HYSTERESIS_LOW,								NULL,						Fct_hysteresis_low},
				{ST_HYSTERESIS_LOW,									NULL,						NULL},
					
					{FCT_HYSTERESIS_LOW_CHANGE,									NULL,						Fct_hysteresis_low_change},
					{ST_HYSTERESIS_LOW_CHANGE,									NULL,						NULL},
						
			
		{FCT_TIME_DATE,                      NULL,   		            Fct_time_date},
		{ST_TIME_DATE,                       NULL,   		            NULL},

			{FCT_TIME_CHANGE,                      NULL,   		            Fct_time_change},
			{ST_TIME_CHANGE,                       NULL,   		            NULL},
			
			{FCT_DATE_CHANGE,                      NULL,   		            Fct_date_change},
			{ST_DATE_CHANGE,                       NULL,   		            NULL},
	
	{0,                                 NULL,                       NULL},
	
};
#endif /* _menu.h */