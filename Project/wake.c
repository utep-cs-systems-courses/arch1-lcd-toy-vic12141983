#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#define LED_GREEN BIT6             // P1.6


short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;
u_char helloCol = 10;
u_char nextHelloCol =10;
signed char helloVelocity = 1;

void shape_1(){
 int count =0;
 
 u_char offset_r = 80, offset_c = 60;
  for( int r = 0; r<=50; r++){
    for (int c = 0; c <=50-r; c++){
      drawPixel(offset_c-c,offset_r+r,COLOR_GREEN);
      drawPixel(offset_c+c,offset_r+r,COLOR_GREEN);      
    }
  for (int r =0;r<=50;r++){
      for (int c = 0;c <=50+r; c++){
	drawPixel(offset_c+c,60,COLOR_BLACK);
	drawPixel(offset_c+r,50,COLOR_BLACK);
	drawPixel(offset_c+r,60,COLOR_RED);
	drawPixel(offset_r+c,70,COLOR_RED);
      }
    }    
  }
  
}
void wdt_c_handler()
{
  static int secCount = 0;
  static int dsecCount = 0;
  dsecCount++;
  secCount ++;
  if (secCount == 250) {		/* once/sec */
    secCount = 0;
    fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
    redrawScreen = 1;
  }
  if (dsecCount ==25){
    dsecCount =0;
    nextHelloCol += helloVelocity;
    if ( nextHelloCol > 30 || nextHelloCol <=10) {
      helloVelocity  = -helloVelocity;
      nextHelloCol += helloVelocity;
    }
    redrawScreen =1;
  }
}
  

void main(){
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight; //LCD 

  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_BLUE);
  shape_1();
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      drawString5x7(helloCol,20, "hello", COLOR_BLUE, COLOR_BLACK);
      drawString5x7(nextHelloCol,20, "hello", fontFgColor, COLOR_BLUE);
      helloCol = nextHelloCol;
    
    }
    
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
 
 } 
}

    
    



