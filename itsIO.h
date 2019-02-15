#include "lpc17xx_i2s.h"
//#include "lpc17xx_libcfg.h"
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

void its_init(int cfg);

void its_send(uint32_t itsbuff, int len);

uint32_t its_recieve(void);
