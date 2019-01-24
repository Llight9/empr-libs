#include "lcd_menu.h"

void main (){
    char *string_database[5]={'\0'};
    string_database[0]="Florida";
    string_database[1]="Oregon";
    string_database[2]="California";
    string_database[3]="Georgia";
    int i;
    menu_make(3, string_database);
    for (i = 0; i < 10; i ++){
        Delay(400);
        menu_down();
    }
    for (i = 0; i < 10; i ++){
        Delay(400);
        menu_up();
    }
}
