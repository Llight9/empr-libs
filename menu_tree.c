#include "empr-libs/lcd_menu.h"

#define audio_type_in         1
#define audio_type_out        2
#define audio_type_bypass     3

#define menu_type_list        1
#define menu_type_selc        2
#define menu_type_opt         3
#define menu_type_multi_opt   4

typedef struct node{
    struct node * parent;
    int child_num;
    int data_num;
    char * data[10];
    int data_item_len[data_num];
    int data_type;
    struct node * children[10];
} node;

typedef struct {
    int speed;
    int pitch_shift;
} effect_data;

typedef struct {
    int loss;
} format_data;

typedef struct {
    int quality;
} quality_data;

typedef struct {
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
head.data_num = 3;
head.data_item = {'\0'};
head.data_item[0] = "audio in";
head.data_item[1] = "audio out";
head.data_item[2] = "both";
head.data_item_len = {8, 9, 4};
head.data_type = menu_type_list;
head.children = {
    & menu_audio_in ,
    & menu_audio_out ,
    & menu_audio_both ,
};

menu_audio_in.parent = &head;
menu_audio_in.child_num = 5;
menu_audio_in.data_num = 5;
menu_audio_in.data_item = {'\0'};
menu_audio_in.data_item[0] = "fast";
menu_audio_in.data_item[1] = "normal";
menu_audio_in.data_item[2] = "formats";
menu_audio_in.data_item[3] = "quality";
menu_audio_in.data_item[4] = "effects";
menu_audio_in.data_type = menu_type_list;
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
menu_in_fast.data_num = 1;
menu_audio_in.data_item = {'\0'};
menu_audio_in.data_item[0] = "play";
menu_audio_in.data_type = menu_type_selc;
menu_audio_in.data_item_len = {4};

menu_in_normal.parent = &menu_audio_in;
menu_in_normal.child_num = 0;
menu_in_normal.data_num = 1;
menu_in_normal.data_item = {'\0'};
menu_in_normal.data_item[0] = "play";
menu_in_normal.data_type = menu_type_selc;
menu_in_normal.data_item_len = {4};

menu_in_formats.parent = &menu_audio_in;
menu_in_formats.child_num = 0;
menu_in_formats.data_num = 3;
menu_in_formats.data_item = {'\0'};
menu_in_formats.data_item[0] = "lossy";
menu_in_formats.data_item[1] = "lossless";
menu_in_formats.data_item[2] = "normal";
menu_in_formats.data_type = menu_type_opt;
menu_in_formats.data_item_len = {5, 8, 6};

menu_in_quality.parent = &menu_audio_in;
menu_in_quality.child_num = 0;
menu_in_quality.data_num = 6;
menu_in_quality.data_item = {'\0'};
menu_in_quality.data_item[0] = "worst";
menu_in_quality.data_item[1] = "bad";
menu_in_quality.data_item[2] = "normal";
menu_in_quality.data_item[3] = "good";
menu_in_quality.data_item[4] = "better";
menu_in_quality.data_item[5] = "best";
menu_in_quality.data_type = menu_type_opt;
menu_in_quality.data_item_len = {5, 3, 6, 4, 6, 4};

menu_in_formats.parent = &menu_audio_in;
menu_in_formats.child_num = 0;
menu_in_formats.data_num = 3;
menu_in_formats.data_item = {'\0'};
menu_in_formats.data_item[0] = "a";
menu_in_formats.data_item[1] = "b";
menu_in_formats.data_item[2] = "c";
menu_in_formats.data_type = menu_type_multi_opt;
menu_in_formats.data_item_len = {1, 1, 1};

menu_audio_out.parent = &head;
menu_audio_out.child_num = 5;
menu_audio_out.data_item[0] = "fast"   ;
menu_audio_out.data_item[1] = "normal" ;
menu_audio_out.data_item[2] = "formats";
menu_audio_out.data_item[3] = "quality";
menu_audio_out.data_item[4] = "effects";
menu_audio_out.data_item_len = {4, 6, 7, 7, 7};
menu_audio_out.data_type = menu_type_list;
menu_audio_out.children = {
    & menu_out_fast ,
    & menu_out_normal ,
    & menu_out_formats ,
    & menu_out_quality ,
    & menu_out_effects ,
};

menu_out_fast.parent = &menu_audio_out;
menu_out_fast.child_num = 0;
menu_out_fast.data_num = 1;
menu_audio_out.data_item = {'\0'};
menu_audio_out.data_item[0] = "recd";
menu_audio_out.data_type = menu_type_selc;
menu_audio_out.data_item_len = {4};

menu_out_normal.parent = &menu_audio_out;
menu_out_normal.child_num = 0;
menu_out_normal.data_num = 1;
menu_out_normal.data_item = {'\0'};
menu_out_normal.data_item[0] = "recd";
menu_out_normal.data_type = menu_type_selc;
menu_out_normal.data_item_len = {4};

menu_out_formats.parent = &menu_audio_out;
menu_out_formats.child_num = 0;
menu_out_formats.data_num = 3;
menu_out_formats.data_item = {'\0'};
menu_out_formats.data_item[0] = "lossy";
menu_out_formats.data_item[1] = "lossless";
menu_out_formats.data_item[2] = "normal";
menu_out_formats.data_type = menu_type_opt;
menu_out_formats.data_item_len = {5, 8, 6};

menu_out_quality.parent = &menu_audio_out;
menu_out_quality.child_num = 0;
menu_out_quality.data_num = 6;
menu_out_quality.data_item = {'\0'};
menu_out_quality.data_item[0] = "worst";
menu_out_quality.data_item[1] = "bad";
menu_out_quality.data_item[2] = "normal";
menu_out_quality.data_item[3] = "good";
menu_out_quality.data_item[4] = "better";
menu_out_quality.data_item[5] = "best";
menu_out_quality.data_type = menu_type_opt;
menu_out_quality.data_item_len = {5, 3, 6, 4, 6, 4};

menu_out_formats.parent = &menu_audio_out;
menu_out_formats.child_num = 0;
menu_out_formats.data_num = 3;
menu_out_formats.data_item = {'\0'};
menu_out_formats.data_item[0] = "a";
menu_out_formats.data_item[1] = "b";
menu_out_formats.data_item[2] = "c";
menu_out_formats.data_type = menu_type_multi_opt;
menu_out_formats.data_item_len = {1, 1, 1};

menu_audio_both.parent = &head;
menu_audio_both.child_num = 0;
menu_audio_both.data_num = 3;
menu_audio_both.data_item = {'\0'};
menu_audio_both.data_item[0] = "bypass";
menu_audio_both.data_item[1] = "in out";
menu_audio_both.data_item[2] = "out in";
menu_audio_both.data_item_len = {6, 6, 6};
menu_audio_both.dtat_type = menu_type_selc;
menu_audio_both.children = {
    & menu_bypass ,
    & menu_in_out ,
    & menu_out_in ,
};


void menu_tree_init(void);
void menu_tree_up(void);
void menu_tree_down(void);
void menu_tree_forward();
void menu_tree_back();
menu_status menu_tree_select(void);
int menu_tree_type(void);
void menu_tree_exit(void);


void menu_tree_init(){
    menu_make(head.data_num, head.data_item);
}
