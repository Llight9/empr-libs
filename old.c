#include "lpc17xx_i2c.h"
//#include "lpc17xx_libcfg.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc_types.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_exti.h"

#include "stdio.h"
#include "project2.h"

//---------------------
// Prototypes
// Declarations
//---------------------
int LEDturnon (int input);
int LEDallOff(void);
Status I2Csendcommand(uint8_t *bytestream,int size,int address);
int LCDLetterAddress(char letter);
void delay (void);

int I2CrecCommand(int size,int address);
int keypadToChar(int keypadbyte);
void LCDupdate(void);
void LCDprint(uint8_t address, char string[32], int length);
//---------------------
// Globals
//---------------------

//Hard coded address of LCD
int LCDaddress = 59;
int KeypadResponse[16];
uint8_t Screenaddress1[2] = {0,128};
uint8_t Screenaddress2[2] = {0,192};

char Inputbuffer[16];
char Lastbuffer[16];
int Inputbufferpos = 0;
//---------------------
// Interrupt
//---------------------

void EINT3_IRQHandler(void)
{
	//NVIC_DisableIRQ(EINT3_IRQn);
	int result = 0;
	//Read the character that was pressed.
	uint8_t temp[1];
	if(GPIO_GetIntStatus(0, 23, 1))
	{
		LEDturnon(8);
		//Clear the ISR flag
		//GPIO_ClearInt(0,(1<<23));



		//Read columns
		result = I2CrecCommand(1,33);

		//Read rows
		temp[0] = 0xf0;
		I2Csendcommand(temp,1,33);
		result += I2CrecCommand(1,33);

		if (result < 0xf0){
		KeypadResponse[Inputbufferpos]=result;
		Inputbuffer[Inputbufferpos] = keypadToChar(result);
		Inputbufferpos++;
		}
		delay();

	}

	temp[0] = 0x0f;
	I2Csendcommand(temp,1,33);
	//Clear the ISR flag
	GPIO_ClearInt(0,(1<<23));
	//NVIC_EnableIRQ(EINT3_IRQn);
	LCDupdate();
}

//---------------------
// I2C
//---------------------

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

// I2C - LCD
//---------------------

void LCDclearscreen(){

	I2Csendcommand(Screenaddress1,2,LCDaddress);
	int k = 0;
	uint8_t temp[64];
	temp[0] = 64;

	for(k=1; k<64; k++)
	{
	temp[k] = 160;
	}

	I2Csendcommand(temp,63,LCDaddress);
}

void LCDupdate()
{
	int i=0;
	int notchange=1;
	for(i=0;i<16;i++)
	{
		if(Lastbuffer[i] != Inputbuffer[i])
		{
			Lastbuffer[i] = Inputbuffer[i];
			notchange=0;
		}
	}
	if(notchange == 0)
	{

		LCDclearscreen();
		LCDprint(0, Lastbuffer, 16);

	}
}

void LCDprint(uint8_t address, char string[32], int length){
	int k;

	uint8_t offsetaddress[2];
	offsetaddress[0] = Screenaddress1[0];
	offsetaddress[1] = Screenaddress1[1];

	offsetaddress[1]+=address;
	I2Csendcommand(offsetaddress,2,LCDaddress);
	uint8_t temp[64];
	temp [0]=64;
	for(k=0; k<length; k++)
	{
		temp[k+1] = LCDLetterAddress(string[k]);
	}
	length++;
	I2Csendcommand(temp,length,LCDaddress);
}

void LCDinit(int address) {
	//Required init byte
	uint8_t bytebuffer[11]  = {0x00,0x34,0x0c,0x06,0x35,0x04,0x10,0x42,0x9f,0x34,0x02};
	//Send command byte

	if(I2Csendcommand(&bytebuffer,11,address) == SUCCESS)
	{
		delay();
	}
	else
	{

	}

}

//---------------------
// SERIAL
//---------------------
// Read options
int read_usb_serial_none_blocking(char *buf,int length)
{
	return(UART_Receive((LPC_UART_TypeDef *)LPC_UART0, (uint8_t *)buf, length, NONE_BLOCKING));
}

// Write options
int write_usb_serial_blocking(char *buf,int length)
{
	return(UART_Send((LPC_UART_TypeDef *)LPC_UART0,(uint8_t *)buf,length, BLOCKING));
}

void serial_init(void)
{
	UART_CFG_Type UARTConfigStruct;			// UART Configuration structure variable
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;	// UART FIFO configuration Struct variable
	PINSEL_CFG_Type PinCfg;				// Pin configuration for UART
	/*
	 * Initialize UART pin connect
	 */
	PinCfg.Funcnum = 1;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	// USB serial first
	PinCfg.Portnum = 0;
	PinCfg.Pinnum = 2;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 3;
	PINSEL_ConfigPin(&PinCfg);

	/* Initialize UART Configuration parameter structure to default state:
	 * - Baudrate = 9600bps
	 * - 8 data bit
	 * - 1 Stop bit
	 * - None parity
	 */
	UART_ConfigStructInit(&UARTConfigStruct);
	/* Initialize FIFOConfigStruct to default state:
	 * - FIFO_DMAMode = DISABLE
	 * - FIFO_Level = UART_FIFO_TRGLEV0
	 * - FIFO_ResetRxBuf = ENABLE
	 * - FIFO_ResetTxBuf = ENABLE
	 * - FIFO_State = ENABLE
	 */
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);
	// Built the basic structures, lets start the devices/
	// USB serial
	UART_Init((LPC_UART_TypeDef *)LPC_UART0, &UARTConfigStruct);		// Initialize UART0 peripheral with given to corresponding parameter
	UART_FIFOConfig((LPC_UART_TypeDef *)LPC_UART0, &UARTFIFOConfigStruct);	// Initialize FIFO for UART0 peripheral
	UART_TxCmd((LPC_UART_TypeDef *)LPC_UART0, ENABLE);			// Enable UART Transmit

}

//---------------------
// MISC
//---------------------

//turns LED on
int LEDturnon (int input)
{
	LEDallOff();
	int totalbit = 0;
	if(input&1)
		{
			totalbit+=0x40000;
		}
	if(input&2)
		{
			totalbit+=0x100000;
		}
	if(input&4)
		{
			totalbit+=0x20000A;
		}
	if(input&8)
		{
			totalbit+=0x800000;
		}
	GPIO_SetDir (1, totalbit, 1);
	GPIO_SetValue (1, totalbit);
	return 0;
}
//takes char input and returns LCD binary address
int LCDLetterAddress(char letter)
{
	int output=160;
	if (letter>=65 && letter<=90)
	{
		output=letter+128;
	}
	else if (letter>=97 && letter<=122)
	{
		output=letter;
	}
	else if (letter>=48 && letter<=57)
	{
		output =letter+128;
	}
	else if (letter == 35)
	{
		output = 163;
	}
	else if (letter == 42)
	{
		output = 170;
	}
	return output;
}

//takes keypad byte and returns char
int keypadToChar(int keypadbyte)
{
//bitwise inverter
	int localkeypadbyte= ~keypadbyte;
//initialize the chart
	char keypadChart[4][4] = {"D#0*", "C987", "B654", "A321"};
	int i;
	int x;
	int y;
//work out the character pressed
	for(i=0; i<4; i++)
	{
		if (localkeypadbyte & (1 << i))
		{
			x=i;
		}
	}
	for(i=4; i<8; i++)
	{
		if(localkeypadbyte & (1 << i))
		{
			y=i-4;
		}
	}

	return keypadChart[x][y];
}

//clears LED
int LEDallOff(void)
{
	GPIO_ClearValue(1, 0xffffffff);
	return 0;
}

void delay (void)
{
	unsigned int i;

	for (i = 0;i < 0x100000;i++) {
	}
}
void delay10 (void)
{
	int i;
	for (i=0;i<10;i++)
	delay();
}


//---------------------
// Main
//---------------------
int main (void)
{
	//----
	// TASK 1
	//----
	LEDturnon(1);
	//loop var
	uint8_t i;
	//Array to store addresses
	int connected[6];
	int connectedlength=0;

	for (i=0; i<6; i++)
	{
		connected[i]=0;
	}

	I2Cinit();

	uint8_t testdata = 0;
	//Poll all addresses on the I2C
	for (i=0; i<128; i++)
	{
		if(I2Csendcommand(&testdata,1,i) == SUCCESS)
		{
			if (connectedlength < 6)
			{
				connectedlength++;
				connected[connectedlength]=i;
			}
			else
			{

				break;
			}
		}

	}

	//Start serial and print

	serial_init();
	char debugbuffer[50];
	int buffersizeactual;

	for(i=0;i<connectedlength;i++){
		buffersizeactual = sprintf(debugbuffer,"Address: %d\n\r",connected[i]);
		write_usb_serial_blocking(debugbuffer,buffersizeactual);
	}

	delay10();
	//----
	// TASK 2
	LEDturnon(2);
	//Hard coded address of LCD
	int LCDaddress = 59;

	LCDinit(LCDaddress);
	delay();
	//----
	// TASK 3
	LEDturnon(3);
	//----

	//Blank the screen
	LCDclearscreen();
	LEDturnon (15);
	//Write hello world
	LCDprint(0,"Hello World", 11);
	delay10();
	LCDclearscreen();
	LCDprint(0,"Hello",5);
	LCDprint(64,"World",5);
	LEDturnon (8);

	//----
	// TASK 4 - Keypad
	LEDturnon(4);
	//----
	LEDturnon(15);
	uint8_t temp[1];
	temp[0] = 0x0f;
	I2Csendcommand(temp,1,33);
	GPIO_IntCmd(0,(1<<23),1);
	NVIC_EnableIRQ(EINT3_IRQn);

//	LCDclearscreen();
	//LEDturnon(1);
	while(Inputbufferpos < 16)
	{

		LEDturnon(1);

	}
	NVIC_DisableIRQ(EINT3_IRQn);
	serial_init();

	for(i=0;i<Inputbufferpos;i++){
		buffersizeactual = sprintf(debugbuffer,"CHARS: %c, Keypad Bytes: %x \n\r",Inputbuffer[i], KeypadResponse[i]);
		write_usb_serial_blocking(debugbuffer,buffersizeactual);
	}

}
