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
signed char helloVelocity = 1; // move one pixel to right

void wdt_c_handler()
{
  static int secCount = 0; // timer 
  static int dsecCount = 0;//
  dsecCount++;
  secCount ++;
  if (secCount == 250) { // reset counter 
    secCount = 0;
    fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN; // change font Color
    redrawScreen = 1; // set redrawScreen to meanin screen was redrawn 
  }
  if (dsecCount ==25){ // if 25 reset counter
    dsecCount =0;
    nextHelloCol += helloVelocity; // Add Variables
    if ( nextHelloCol > 30 || nextHelloCol <=10) {// reverse direction
      helloVelocity  = -helloVelocity;
      nextHelloCol += helloVelocity;
    }
    redrawScreen =1; // screen redrawn. (interrupt)
  }
}
/*void change_to_triangle(){
  static char state;
  if(redrawScreecn){
    redrawScreen = 0;
    switch(state){
    case 0:
    }
    }*/
  
void advance(){
  u_int switches  = p2sw_read();
  char str[5];
  // Corresponding switches 1,2,3,4
  str[0] = (switches & (1<<0)) ? 0 :1; 
  str[1] = (switches & (1<<1)) ? 0 :1;
  str[2] = (switches & (1<<2)) ? 0 :1;
  str[3] = (switches & (1<<3)) ? 0 :1;
  // If button 1 is pressed then shape_1() is drawn to the screen
  // After it is released the Screen is cleared. 
  if (str[0]){
    shape1();  
  }
  
  else if(str[1]){
    shape2();
  }
  else if(str[2]){
   shape3();
  }
  else if(str[3]){
    shape4();
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
  clearScreen(COLOR_BLACK);
  
    while (1) {
      assy_change();
      advance();
    
     if (redrawScreen) {    /*If screen is set to 1 */          
      redrawScreen = 0;     /* set it to 0 or off */
      drawString11x16(helloCol,20, "WELCOME", COLOR_BLACK, COLOR_BLACK);
      drawString11x16(nextHelloCol,20, "WELCOME", fontFgColor, COLOR_BLACK);
      helloCol = nextHelloCol;
      }
        P1OUT &= ~LED_GREEN;	/* green off*/ 
     or_sr(0x10);		/**< CPU OFF **/
    P1OUT |= LED_GREEN;		/* green on*/ 
    }

}
    
    



