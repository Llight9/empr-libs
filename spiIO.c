#include "empr-libs/screenIO.h"
#include "lpc17xx_i2s.h"
#include "lpc17xx_pinsel.h"
#include "debug_frmwrk.h"
#include "lpc17xx_spi.h"
#include "lpc_types.h"

#define BUFFER_SIZE             0x400
#define I2S_BUFFER_SRC          LPC_AHBRAM1_BASE
#define I2S_BUFFER_DST          (I2S_BUFFER_SRC+0x1000UL)
#define CS_PORT_NUM             0
#define CS_PIN_NUM              11

#define MBEDAUDIO_REG_LMIC                  0x00
#define MBEDAUDIO_REG_RMIC                  0x200
#define MBEDAUDIO_REG_LOUT                  0x400
#define MBEDAUDIO_REG_ROUT                  0x600
#define MBEDAUDIO_REG_ANALOGPATH            0x800
#define MBEDAUDIO_REG_DIGITALPATH           0xA00
#define MBEDAUDIO_REG_POWER                 0xC00
#define MBEDAUDIO_REG_DIGITALINTERFACE      0xE00
#define MBEDAUDIO_REG_SAMPLERATE            0x1000
#define MBEDAUDIO_REG_DIGITALACTIVATION     0x1200
#define MBEDAUDIO_REG_RESET                 0x1E00


void CS_Force(int32_t state){
    switch (state) {
        case 1:
            GPIO_SetValue(CS_PORT_NUM, (1<<CS_PIN_NUM));
            break;
        default:
            GPIO_ClearValue(CS_PORT_NUM, (1<<CS_PIN_NUM));
            break;
    }
}

uint32_t sd_polling(void* tx_buf, void* rx_buf, uint32_t length){
	CS_Force(0);
	xferConfig.tx_data = tx_buf;
	xferConfig.rx_data = rx_buf;
	xferConfig.length = length;
	SPI_ReadWrite(LPC_SPI, &xferConfig, SPI_TRANSFER_POLLING);
	CS_Force(1);
	return xferConfig.counter;
}

void spi_init(void){
    PINSEL_CFG_Type PinCfg;
    SPI_DATA_SETUP_Type xferConfig;
	SPI_CFG_Type SPI_cfgstruct;
	PinCfg.Funcnum = 0;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Portnum = 0;
	PinCfg.Pinnum = 11;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Funcnum = 3;
	PinCfg.Pinnum = 18;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 17;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 15;
	PINSEL_ConfigPin(&PinCfg);
	SPI_ConfigStructInit(&SPI_cfgstruct);
	SPI_cfgstruct.Databit = SPI_DATABIT_16;
	SPI_Init(LPC_SPI, &SPI_cfgstruct);
    GPIO_SetDir(CS_PORT_NUM, (1<<CS_PIN_NUM), 1);
    GPIO_SetValue(CS_PORT_NUM, (1<<CS_PIN_NUM));
}

void spi_bypass(void){
	uint16_t transmitbuffer[9]={0x1E00, 0x001F, 0x021F, 0x0C08, 0x0E02, 0x1201, 0x0809, 0x04FF, 0x06FF};
    spi_write(transmitbuffer, 9);
}

void spi_write(uint16_t buff[], int len){
    int i;
    for (i = 0; i < len; ++i){
        sd_polling(&buff[i], NULL, 2);
    }
}

