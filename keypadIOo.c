//keypad library

#include "lpc17xx_i2c.h"

void keypad_init(void){
	PINSEL_CFG_Type PinCfg;
	PinCfg.Funcnum = 3;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Portnum = 0;
	PinCfg.Pinnum = 1;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 0;
	PINSEL_ConfigPin(&PinCfg);
	I2C_Init(LPC_I2C1, 100000);
	I2C_Cmd(LPC_I2C1, ENABLE);
}

void keypad_enable(void);

void keypad_disable(void);

char keypad_get(void);

char keypad_convert(int keypadbyte){
	int localkeypadbyte= ~keypadbyte;
	char keypadChart[4][4] = {"D#0*", "C987", "B654", "A321"};
	int i, x, y;
	for(i=0; i<4; i++){
		if (localkeypadbyte & (1 << i)){
			x=i;
		}
	}
	for(i=4; i<8; i++){
		if(localkeypadbyte & (1 << i)){
			y=i-4;
		}
	}
	return keypadChart[x][y];
}

