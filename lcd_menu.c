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

int menu_select(void);

void menu_down(void);

void menu_up(void);

typedef struct menu_item {
    char item[18];
    int len;
} menu_item;

menu_item tmp_menu[20];
int menu_top;
int menu_len;


void menu_push(char * item, int len_item){
    switch (DBG_menu){
        case 1:
            write_usb_serial_blocking(item, len_item);
            lcd_write(item, len_item);
        default:
            lcd_write(item, len_item);
    }
}

void menu_make(int len, char **items){
    switch (DBG_menu){
        case 1:
            lcd_init();
    }
    lcd_init();
    menu_top = 0;
    int i = 0;
    menu_len = len;
    for(i = 0; i < len; i++){
        char tmp_str[] = " ";
        strcat(tmp_str, items[i]);
        strcat(tmp_str, "\n");
        //tmp_menu[i].item = *tmp_str;
        strcpy(tmp_menu[i].item, tmp_str);
        tmp_menu[i].len = strlen(tmp_str);
    }
}

void menu_down(){
    switch (menu_top == menu_len){
        case 0:
            menu_top++;
        default:
            menu_top = 0;
    }
    lcd_gohome();
    menu_item top_line;
    top_line = tmp_menu[menu_top];
    top_line.item[0] = '>';
    menu_push(top_line.item, top_line.len);
    menu_item bot_line;
    switch (menu_top == menu_len){
        case 0:
            bot_line = tmp_menu[menu_top++];
        default:
            bot_line = tmp_menu[0];
    }
    menu_push(bot_line.item, bot_line.len);
}

void menu_up(){
    switch (menu_top == 0){
        case 0:
            menu_top--;
        default:
            menu_top = menu_len;
    }
    lcd_gohome();
    menu_item top_line;
    top_line = tmp_menu[menu_top];
    top_line.item[0] = '>';
    menu_push(top_line.item, top_line.len);
    menu_item bot_line;
    switch (menu_top == menu_len){
        case 0:
            bot_line = tmp_menu[menu_top++];
        default:
            bot_line = tmp_menu[0];
    }
    menu_push(bot_line.item, bot_line.len);
}

int menu_select(){
    return menu_top;
}

/*
void menu_append_line(char * line){
    menu_structure =

void menu_make(int len, char ** items){
    int i = 0;
    int item_len;
    for(i = 0; i < len; i++){
        char item = items[i];
        int len_item = strlen(item);
        item_len += len_item;
        //needs multiple line support
        if(item_len > 17){
            menu_push("\n", 1);
    }
    menu_push(" ", 1);
    menu_push(item, len_item);
    menu_push(" ", 1);
}
*/
