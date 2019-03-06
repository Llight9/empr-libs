#include "usbIO.h"
#include "ledIO.h"
#include "lcdIO.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

/*
library for writing a menu
on the lcd screen
*/

//debug
#define DBG_menu true


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
    int print_len;
    print_len = len_item + 3;
    char item_print[print_len];
    switch (DBG_menu){
        case true:
            sprintf(item_print, "%s \r\n", item);
            write_usb_serial_blocking(item_print, print_len);
    }
    lcd_write(item, len_item);
}

void menu_make(int len, char **items){
    switch (DBG_menu){
        case true:
            write_usb_serial_blocking("make menu \r\n", 12);
    }
    lcd_init();
    write_usb_serial_blocking("fin init \r\n", 11);
    menu_top = 0;
    int i = 0;
    menu_len = len - 1;
    for(i = 0; i < len; i++){
        char tmp_str[20] = " ";
        char tmp_str_out[21] = " ";
        strcat(tmp_str, items[i]);
        strcat(tmp_str, "\n");
        strcat(tmp_str_out, items[i]);
        strcat(tmp_str_out, "\r\n");
        write_usb_serial_blocking(tmp_str_out, 21);
        //tmp_menu[i].item = *tmp_str;
        strcpy(tmp_menu[i].item, tmp_str);
        tmp_menu[i].len = strlen(tmp_str);
    }
}

void menu_print(){
    write_usb_serial_blocking("menu print \r\n", 13);
    lcd_clear();
    lcd_gohome();
    menu_item top_line;
    top_line = tmp_menu[menu_top];
    top_line.item[0] = '>';
    menu_push(top_line.item, top_line.len);
    menu_item bot_line;
    int menu_bot;
    switch (menu_top == menu_len){
        case 0:
            menu_bot = menu_top + 1;
            bot_line = tmp_menu[menu_bot];
            break;
        default:
            menu_bot = 0;
            bot_line = tmp_menu[0];
    }
    char top_print[18];
    char len_print[18];
    char bot_print[18];
    write_usb_serial_blocking("print init finished, values are : \r\n", 36);
    sprintf(top_print, "menu_top ---> %d \r\n", menu_top);
    sprintf(len_print, "menu_len ---> %d \r\n", menu_len);
    sprintf(bot_print, "menu_bot ---> %d \r\n", menu_bot);
    write_usb_serial_blocking(top_print, 18);
    write_usb_serial_blocking(len_print, 18);
    write_usb_serial_blocking(bot_print, 18);
    menu_push(bot_line.item, bot_line.len);
}

void menu_down(){
    write_usb_serial_blocking("menu down \r\n", 12);
    switch (menu_top == menu_len){
        case 0:
            menu_top++;
            break;
        default:
            menu_top = 0;
    }
}

void menu_up(){
    switch (menu_top == 0){
        case 0:
            menu_top--;
            break;
        default:
            menu_top = menu_len;
    }
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
