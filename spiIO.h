#include "empr-libs/screenIO.h"
#include "lpc_types.h"

#define BUFFER_SIZE             0x400
#define I2S_BUFFER_SRC          LPC_AHBRAM1_BASE
#define I2S_BUFFER_DST          (I2S_BUFFER_SRC+0x1000UL)
#define CS_PORT_NUM             0
#define CS_PIN_NUM              11

#define MBEDAUDIO_REG_LMIC  0x00
#define LMIC_VALUE 0x1F //000011111
#define MBEDAUDIO_REG_RMIC  0x200
#define RMIC_VALUE 0x1F //000011111
#define MBEDAUDIO_REG_LOUT  0x400
#define LOUT_VALUE 0xFF //011111111
#define MBEDAUDIO_REG_ROUT  0x600
#define ROUT_VALUE 0xFF //011111111
#define MBEDAUDIO_REG_ANALOGPATH  0x800
#define ANALOGPATH_VALUE 0x15 //000010101 //if anything is wrong its probably this
#define MBEDAUDIO_REG_DIGITALPATH  0xA00
#define DIGITALPATH_VALUE 0x04 //000000100
#define MBEDAUDIO_REG_POWER  0xC00
#define POWER_VALUE 0x07 //000000111
#define MBEDAUDIO_REG_DIGITALINTERFACE  0xE00
#define DIGITALINTERFACE_VALUE 0x2 //000000010
#define MBEDAUDIO_REG_SAMPLERATE  0x1000
#define SAMPLERATE_VALUE 0x0C //000001100
#define MBEDAUDIO_REG_DIGITALACTIVATION  0x1200
#define DIGITALACTIVATION_VALUE 0x1 //0000000001
#define MBEDAUDIO_REG_RESET 0x1E00

void spi_init(void);

void spi_bypass(void);

void spi_init_read(void);

void spi_write(uint16_t buff[], int len);
