#include "lpc17xx_i2s.h"
#include "lpc17xx_pinsel.h"
#include "debug_frmwrk.h"
#include "lpc17xx_spi.h"
#include "lpc17xx_gpdma.h"
#include "empr-libs/screenIO.h"

//#define BUFFER_SIZE             0x400
#define I2S_BUFFER_SRC          LPC_AHBRAM1_BASE
#define I2S_BUFFER_DST          (I2S_BUFFER_SRC+0x1000UL)
#define CS_PORT_NUM             0
#define CS_PIN_NUM              11


PINSEL_CFG_Type PinCfg;

SPI_DATA_SETUP_Type xferConfig;

void its_init(int cfg){
	I2S_CFG_Type I2S_ConfigStruct;
	I2S_MODEConf_Type I2S_ClkConfig;
	PinCfg.Funcnum = 1;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Pinnum = 4;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 5;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 6;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 7;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 8;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 9;
	PINSEL_ConfigPin(&PinCfg);
	I2S_Init(LPC_I2S);
    switch (cfg){
        case 0:
            I2S_ConfigStruct.wordwidth = I2S_WORDWIDTH_16;
            I2S_ConfigStruct.mono = I2S_STEREO;
            I2S_ConfigStruct.stop = I2S_STOP_ENABLE;
            I2S_ConfigStruct.reset = I2S_RESET_ENABLE;
            I2S_ConfigStruct.ws_sel = I2S_MASTER_MODE;
            I2S_ConfigStruct.mute = I2S_MUTE_DISABLE;
            I2S_Config(LPC_I2S,I2S_TX_MODE,&I2S_ConfigStruct);
            I2S_ConfigStruct.ws_sel = I2S_MASTER_MODE;
            I2S_Config(LPC_I2S,I2S_RX_MODE,&I2S_ConfigStruct);
            I2S_ClkConfig.clksel = I2S_CLKSEL_FRDCLK;
            I2S_ClkConfig.fpin = I2S_4PIN_DISABLE;
            I2S_ClkConfig.mcena = I2S_MCLK_DISABLE;
            I2S_ModeConfig(LPC_I2S,&I2S_ClkConfig,I2S_TX_MODE);
            I2S_ModeConfig(LPC_I2S,&I2S_ClkConfig,I2S_RX_MODE);
            I2S_FreqConfig(LPC_I2S, 48000, I2S_TX_MODE);
            I2S_SetBitRate(LPC_I2S, 0, I2S_RX_MODE);
            break;
        case 1:
            I2S_ConfigStruct.wordwidth = I2S_WORDWIDTH_16;
            I2S_ConfigStruct.mono = I2S_MONO;
            I2S_ConfigStruct.stop = I2S_STOP_ENABLE;
            I2S_ConfigStruct.reset = I2S_RESET_ENABLE;
            I2S_ConfigStruct.ws_sel = I2S_MASTER_MODE;
            I2S_ConfigStruct.mute = I2S_MUTE_DISABLE;
            I2S_Config(LPC_I2S,I2S_TX_MODE,&I2S_ConfigStruct);
            I2S_ConfigStruct.ws_sel = I2S_MASTER_MODE;
            I2S_Config(LPC_I2S,I2S_RX_MODE,&I2S_ConfigStruct);
            I2S_ClkConfig.clksel = I2S_CLKSEL_FRDCLK;
            I2S_ClkConfig.fpin = I2S_4PIN_DISABLE;
            I2S_ClkConfig.mcena = I2S_MCLK_DISABLE;
            I2S_ModeConfig(LPC_I2S,&I2S_ClkConfig,I2S_TX_MODE);
            I2S_ModeConfig(LPC_I2S,&I2S_ClkConfig,I2S_RX_MODE);
            I2S_FreqConfig(LPC_I2S, 16000, I2S_TX_MODE);
            I2S_SetBitRate(LPC_I2S, 0, I2S_RX_MODE);
            break;
    }
}

void its_send(uint32_t itsbuff, int len);
