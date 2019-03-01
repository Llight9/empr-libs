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

// node.data = (char**) malloc(size * sizeof(char*));
//
// free(node.data);

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
