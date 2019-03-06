/*
led display using look up table
*/

// Serial code
#include "lpc17xx_gpio.h"		// Central include files
#include "lpc_types.h"
//#include "serial.h"			// Local functions


void write_leds(int num_out){
  long leds[4];
  leds[0] = 0x40000;
  leds[1] = 0x100000;
  leds[2] = 0x200000;
  leds[3] = 0x800000;
  int i;
  switch (num_out) {
  case 0:
    for(i=0; i<4; i++){
      GPIO_ClearValue(1, leds[i]);
    }
    break;
  case 1:
    write_leds(0);
    GPIO_SetValue(1, leds[0]);
    break;
  case 2:
    write_leds(0);
    GPIO_SetValue(1, leds[1]);
    break;
  case 3:
    write_leds(0);
    GPIO_SetValue(1, leds[0]);
    GPIO_SetValue(1, leds[1]);
    break;
  case 4:
    write_leds(0);
    GPIO_SetValue(1, leds[2]);
    break;
  case 5:
    write_leds(0);
    GPIO_SetValue(1, leds[0]);
    GPIO_SetValue(1, leds[2]);
    break;
  case 6:
    write_leds(0);
    GPIO_SetValue(1, leds[1]);
    GPIO_SetValue(1, leds[2]);
    break;
  case 7:
    write_leds(0);
    GPIO_SetValue(1, leds[0]);
    GPIO_SetValue(1, leds[1]);
    GPIO_SetValue(1, leds[2]);
    break;
  case 8:
    write_leds(0);
    GPIO_SetValue(1, leds[3]);
    break;
  case 9:
    write_leds(0);
    GPIO_SetValue(1, leds[0]);
    GPIO_SetValue(1, leds[3]);
    break;
  case 10:
    write_leds(0);
    GPIO_SetValue(1, leds[1]);
    GPIO_SetValue(1, leds[3]);
    break;
  case 11:
    write_leds(0);
    GPIO_SetValue(1, leds[0]);
    GPIO_SetValue(1, leds[1]);
    GPIO_SetValue(1, leds[3]);
    break;
  case 12:
    write_leds(0);
    GPIO_SetValue(1, leds[2]);
    GPIO_SetValue(1, leds[3]);
    break;
  case 13:
    write_leds(0);
    GPIO_SetValue(1, leds[0]);
    GPIO_SetValue(1, leds[2]);
    GPIO_SetValue(1, leds[3]);
    break;
  case 14:
    write_leds(0);
    GPIO_SetValue(1, leds[1]);
    GPIO_SetValue(1, leds[2]);
    GPIO_SetValue(1, leds[3]);
    break;
  case 15:
    write_leds(0);
    GPIO_SetValue(1, leds[0]);
    GPIO_SetValue(1, leds[1]);
    GPIO_SetValue(1, leds[2]);
    GPIO_SetValue(1, leds[3]);
    break;
  default:
    write_leds(0);
    break;
  }
}

void setup_leds()
{
  long led = 0xB40000;
  GPIO_SetDir(1, led, 1);
}
