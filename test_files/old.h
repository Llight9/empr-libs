int read_usb_serial_none_blocking(char *buf,int length);

int write_usb_serial_blocking(char *buf,int length);

void serial_init(void);

void I2Cinit(void);

Status I2Csendcommand(uint8_t *bytestream,int size,int address);

int I2CrecCommand(int size,int address);
