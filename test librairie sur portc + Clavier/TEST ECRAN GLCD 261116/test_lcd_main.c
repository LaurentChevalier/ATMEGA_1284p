
//*****************************************************************************
//
// Work File    : main.c
// Description	: Test module for KS0107 driven LCD display
// Author	: Sami Varjo
// Created	: 2008-06-23
// Revised	: 2008-06-28
// Version	: 0.2
// Target MCU	: Atmel AVR series - ATMEGA 5815 (or equivalent);
//
// This code is distributed under the GNU Public License
// which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************
#ifndef F_CPU
//#define F_CPU 1000000UL  //CPU speed 8Mhz (for delay.h)
//#define F_CPU  7372800UL   //Atmega5815 8PU  7.3728MHz
//#define F_CPU 14745600UL //Atmega8    14.7456MHz
#define F_CPU 8000000UL
#endif

#include <util/delay.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "lcd_driver_KS0107.h"
#include "lcd_graphics.h"
#include "girl_1_glcd.h"
#include "atmel_glcd.h"

#include "arial_bold_14.h"
#include "corsiva_12.h"
#include "Hardware.h"

void wait_100x_ms(int ms) { uint8_t i; for (i=0;i<ms;i++) _delay_ms(100); }
void drawTest(int type);

volatile unsigned char Button ;

int main(void)
{
  LCD_init();
  
  	/* Initialisation du I/O */
  	
  	initialize_entree();
	initialize_sortie();
	
	PCICR |= (1<<PCIE1);
	PCMSK1 |= (1<<PCINT12) | (1<<PCINT13) | (1<<PCINT14) | (1<<PCINT15) ;
	sei ();
	LCD_clr();
	LCD_setCursorXY(15,0);
	LCD_puts ((uint8_t*)"GLCD_TEST");
  
	 while(1) {    
		switch (Button){
		case BOUTON_0 :
		 LCD_clr();
		 LCD_setCursorXY(15,0);
		 LCD_puts ((uint8_t*)"Bouton 0\0");
		Button=0;
		break;
	
		case BOUTON_1 :
		LCD_clr();
		LCD_setCursorXY(15,0);
		LCD_puts ((uint8_t*)"Bouton 1\0");
		Button=0;
		break;
	
		case BOUTON_2 :
		LCD_clr();
		LCD_setCursorXY(15,0);
		LCD_puts ((uint8_t*)"Bouton 2\0");
		Button=0;
		break;
	
		case BOUTON_3 :
		LCD_clr();
		LCD_setCursorXY(15,0);
		LCD_puts ((uint8_t*)"Bouton 3\0");
		Button=0;
		break;
	
		case BOUTON_4 :
		LCD_clr();
		LCD_setCursorXY(15,0);
		LCD_puts ((uint8_t*)"Bouton 4\0");
		Button=0;
		break;
	
		case BOUTON_5 :
		LCD_clr();
		LCD_setCursorXY(15,0);
		LCD_puts ((uint8_t*)"Bouton 5\0");
		Button=0;
		break;
	
		case BOUTON_6 :
		LCD_clr();
		LCD_setCursorXY(15,0);
		LCD_puts ((uint8_t*)"Bouton 6\0");
		Button=0;
		break;
	
		case BOUTON_7 :
		LCD_clr();
		LCD_setCursorXY(15,0);
		LCD_puts ((uint8_t*)"Bouton 7\0");
		Button=0;
		break;
	
		case BOUTON_8 :
		LCD_clr();
		LCD_setCursorXY(15,0);
		LCD_puts ((uint8_t*)"Bouton 8\0");
		Button=0;
		break;
	
		case BOUTON_9 :
		LCD_clr();
		LCD_setCursorXY(15,0);
		LCD_puts ((uint8_t*)"Bouton 9\0");
		Button=0;
		break;
	
		case BOUTON_etoile :
		LCD_clr();
		LCD_setCursorXY(15,0);
		LCD_puts ((uint8_t*)"Bouton etoile\0");
		Button=0;
		break;
	
		case BOUTON_dieze :
		LCD_clr();
		LCD_setCursorXY(15,0);
		LCD_puts ((uint8_t*)"Bouton dieze\0");
		Button=0;
		break;
	
		case BOUTON_A :
		LCD_clr();
		LCD_setCursorXY(15,0);
		LCD_puts ((uint8_t*)"Bouton A\0");
		Button=0;
		break;
	
		case BOUTON_B :
		LCD_clr();
		LCD_setCursorXY(15,0);
		LCD_puts ((uint8_t*)"Bouton B\0");
		Button=0;
		break;
	
		case BOUTON_C :
		LCD_clr();
		LCD_setCursorXY(15,0);
		LCD_puts ((uint8_t*)"Bouton C\0");
		Button=0;
		break;
	
		case BOUTON_D :
		LCD_clr();
		LCD_setCursorXY(15,0);
		LCD_puts ((uint8_t*)"Bouton D\0");
		break;
	}
  }
}
    /*drawTest(0); //simple text    
    drawTest(1); //simple drawing
    drawTest(2); //more simple drawing
    drawTest(6); //simple progress bar
    drawTest(3); //scrolling text up-down
    drawTest(4); //menus with invert
    drawTest(5); //reading status of LCD
    drawTest(7); //128x64 bmp on screen   
    drawTest(8); //put a bmp on screen (atmel picture is 108x35)    
    drawTest(9);
  }  
  return 0;
}

void drawTest(int type){
  uint8_t i,j;
  
  uint8_t menuStrings[5][15] = {"Automatique\0","Manuel\0","Parametres\0","Pizza\0","Exit\0"};
  
  switch (type){

  case 0: //simple text on screen
    LCD_clr();
    LCD_setCursorXY(15,0);
    LCD_puts ((uint8_t*)"Hello AVR world!\0");
    LCD_putsp((uint8_t*)"This LCD uses KS0107\0",3,3);
    LCD_putsp((uint8_t*)"Too long paged text is wrapped automatically\0",5,3);
    wait_100x_ms(30);
    break;

  case 1: //some of the drawing functions
    LCD_clr();
    LCD_drawLine(0,0,127,63);
    LCD_drawLine(0,63,127,0);
    LCD_drawRect(10,10,117,53);
    LCD_fillCirc(63,31,15);
    wait_100x_ms(20);

    break;

  case 2: //write on screen byte by byte
     for(j=0;j<8;j++){
	LCD_setCursorXY(0,j*8);
	for(i=0;i<LCD_LINE_LENGTH/4;i++){	  
	  LCD_writeByte(0b00110011);
	  LCD_writeByte(0b00110011);
	  LCD_writeByte(0b11001100);
	  LCD_writeByte(0b11001100);
	}
     }
    wait_100x_ms(20);
    break;

  case 3: //scrolling text up->down
    LCD_clr();
    LCD_setCursorXY(0,0);
    LCD_puts((uint8_t*)"Scrolling text\n goes here..!\0");      
    i=63;
    j=110;
    while(j>0){
      _delay_ms(30);      
      LCD_selectLeftChip();
      LCD_setInitialLineAddress(i);
      LCD_selectRightChip();
      LCD_setInitialLineAddress(i);
      if (i==0) i=63;
      else i--;
      j--;
    }
    LCD_clr();
    LCD_selectLeftChip();
    LCD_setInitialLineAddress(0);
    LCD_selectRightChip();
    LCD_setInitialLineAddress(0);
    break;

  case 4:  //using invert for menus
    
    for(i=0;i<5;i++){
      LCD_putsp(menuStrings[i],i+1,25);
    }
    j=2;
    while(j--){
      LCD_invertPage(1,20,100);
      wait_100x_ms(3);
      for(i=0;i<5;i++){      
	wait_100x_ms(3);
	LCD_invertPage(i+1,20,100);
	if(i<4)
	  LCD_invertPage(i+2,20,100);
	wait_100x_ms(3);
      }
    }
    break;

  case 5: //read status (on /off)
    j=4;
    while(j--){
      LCD_clr();
      if(!LCD_isOff()){
	LCD_putsp((uint8_t*)"LCD is On\0",1,10);
	wait_100x_ms(5);
	LCD_off();
      }
      else {
	wait_100x_ms(5);
	LCD_on();
	LCD_putsp((uint8_t*)"LCD was Off\0",1,10);
	wait_100x_ms(5);
      }
    }
    break;

  case 6: //"progress bar"
    LCD_clr();
    LCD_drawRect(5,5,122,58);
    LCD_putsp((uint8_t*)"Prosessing...\0",2,16);
    LCD_drawRect(10,30,113,41);

    for(j=0;j<100;j++){     
      LCD_setCursorXY(12+j,32);
      LCD_writeByte(0xff);
      wait_100x_ms(1); 
    }
    LCD_putsp((uint8_t*)"Done!        \0",2,16);
    wait_100x_ms(10);
    break;

  case 7:
    LCD_clr();
    LCD_drawFullBMP(girl_1_glcd_bmp);
    wait_100x_ms(20);
    break;

  case 8:
    i=0b10101010;
    LCD_clr();
    LCD_drawBMP((uint8_t*)atmel_glcd_bmp, 12, 12, 
		  ATMEL_GLCD_WIDTH,ATMEL_GLCD_HEIGHT);

    wait_100x_ms(20);
    break;
 //(uint8_t*)
  case 9:
    LCD_clr();
    
    //LCD_putgstr((uint8_t*)"Corsiva 12 test", Corsiva_12,10,10);
    //LCD_putgstr((uint8_t*)"qwertyhjkl12345", Corsiva_12,12,30);
    
    LCD_putgstr((uint8_t*)"putgstr() test",Arial_Bold_14,10,10);
    LCD_putgstr((uint8_t*)"1q2w3e4r5t6y8u9i0l",Arial_Bold_14,10,30);

    wait_100x_ms(20);
  }
}*/

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
ISR (PCINT1_vect){

	Button = NONE;
	
	/*Check 1st Column */
	
	cbiBF(PORTB,0);
	sbiBF(PORTB,1);
	sbiBF(PORTB,2);
	sbiBF(PORTB,3);
	if(~PINB & 0b10000000)	Button=BOUTON_etoile;
	if(~PINB & 0b01000000)  Button=BOUTON_7;
	if(~PINB & 0b00100000)  Button=BOUTON_4;
	if(~PINB & 0b00010000)  Button=BOUTON_1;

	/*Check 2st Column */
	sbiBF(PORTB,0);
	cbiBF(PORTB,1);
	if(~PINB & 0b10000000)	Button=BOUTON_0;
	if(~PINB & 0b10000000)	Button=BOUTON_0;
	if(~PINB & 0b01000000)  Button=BOUTON_8;
	if(~PINB & 0b00100000)  Button=BOUTON_5;
	if(~PINB & 0b00010000)  Button=BOUTON_2;
	
	/*Check 3st Column */
	sbiBF(PORTB,1);
	cbiBF (PORTB,2);
	if(~PINB & 0b10000000)	Button=BOUTON_dieze;
	if(~PINB & 0b10000000)	Button=BOUTON_dieze;
	if(~PINB & 0b01000000)  Button=BOUTON_9;
	if(~PINB & 0b00100000)  Button=BOUTON_6;
	if(~PINB & 0b00010000)  Button=BOUTON_3;
	
	/*Check 4st Column */
	sbiBF(PORTB,2);
	cbiBF (PORTB,3);
	if(~PINB & 0b10000000)	Button=BOUTON_D;
	if(~PINB & 0b10000000)	Button=BOUTON_D;
	if(~PINB & 0b01000000)  Button=BOUTON_C;
	if(~PINB & 0b00100000)  Button=BOUTON_B;
	if(~PINB & 0b00010000)  Button=BOUTON_A;
	
	/*Port à zéro */
	cbiBF (PORTB, 0);
	cbiBF (PORTB, 1);
	cbiBF (PORTB, 2);
	//cbiBF (PORTB, 3);
}