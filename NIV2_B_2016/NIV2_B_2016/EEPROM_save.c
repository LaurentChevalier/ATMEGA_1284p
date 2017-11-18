/*
 * EEPROM_save.c
 *
 * Created: 19-12-16 13:49:08
 *  Author: Laurent
 */ 

#include <avr/pgmspace.h>
#include "EEPROM_routines.h"
#include "EEPROM_save.h"

extern unsigned char data_array[100];
extern unsigned char consigne[3];
extern unsigned char out[3];
extern unsigned char alarme_high[3];
extern unsigned char alarme_low[3];
extern unsigned char hysteresis_high[3];
extern unsigned char hysteresis_low[3];
extern unsigned char bp[3];
extern unsigned char ti[5];
extern unsigned char td[5];
extern unsigned char te[5];
extern unsigned char out0[3];
extern unsigned char recurrence_a[90];
extern unsigned char recurrence_b[90];

void EEPROM_save_consigne(void)
{
	data_array[0]=consigne[0];
	data_array[1]=consigne[1];
	data_array[2]=consigne[2];
	EEPROM_write(0,0,3);
}

void EEPROM_save_out(void)
{
	data_array[0]=out[0];
	data_array[1]=out[1];
	data_array[2]=out[2];
	EEPROM_write(0,3,3);
}

void EEPROM_save_alarme_high(void)
{
	data_array[0]=alarme_high[0];
	data_array[1]=alarme_high[1];
	data_array[2]=alarme_high[2];
	EEPROM_write(0,6,3);
}

void EEPROM_save_alarme_low(void)
{
	data_array[0]=alarme_low[0];
	data_array[1]=alarme_low[1];
	data_array[2]=alarme_low[2];
	EEPROM_write(0,9,3);
}

void EEPROM_save_hysteresis_high(void)
{
	data_array[0]=hysteresis_high[0];
	data_array[1]=hysteresis_high[1];
	data_array[2]=hysteresis_high[2];
	EEPROM_write(0,12,3);
}

void EEPROM_save_hysteresis_low(void)
{
	data_array[0]=hysteresis_low[0];
	data_array[1]=hysteresis_low[1];
	data_array[2]=hysteresis_low[2];
	EEPROM_write(0,15,3);
}

void EEPROM_save_bp(void)
{
	data_array[0]=bp[0];
	data_array[1]=bp[1];
	data_array[2]=bp[2];
	EEPROM_write(0,18,3);
}

void EEPROM_save_ti(void)
{
	data_array[0]=ti[0];
	data_array[1]=ti[1];
	data_array[2]=ti[2];
	data_array[3]=ti[3];
	data_array[4]=ti[4];
	EEPROM_write(0,21,5);
}

void EEPROM_save_td(void)
{
	data_array[0]=td[0];
	data_array[1]=td[1];
	data_array[2]=td[2];
	data_array[3]=td[3];
	data_array[4]=td[4];
	EEPROM_write(0,26,5);
}

void EEPROM_save_te(void)
{
	data_array[0]=te[0];
	data_array[1]=te[1];
	data_array[2]=te[2];
	data_array[3]=te[3];
	data_array[4]=te[4];
	EEPROM_write(0,31,5);
}

void EEPROM_save_out0(void)
{
	data_array[0]=out0[0];
	data_array[1]=out0[1];
	data_array[2]=out0[2];
	EEPROM_write(0,36,3);
}

void EEPROM_save_recurrence_a(void)
{
	data_array[0]=recurrence_a[0];
	data_array[1]=recurrence_a[1];
	data_array[2]=recurrence_a[2];
	data_array[3]=recurrence_a[3];
	data_array[4]=recurrence_a[4];
	data_array[5]=recurrence_a[5];
	data_array[6]=recurrence_a[6];
	data_array[7]=recurrence_a[7];
	data_array[8]=recurrence_a[8];
	data_array[9]=recurrence_a[9];
	data_array[10]=recurrence_a[10];
	data_array[11]=recurrence_a[11];
	data_array[12]=recurrence_a[12];
	data_array[13]=recurrence_a[13];
	
	data_array[14]=recurrence_a[14];
	data_array[15]=recurrence_a[15];
	data_array[16]=recurrence_a[16];
	data_array[17]=recurrence_a[17];
	data_array[18]=recurrence_a[18];
	data_array[19]=recurrence_a[19];
	data_array[20]=recurrence_a[20];
	data_array[21]=recurrence_a[21];
	data_array[22]=recurrence_a[22];
	data_array[23]=recurrence_a[23];
	data_array[24]=recurrence_a[24];
	data_array[25]=recurrence_a[25];
	data_array[26]=recurrence_a[26];
	data_array[27]=recurrence_a[27];
	
	data_array[28]=recurrence_a[28];
	data_array[29]=recurrence_a[29];
	data_array[30]=recurrence_a[30];
	data_array[31]=recurrence_a[31];
	data_array[32]=recurrence_a[32];
	data_array[33]=recurrence_a[33];
	data_array[34]=recurrence_a[34];
	data_array[35]=recurrence_a[35];
	data_array[36]=recurrence_a[36];
	data_array[37]=recurrence_a[37];
	data_array[38]=recurrence_a[38];
	data_array[39]=recurrence_a[39];
	data_array[40]=recurrence_a[40];
	data_array[41]=recurrence_a[41];
	
	data_array[42]=recurrence_a[42];
	data_array[43]=recurrence_a[43];
	data_array[44]=recurrence_a[44];
	data_array[45]=recurrence_a[45];
	data_array[46]=recurrence_a[46];
	data_array[47]=recurrence_a[47];
	data_array[48]=recurrence_a[48];
	data_array[49]=recurrence_a[49];
	data_array[50]=recurrence_a[50];
	data_array[51]=recurrence_a[51];
	data_array[52]=recurrence_a[52];
	data_array[53]=recurrence_a[53];
	data_array[54]=recurrence_a[54];
	data_array[55]=recurrence_a[55];
	
	data_array[56]=recurrence_a[56];
	data_array[57]=recurrence_a[57];
	data_array[58]=recurrence_a[58];
	data_array[59]=recurrence_a[59];
	data_array[60]=recurrence_a[60];
	data_array[61]=recurrence_a[61];
	data_array[62]=recurrence_a[62];
	data_array[63]=recurrence_a[63];
	data_array[64]=recurrence_a[64];
	data_array[65]=recurrence_a[65];
	data_array[66]=recurrence_a[66];
	data_array[67]=recurrence_a[67];
	data_array[68]=recurrence_a[68];
	data_array[69]=recurrence_a[69];
	
	data_array[70]=recurrence_a[70];
	data_array[71]=recurrence_a[71];
	data_array[72]=recurrence_a[72];
	data_array[73]=recurrence_a[73];
	data_array[74]=recurrence_a[74];
	data_array[75]=recurrence_a[75];
	data_array[76]=recurrence_a[76];
	data_array[77]=recurrence_a[77];
	data_array[78]=recurrence_a[78];
	data_array[79]=recurrence_a[79];
	data_array[80]=recurrence_a[80];
	data_array[81]=recurrence_a[81];
	data_array[82]=recurrence_a[82];
	data_array[83]=recurrence_a[83];
	
	data_array[84]=recurrence_a[84];
	data_array[85]=recurrence_a[85];
	data_array[86]=recurrence_a[86];
	data_array[87]=recurrence_a[87];
	data_array[88]=recurrence_a[88];
	
	EEPROM_write(0,128,89);
}

void EEPROM_save_recurrence_b(void)
{
	data_array[0]=recurrence_b[0];
	data_array[1]=recurrence_b[1];
	data_array[2]=recurrence_b[2];
	data_array[3]=recurrence_b[3];
	data_array[4]=recurrence_b[4];
	data_array[5]=recurrence_b[5];
	data_array[6]=recurrence_b[6];
	data_array[7]=recurrence_b[7];
	data_array[8]=recurrence_b[8];
	data_array[9]=recurrence_b[9];
	data_array[10]=recurrence_b[10];
	data_array[11]=recurrence_b[11];
	data_array[12]=recurrence_b[12];
	data_array[13]=recurrence_b[13];
	
	data_array[14]=recurrence_b[14];
	data_array[15]=recurrence_b[15];
	data_array[16]=recurrence_b[16];
	data_array[17]=recurrence_b[17];
	data_array[18]=recurrence_b[18];
	data_array[19]=recurrence_b[19];
	data_array[20]=recurrence_b[20];
	data_array[21]=recurrence_b[21];
	data_array[22]=recurrence_b[22];
	data_array[23]=recurrence_b[23];
	data_array[24]=recurrence_b[24];
	data_array[25]=recurrence_b[25];
	data_array[26]=recurrence_b[26];
	data_array[27]=recurrence_b[27];

	data_array[28]=recurrence_b[28];
	data_array[29]=recurrence_b[29];
	data_array[30]=recurrence_b[30];
	data_array[31]=recurrence_b[31];
	data_array[32]=recurrence_b[32];
	data_array[33]=recurrence_b[33];
	data_array[34]=recurrence_b[34];
	data_array[35]=recurrence_b[35];
	data_array[36]=recurrence_b[36];
	data_array[37]=recurrence_b[37];
	data_array[38]=recurrence_b[38];
	data_array[39]=recurrence_b[39];
	data_array[40]=recurrence_b[40];
	data_array[41]=recurrence_b[41];
	
	data_array[42]=recurrence_b[42];
	data_array[43]=recurrence_b[43];
	data_array[44]=recurrence_b[44];
	data_array[45]=recurrence_b[45];
	data_array[46]=recurrence_b[46];
	data_array[47]=recurrence_b[47];
	data_array[48]=recurrence_b[48];
	data_array[49]=recurrence_b[49];
	data_array[50]=recurrence_b[50];
	data_array[51]=recurrence_b[51];
	data_array[52]=recurrence_b[52];
	data_array[53]=recurrence_b[53];
	data_array[54]=recurrence_b[54];
	data_array[55]=recurrence_b[55];
	
	data_array[56]=recurrence_b[56];
	data_array[57]=recurrence_b[57];
	data_array[58]=recurrence_b[58];
	data_array[59]=recurrence_b[59];
	data_array[60]=recurrence_b[60];
	data_array[61]=recurrence_b[61];
	data_array[62]=recurrence_b[62];
	data_array[63]=recurrence_b[63];
	data_array[64]=recurrence_b[64];
	data_array[65]=recurrence_b[65];
	data_array[66]=recurrence_b[66];
	data_array[67]=recurrence_b[67];
	data_array[68]=recurrence_b[68];
	data_array[69]=recurrence_b[69];
	
	data_array[70]=recurrence_b[70];
	data_array[71]=recurrence_b[71];
	data_array[72]=recurrence_b[72];
	data_array[73]=recurrence_b[73];
	data_array[74]=recurrence_b[74];
	data_array[75]=recurrence_b[75];
	data_array[76]=recurrence_b[76];
	data_array[77]=recurrence_b[77];
	data_array[78]=recurrence_b[78];
	data_array[79]=recurrence_b[79];
	data_array[80]=recurrence_b[80];
	data_array[81]=recurrence_b[81];
	data_array[82]=recurrence_b[82];
	data_array[83]=recurrence_b[83];
	
	data_array[84]=recurrence_b[84];
	data_array[85]=recurrence_b[85];
	data_array[86]=recurrence_b[86];
	data_array[87]=recurrence_b[87];
	data_array[88]=recurrence_b[88];
	
	EEPROM_write(1,0,89);
}


