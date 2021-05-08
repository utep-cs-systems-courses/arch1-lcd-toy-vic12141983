#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "p2switches.h"

#define LED_GREEN BIT6             // P1.6


short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;
u_char helloCol = 10;
u_char nextHelloCol =10;
signed char helloVelocity = 1;

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
void advance(){
  u_int switches  = p2sw_read();
  char str[5];

  str[0] = (switches & (1<<0)) ? 0 :1;
  str[1] = (switches & (1<<1)) ? 0 :1;
  str[2] = (switches & (1<<2)) ? 0 :1;
  str[3] = (switches & (1<<3)) ? 0 :1;
  if (str[0]){
    shape_1();
  }
  else if(str[1]){
    shape_2();
  }
  else if(str[2]){
    shape_2();
  }
  else if(str[3]){
    shape_2();
  }
  else {
    clearScreen(COLOR_BLACK);
  }
}
  

void main(){
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  p2sw_init(15);
  lcd_init();
  
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  clearScreen(COLOR_BLUE);
  
    while (1) {
     advance();   
    
    if (redrawScreen) {
      redrawScreen = 0;
      drawString5x7(helloCol,20, "hello", COLOR_BLACK, COLOR_BLACK);
      drawString5x7(nextHelloCol,20, "hello", fontFgColor, COLOR_BLUE);
      helloCol = nextHelloCol;
      }
        P1OUT &= ~LED_GREEN;	/* green off*/ 
     or_sr(0x10);		/**< CPU OFF **/
    P1OUT |= LED_GREEN;		/* green on*/ 
    }

}
    
    



