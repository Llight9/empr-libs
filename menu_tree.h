#define audio_type_in         1
#define audio_type_out        2
#define audio_type_bypass     3

#define menu_type_list        1
#define menu_type_selc        2
#define menu_type_opt         3
#define menu_type_multi_opt   4

typedef struct {
    node * parent;
    int child_num;
    int data_num;
    char * data[data_num];
    int data_item_len[data_num];
    int data_type;
    node * children[child_num];
} node;

typedef struct {
    int speed;
    int pitch_shift;
} effect_data;

typedef struct {
    int loss;
} format_data;

typedef struct {
    int quality
} quality_data;

typedef struct {
    int quality
} quality_data;

typedef struct {
    int audio_type;
    format_data format_type;
    quality_data quality_type;
    effect_data effect_type;
} menu_status;

void menu_init(void);
void menu_up(void);
void menu_down(void);
void menu_forward();
void menu_back();
menu_status menu_select(void);
int menu_type(void);
void exit_menu(void);
