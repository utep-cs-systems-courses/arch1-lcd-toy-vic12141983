#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "libTimer.h"
 
void state_advance(){
  char buzz_state = 0;
   if(switch_1){
     shape_1();
   }
  
  else{
     buzzer_set_period(0);
   }
}

 
 


