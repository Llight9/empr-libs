#include "lcd_menu.h"

void main (){
    serial_init();
    setup_leds();
    write_usb_serial_blocking("-------------------- \n\r", 23);
    write_leds(1);
    char *string_database[4]={'\0'};
    string_database[0]="Florida";
    string_database[1]="Oregon";
    string_database[2]="California";
    string_database[3]="Georgia";
    int i;
    write_leds(2);
    menu_make(4, string_database);
    write_leds(3);
    menu_print();
    for (i = 0; i < 8; i ++){
        Delay(4);
        menu_down();
        menu_print();
    }
    write_leds(4);
    for (i = 0; i < 6; i ++){
        Delay(4);
        menu_up();
        menu_print();
    }
    write_leds(5);
    i = menu_select();
    write_leds(i);
    write_usb_serial_blocking("-------------------- \n\r", 23);
}
