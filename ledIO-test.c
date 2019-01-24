#include "ledIO.h"

void main(){
    setup_leds();
    int i;
    for(i=0;i<16;i++){
        Delay(1);
        write_leds(i);
    }
}
