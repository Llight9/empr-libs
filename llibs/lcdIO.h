/*
library for writing to the lcd
*/

#include "lpc17xx_i2c.h"
#include "lpc17xx_pinsel.h"
#include "lpc_types.h"
#include "delay.h"

void lcd_init(void);

void lcd_gohome(void);

void lcd_write(char * str_out, int length);

void lcd_append(char chr_out);

void lcd_clear(void);
