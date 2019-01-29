#include "usbIO.h"

void main(){
    serial_init();
    int i;
	for(i=0;i<100;i++){
		write_usb_serial_blocking("hey\n\r", 5);
	}
}
