#define audio_type_in         1
#define audio_type_out        2
#define audio_type_bypass     3

#define menu_type_list        1
#define menu_type_selc        2
#define menu_type_opt         3
#define menu_type_multi_opt   4

typedef struct {
    typedef node * parent;
    int child_num;
    int data_num;
    char * data[data_num];
    int data_item_len[data_num];
    int data_type;
    typedef node * children[child_num];
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

void menu_tree_init(void);
void menu_tree_up(void);
void menu_tree_down(void);
void menu_tree_forward();
void menu_tree_back();
menu_status menu_tree_select(void);
int menu_tree_type(void);
void menu_tree_exit(void);
