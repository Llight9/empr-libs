/*
   for testing only
   not for use
*/

#include "lpc17xx_i2c.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_pincel.h"
#include "lpc17x_uart.h"
#include "lpc17xx_exiti.h"
#include "lpc_types.h"
#include "usbIO.h"

void keypad_init(void);

void keypad_enable(void);

void keypad_disable(void);

char keypad_get(void);

char keypad_convert(int keypadbyte);
