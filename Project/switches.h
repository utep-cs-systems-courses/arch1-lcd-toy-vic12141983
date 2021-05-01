#include <msp430.h>
#include "led.h"

#ifndef switches_included                                                      
#define switches_included                                                      




                                                                               
//#define SW1 BIT3                /* switch1 is p1.3 */                          
//#define SWITCHES SW1            /* only 1 switch on this board */
#define SW1 BIT0                 /* DEFINE switches with bits */
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3

#define SWITCHES (SW1|SW2|SW3|SW4) /* 4 switches on this board */
extern char switch_state_down, switch_state_changed,switch_1,switch_2,switch_3,switch_4; /* effectively boolean */

void switch_init();			

void switch_interrupt_handler();

                                                                               
                                                           
#endif // included                                                             
                                                                               
