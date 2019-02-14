#include "empr-libs/screenIO.h"
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

void spi_init(void);

void spi_bypass(void);

void spi_write(uint16_t buff[], int len);
