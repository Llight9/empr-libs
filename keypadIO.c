#include "lpc17xx_i2c.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_exti.h"
#include "lpc17xx_libcfg.h"
#include "lpc_types.h"
#include "usbIO.h"
#include "empr-libs/delay.h"
#include "empr-libs/ledIO.h"

void keypad_init(void){
    int LCDaddress = 59;
    int KeypadResponse[16];
    uint8_t Screenaddress1[2] = {0,128};
    uint8_t Screenaddress2[2] = {0,192};
    char Inputbuffer[16];
    char Lastbuffer[16];
    int Inputbufferpos = 0;
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

void keypad_enable(void){
	NVIC_EnableIRQ(EINT3_IRQn);
}

void keypad_disable(void){
	NVIC_DisableIRQ(EINT3_IRQn);
}

//char keypad_get(void);

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

char keypad_handler(void){
	int result = 0;
	uint8_t temp[1];
	if(GPIO_GetIntStatus(0, 23, 1)){
		result = I2CrecCommand(1,33);
		temp[0] = 0xf0;
		I2Csendcommand(temp,1,33);
		result += I2CrecCommand(1,33);
		if (result < 0xf0){
            KeypadResponse[Inputbufferpos]=result;
            Inputbuffer[Inputbufferpos] = kepad_convert(result);
            Inputbufferpos++;
		}
        Delay(1);
	}
	temp[0] = 0x0f;
	I2Csendcommand(temp,1,33);
	GPIO_ClearInt(0,(1<<23));
    return Inputbuffer[Inputbufferpos];
}

int keypad_send(int size, int address){
	uint8_t bytestream[1];
	bytestream[0] = 0x00;
	I2C_M_SETUP_Type tempsetup;
	Status check;
	tempsetup.sl_addr7bit = address;
	tempsetup.retransmissions_max = 3;
	tempsetup.tx_data = NULL;
	tempsetup.tx_length = 0;
	tempsetup.rx_data = &bytestream;
	tempsetup.rx_length = size;
	check = I2C_MasterTransferData(LPC_I2C1, &tempsetup, I2C_TRANSFER_POLLING);
    switch(check){
        case SUCCESS:
            return bytestream[0];
        default:
            return 1254;
    }
}

