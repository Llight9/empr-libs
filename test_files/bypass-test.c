#include "empr-libs/screenIO.h"
#include "empr-libs/itsIO.h"
#include "empr-libs/spiIO.h"
#include "empr-libs/ledIO.h"


void main(){
    screen_init();
    screen_breakline();

    setup_leds();
    screen_write("leds init");

    spi_init();
    screen_write("spi init");

    spi_bypass();
    screen_write("bypass init");

    while(1); write_leds(1);
}
