/*
 * EEPROM_save.h
 *
 * Created: 19-12-16 13:56:53
 *  Author: Laurent
 */ 


#ifndef EEPROM_SAVE_H_
#define EEPROM_SAVE_H_

void EEPROM_save_consigne(void);
void EEPROM_save_out(void);
void EEPROM_save_alarme_high(void);
void EEPROM_save_alarme_low(void);
void EEPROM_save_hysteresis_high(void);
void EEPROM_save_hysteresis_low(void);
void EEPROM_save_bp(void);
void EEPROM_save_ti(void);
void EEPROM_save_td(void);
void EEPROM_save_te(void);
void EEPROM_save_out0(void);
void EEPROM_save_recurrence_a(void);
void EEPROM_save_recurrence_b(void);



#endif /* EEPROM_SAVE_H_ */