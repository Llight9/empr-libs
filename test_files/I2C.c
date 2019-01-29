#include <lpc17xx_i2c.h>
#include <stdlib.h>
#include <lpc17xx_gpio.h>
#include <lpc17xx_pinsel.h>
#include <stdio.h>
#include "usbIO.h"
#define Address_LCD 0x3b
long leds[4];

/*
typedef struct{ 
  uint32_t sl_addr7bit;
  uint8_t* tx_data;
  uint32_t tx_length;
  uint32_t tx_count;
  uint8_t* rx_data;
  uint32_t rx_length;
  uint32_t rx_count;
  uint32_t retransmissions_max;
  uint32_t retransmissions_count;
  uint32_t status;
  void (*callback)(void);
} I2C_M_SETUP_Type;
*/

void delay(int yes)
{
  int i,j;
  for(i=0; i<1000; i++)
    for(j=0; j <yes; j++)
      ;
}

void setup_leds()
{
  int i = 0;
  for(i = 0; i< 4; i++)
    GPIO_SetDir(1, leds[i], 1);
}

void ledcounter()
{
  int i = 0;
  for(i = 1; i<17; i++)
  {
    int j = 0;
    int y = 0;
    for(j=1, y=0; j<9; j<<=1, y++)
      if((i & j) && i != 16)
	GPIO_SetValue(1,leds[y]);
      else
	GPIO_ClearValue(1, leds[y]);
    delay(10000);
  }
}
//I2C_M_SETUP_Type I2C_buff;

void I2Cinit()
{
  PINSEL_CFG_Type PinCfg;
  PinCfg.OpenDrain = 0;
  PinCfg.Pinmode = 0;
  PinCfg.Funcnum = 3;
  PinCfg.Pinnum = 0;
  PinCfg.Portnum = 0;
  PINSEL_ConfigPin(&PinCfg);
  PinCfg.Pinnum = 1;
  PINSEL_ConfigPin(&PinCfg);
  I2C_Init(LPC_I2C1, 100000);
  I2C_Cmd(LPC_I2C1, ENABLE);
}

Status I2Csend(int address, unsigned char * data, int data_len)
{
  I2C_M_SETUP_Type I2C_buff;
  I2C_buff.sl_addr7bit = (uint32_t) address;
  I2C_buff.tx_data = &data;
  I2C_buff.tx_length = (uint32_t) data_len;
  I2C_buff.rx_data = NULL;
  I2C_buff.rx_length = 0;
  I2C_buff.retransmissions_max = 0;
  //I2C_buff.status = 0;
  return I2C_MasterTransferData(LPC_I2C1, &I2C_buff, I2C_TRANSFER_POLLING);
}

/* should be the receive*/
Status I2Creceive(int address, unsigned char * data, int data_len)
{
  I2C_M_SETUP_Type I2C_buff;
  I2C_buff.sl_addr7bit = (uint32_t) address;
  I2C_buff.tx_data = data;
  I2C_buff.tx_length = data_len;
  I2C_buff.rx_data = NULL;
  I2C_buff.rx_length = 0;
  I2C_buff.retransmissions_max = 0;
  I2C_buff.status = 0;
  return I2C_MasterTransferData(LPC_I2C1, &I2C_buff, I2C_TRANSFER_POLLING);
}

Status LCD_Init()
{
  unsigned char data[11] = {0x00,0x34,0x0c,0x06,0x35,0x04,0x10,0x42,0x9f,0x34,0x02};
  Status result = I2Csend(0x3b, data, 11);
  delay(100000);
  return result;
}

Status LCDwrite(char characters, int length){
  unsigned char data[length * 2];
  data[0] = 0x40;
  data[1] = characters;
  return I2Csend(0x3b, data, length * 2);
}

int main()
{
  int count = 0;
  leds[0] = 0x40000;
  leds[1] = 0x100000;
  leds[2] = 0x200000;
  leds[3] = 0x800000;
  setup_leds();
  I2Cinit();
  serial_init();
  int i;
  for(i = 0; i<128; i++)
  {
    unsigned char * test = '\0';
    Status return_status = I2Csend(i, test, 1);
    if(return_status == SUCCESS)
    {
      char buffer[23];
      sprintf(buffer, "Something is on %x \r\n", i);
      write_usb_serial_blocking(buffer, sizeof(buffer));
      count++;
      //GPIO_SetValue(1, leds[1]);
    }
  }
  
  char buffer[36];
  sprintf(buffer, "%i devices connected to i2c bus\r\n", count);
  write_usb_serial_blocking(buffer, sizeof(buffer));
  //LCD_Init();
  //LCDwrite(0xCF, 1);
  //clearLCD();
  /*break;
      default:*/
	
	/*break;
	  }*/
  /*int i = 0;
   for(i = 0x00; i=<0xFF; i++)
  {
    I2C_MasterTransferData(LPC_I2C1, &yes, I2C_TRANSFER_POLLING);
    } */ 
  //ledcounter();
  return 0;
}
