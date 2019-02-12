//in development

void keypad_init(void);

void keypad_enable(void);

void keypad_disable(void);

//char keypad_get(void);

char keypad_convert(int keypadbyte);

char keypad_handler(void);

int keypad_send(int size, int address);


