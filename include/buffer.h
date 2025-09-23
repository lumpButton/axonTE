#define BUFFER_SIZE 5000
#define LINE_SIZE 1000

typedef struct {
    char* line;
    int length;
}Line;

typedef struct {
    Line* lines[BUFFER_SIZE];
    int amount_lines;
    int current_line;
    int current_pos;
} Buffer;
Line* create_line();
void init_buffer();
void free_line(Line* line);
void init(char* filename);
void add_char(char ch);
void rem_char();
Line** get_buffer();
int get_buffer_pos();
int get_buffer_line();
int get_buffer_size();
void mov_pos_left();
void mov_pos_right();
void mov_pos_up();
void mov_pos_down();