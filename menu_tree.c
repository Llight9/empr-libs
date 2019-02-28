#include "empr-libs/lcd_menu.h"

#define audio_type_in       1
#define audio_type_out      2
#define audio_type_bypass   3

#define main_menu {                             \
                   {                            \
                        {"audio in", 8},        \
                        {"audio out", 9},       \
                        {"both", 4}             \
                    }                           \
                    {                           \
                        {                       \
                            {"fast", 4},        \
                            {"normal", 6},      \
                            {"formats", 7},     \
                            {"quality", 7},     \
                            {"effects", 7}      \
                        }                       \
                        {                       \
                            {"playing", 7}      \
                        }                       \
                        {                       \
                            {"playing", 7}      \
                        }                       \
                        {                       \
                            {"lossey", 6}       \
                            {"lossless", 8}     \
                        }                       \
                        {                       \
                            {"worst", 5}        \
                            {"bad", 3}          \
                            {"normal", 6}       \
                            {"good", 4}         \
                            {"better", 6}       \
                            {"best", 4}         \
                        }                       \
                    }                           \
                    {                           \
                        {                       \
                            {"fast", 4},        \
                            {"normal", 6},      \
                            {"formats", 7},     \
                            {"quality", 7},     \
                            {"effects", 7}      \
                        }                       \
                        {                       \
                            {"playing", 7}      \
                        }                       \
                        {                       \
                            {"playing", 7}      \
                        }                       \
                        {                       \
                            {"lossey", 6}       \
                            {"lossless", 8}     \
                        }                       \
                        {                       \
                            {"worst", 5}        \
                            {"bad", 3}          \
                            {"normal", 6}       \
                            {"good", 4}         \
                            {"better", 6}       \
                            {"best", 4}         \
                        }                       \
                        {                       \
                            {"none", 6}         \
                        }                       \
                    }                           \
                    {                           \
                        {"bypass", 6}           \
                    }                           \
                }

/*
typedef struct data_item {
    int item_len;
    char * item_name;
} data_item;

typedef struct node {
    int child_num;
    int data_len;
    data_item data[data_len];
    node children[child_num];
} node;
*/

typedef struct node {
    node * parent;
    int child_num;
    char * data[child_num];
    int data_item_len[child_num];
    node * children[child_num];
} node;

typedef struct effect_data {
    int speed;
    int pitch_shift;
} effect_data;

typedef struct format_data {
    int loss;
} format_data;

typedef struct quality_data {
    int quality
} quality_data;

typedef struct quality_data {
    int quality
} quality_data;

typedef struct menu_status {
    int audio_type;
    format_data format_type;
    quality_data quality_type;
    effect_data effect_type;
} menu_status;




const node head;
    const node menu_audio_in;
        const node menu_in_fast;
        const node menu_in_normal;
        const node menu_in_formats;
        const node menu_in_quality;
        const node menu_in_effects;
    const node menu_audio_out;
        const node menu_out_fast;
        const node menu_out_normal;
        const node menu_out_formats;
        const node menu_out_quality;
        const node menu_out_effects;
    const node menu_audio_both;
        const node menu_bypass;
        const node menu_in_out;
        const node menu_out_in;



head.parent = NULL;
head.child_num = 3;
head.data_item = {'\0'};
head.data_item[0] = "audio in";
head.data_item[1] = "audio out";
head.data_item[2] = "both";
head.data_item_len = {8, 9, 4};
head.children = {
    & menu_audio_in ,
    & menu_audio_out ,
    & menu_audio_both ,
};

menu_audio_in.parent = &head;
menu_audio_in.child_num = 5;
menu_audio_in.data_item = {'\0'};
menu_audio_in.data_item[0] = "fast"   ;
menu_audio_in.data_item[1] = "normal" ;
menu_audio_in.data_item[2] = "formats";
menu_audio_in.data_item[3] = "quality";
menu_audio_in.data_item[4] = "effects";
menu_audio_in.data_item_len = {4, 6, 7, 7, 7};
menu_audio_in.children = {
    & menu_in_fast ,
    & menu_in_normal ,
    & menu_in_formats ,
    & menu_in_quality ,
    & menu_in_effects ,
};

menu_in_fast.parent = &menu_audio_in;
menu_in_fast.child_num = 0;

menu_in_normal.parent = &menu_audio_in;
menu_in_normal.child_num = 0;

menu_in_formats.parent = &menu_audio_in;
menu_in_formats.child_num = 2;
menu_in_formats.data_item = {'\0'};
menu_in_formats.data_item[0] = "lossy"   ;
menu_in_formats.data_item[1] = "lossless" ;

menu_audio_out.parent = &head;
menu_audio_out.child_num = 5;
menu_audio_out.data_item[0] = "fast"   ;
menu_audio_out.data_item[1] = "normal" ;
menu_audio_out.data_item[2] = "formats";
menu_audio_out.data_item[3] = "quality";
menu_audio_out.data_item[4] = "effects";
menu_audio_out.data_item_len = {4, 6, 7, 7, 7};
menu_audio_out.children = {
    & menu_out_fast ,
    & menu_out_normal ,
    & menu_out_formats ,
    & menu_out_quality ,
    & menu_out_effects ,
};

menu_audio_both.parent = &head;
menu_audio_both.child_num = 3;
menu_audio_both.data_item = {'\0'};
menu_audio_both.data_item[0] = "bypass";
menu_audio_both.data_item[1] = "in out";
menu_audio_both.data_item[2] = "out in";
menu_audio_both.data_item_len = {6, 6, 6};
menu_audio_both.children = {
    & menu_bypass ,
    & menu_in_out ,
    & menu_out_in ,
};


void menu_init(void);
void menu_up(void);
void menu_down(void);
void menu_forward();
void menu_back();
menu_status menu_select(void);
int menu_type(void);
void exit_menu(void);


void menu_init(){

}
