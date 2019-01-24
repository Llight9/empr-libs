#include "lcdIO.h"
#include "usbIO.h"

void main(){
    serial_init();
    setup_leds();
    lcd_init();
    write_usb_serial_blocking("-------------------- \n\r", 23);
    lcd_clear();
    lcd_write("hi ", 3);
    Delay(20);
    lcd_write("abcdefghijklmnopqrstuvwxyz", 26);
    Delay(20);
    lcd_clear();
    lcd_write("line one \nline two", 18);
    Delay(20);
    lcd_gohome();
    lcd_write("overwrite", 9);
    lcd_clear();
    Delay(10);
    lcd_write("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", 34);
    write_usb_serial_blocking("-------------------- \n\r", 23);
}
