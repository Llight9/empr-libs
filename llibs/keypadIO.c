#include "lpc17xx_i2c.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_exti.h"
//#include "lpc17xx_libcfg.h"
#include "lpc_types.h"
#include "usbIO.h"
#include "empr-libs/delay.h"
#include "empr-libs/ledIO.h"
#include "empr-libs/test_files/old.h"

//in development

int LCDaddress = 59;
int KeypadResponse[16];
uint8_t Screenaddress1[2] = {0,128};
uint8_t Screenaddress2[2] = {0,192};
char Inputbuffer[16];
char Lastbuffer[16];
int Inputbufferpos = 0;

void keypad_init(void);

//char keypad_get(void);

char keypad_convert(int keypadbyte);

char keypad_handler(void);

int keypad_send(int size, int address);


void I2Cinit(void) {

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

//	write_usb_serial_blocking("i2c config\n\r", 13);

}

Status I2Csendcommand(uint8_t *bytestream,int size,int address) {
	//Send command byte
	I2C_M_SETUP_Type tempsetup;

	tempsetup.sl_addr7bit = address;
	tempsetup.retransmissions_max = 3;
	tempsetup.tx_data = bytestream;
	tempsetup.tx_length = size;
	tempsetup.rx_data = NULL;
	tempsetup.rx_length = 0;

	return I2C_MasterTransferData(LPC_I2C1, &tempsetup, I2C_TRANSFER_POLLING);


}

int I2CrecCommand(int size,int address) {
	//Send command byte
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

	if (check == SUCCESS) {
//		LEDturnon(14);
		return bytestream[0];
	}
	else
	{

	}
	return 1254;
}

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
            Inputbuffer[Inputbufferpos] = keypad_convert(result);
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
