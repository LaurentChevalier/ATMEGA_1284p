/*
 * EEPROM_read.h
 *
 * Created: 19-12-16 13:54:39
 *  Author: Laurent
 */ 


#ifndef EEPROM_READ_H_
#define EEPROM_READ_H_

void EEPROM_read_consigne(void);
void EEPROM_read_out(void);
void EEPROM_read_alarme_high(void);
void EEPROM_read_alarme_low(void);
void EEPROM_read_hysteresis_high(void);
void EEPROM_read_hysteresis_low(void);
void EEPROM_read_bp(void);
void EEPROM_read_ti(void);
void EEPROM_read_td(void);
void EEPROM_read_te(void);
void EEPROM_read_out0(void);
void EEPROM_read_recurrence_a(void);
void EEPROM_read_recurrence_b(void);



#endif /* EEPROM_READ_H_ */