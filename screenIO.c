#include "usbIO.h"
#include <string.h>

void screen_init(void);

void screen_write(char *buf);

void screen_read(char *buf);

void screen_breakline(void);


void screen_init(void){
    serial_init();
}

void screen_write(char *buf){
    int len = (int)strlen(buf);
    write_usb_serial_blocking(buf, len);
}

void screen_read(char *buf){
    int len = (int)strlen(buf);
    read_usb_serial_none_blocking(buf, len);
}

void screen_breakline(void);
    write_usb_serial_blocking("**************************************************\r\n", 52);

}
