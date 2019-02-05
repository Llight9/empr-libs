#include "empr-libs/screenIO.h"

void main(){
    screen_init();
    screen_breakline();
    screen_write("hi hoow are you");
    screen_write("yay \r\n");
    screen_breakline();
}
