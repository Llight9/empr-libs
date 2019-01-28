/*
library for writing to the lcd
*/

// Serial code
#include "lpc17xx_i2c.h"
#include "lpc17xx_pinsel.h"
#include "lpc_types.h"
#include "delay.h"
#include "usbIO.h"
#include <stdio.h>
//#include "serial.h"

#define LCD_ADDRESS 59

void lcd_init(void);

void lcd_gohome(void);

void lcd_write(char * str_out, int length);

void lcd_append(char chr_out);

void lcd_clear(void);

int chr_buffer;

void lcd_breakline(int length);

Status I2Csend(int address, unsigned char * data, int data_len){
    I2C_M_SETUP_Type I2C_buff;
    I2C_buff.sl_addr7bit = (uint32_t) address;
    I2C_buff.tx_data = data;
    I2C_buff.tx_length = (uint32_t) data_len;
    I2C_buff.rx_data = NULL;
    I2C_buff.rx_length = 0;
    I2C_buff.retransmissions_max = 0;
    //I2C_buff.status = 0;
    return I2C_MasterTransferData(LPC_I2C1, &I2C_buff, I2C_TRANSFER_POLLING);
}


Status LCD_Write_Char(unsigned char character){
  unsigned char data[2];
  data[0] = 0x40;
  data[1] = character;
  return I2Csend(LCD_ADDRESS, data, 2);
}

void lcd_init(){
    PINSEL_CFG_Type PinCfg;
    PinCfg.Funcnum = 3;
    PinCfg.OpenDrain = 0;
    PinCfg.Pinmode = 0;
    PinCfg.Portnum = 0;
    PinCfg.Pinnum = 0;
    PINSEL_ConfigPin(&PinCfg);
    PinCfg.Pinnum = 1;
    PINSEL_ConfigPin(&PinCfg);
    I2C_Init(LPC_I2C1, 100000);
    I2C_Cmd(LPC_I2C1, ENABLE);
    unsigned char data[11] = {0x00,0x34,0x0c,0x06,0x35,0x04,0x10,0x42,0x9f,0x34,0x02};
    I2Csend(LCD_ADDRESS, data, 11);
    chr_buffer = 0;
    Delay(5);
}

char lcd_convert(char chr_in){
    if (chr_in > 64 && chr_in < 91){
        return chr_in + 128;
    } else {
        switch(chr_in){
            case ' ':
                return 160;
            case '>':
                return 190;
            case '\n':
               lcd_breakline(chr_buffer);
               return 160;
            case '<':
                return 188;
            case 0 :
                return 16;
            case 1 :
                return 32;
            default:
                return chr_in;
        }
    }
}

void lcd_gohome(){
    chr_buffer = 0;
    unsigned char data[2] = {0x00, 0x02};
    I2Csend(LCD_ADDRESS, data, 2);
}

void lcd_breakline(int length){
    int i;
    for(i=0; i<40-length;i++){
        LCD_Write_Char(0xA0);
        chr_buffer++;
    }
}

void lcd_write(char * str_out, int length){
    int i;
    //char buff[5];
    //write_usb_serial_blocking("lcd_write \n\r", 12);
    for(i=0; i < length; i++){
        //sprintf(buff, "%c \n\r", *str_out);
        //write_usb_serial_blocking(buff, 4);
        lcd_append(*str_out);
        ++str_out;
    }
}

void lcd_append(char chr_out){
    chr_buffer++;
    if((chr_buffer >= 0 && chr_buffer < 16) || (chr_buffer > 39 && chr_buffer < 57)){
        char chr_form;
        chr_form = lcd_convert(chr_out);
        unsigned char data[2];
        data[0] = 0x40;
        data[1] = chr_form;
        I2Csend(LCD_ADDRESS, data, 2);
    }else if(chr_buffer < 40){
        char chr_form;
        chr_form = lcd_convert(chr_out);
        unsigned char data[2];
        data[0] = 0x40;
        data[1] = chr_form;
        I2Csend(LCD_ADDRESS, data, 2);
        //write_usb_serial_blocking("line break\r\n", 12);
        lcd_breakline(16);
    }else{
        lcd_gohome();
        char chr_form;
        chr_form = lcd_convert(chr_out);
        unsigned char data[2];
        data[0] = 0x40;
        data[1] = chr_form;
        I2Csend(LCD_ADDRESS, data, 2);
    }
}

void lcd_clear(){
    lcd_gohome();
    int x;
    for(x = 0; x <70; x++){
        lcd_append(0xA0);
    }
    lcd_gohome();
}
