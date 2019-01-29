#include "lcdIO.h"
#include "usbIO.h"
#include "ledIO.h"

void main(){
    serial_init();
    write_usb_serial_blocking("-------------------- \n\r", 23);
    setup_leds();
    lcd_init();
    write_leds(1);
    lcd_clear();
    write_leds(2);
    lcd_write("hi ", 3);
    Delay(20);
    write_leds(3);
    lcd_write("abcdefghijklmnopqrstuvwxyz", 26);
    Delay(20);
    write_leds(4);
    lcd_clear();
    lcd_write("line one \nline two", 18);
    write_leds(5);
    Delay(20);
    lcd_gohome();
    write_leds(6);
    lcd_write("overwrite", 9);
    lcd_clear();
    write_leds(7);
    Delay(10);
    lcd_write("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", 34);
    write_leds(8);
    write_usb_serial_blocking("-------------------- \n\r", 23);
    write_leds(9);
}
