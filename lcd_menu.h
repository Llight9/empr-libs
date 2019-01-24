#include "usbIO.h"
#include "ledIO.h"
#include "lcdIO.h"
#include "string.h"

/*
library for writing a menu
on the lcd screen
*/

//debug
#define DBG_menu 1


//defines
void menu_make(int len, char ** items);
// where len is the length of the list of items
// items is a list of strings
int menu_select(void);
// returns the item currently selected
void menu_down(void);
// increments the menu down
void menu_up(void);
// decrements the menu up
