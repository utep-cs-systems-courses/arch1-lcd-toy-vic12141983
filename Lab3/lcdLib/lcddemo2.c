/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include "libTimer.h"
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);

   drawString5x7(20,20, "Hello", COLOR_GREEN, COLOR_RED);

  //  fillRectangle(30,30, 60, 60, COLOR_ORANGE);
  u_char offset_r = 60, offset_c = 60;
  /* for ( int r = 0; r <=10; r++){
    for (int c = 0; c <= r; c++){
      drawPixel(offset_c+c,offset_r+r, COLOR_ORANGE);
    }
    }*/
   for( int r = 0; r<=60; r++){
    for (int c = 0; c <=60-r; c++){
      drawPixel(offset_c-c,offset_r+r,COLOR_GREEN);
      drawPixel(offset_c+c,offset_r+r,COLOR_GREEN);
    }
  }
  
  for (int r =0; r<=60; r++){
    for (int c = 0; c<=r; c++){
      drawPixel(10 -c, 10+r, COLOR_RED);
    }
  }
  for ( int r = 0; r<=60; r++){
    for ( int c =0; c<=r; c++){
      drawPixel(10+c, offset_r-r, COLOR_RED);     
    }
  }
  /* for ( signed c = -10; c<10;c++){
    drawPixel(20-c,c+20, COLOR_BLACK);
    if(c>0){
      for( signed char r = c; r<=2*r;r++){
	drawPixel(20+c,20+r, COLOR_BLACK);

      }
    }
    }*/
  
}
