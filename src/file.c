#include <stdio.h>
#include "../include/buffer.h"
void load_buffer(char* filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        int ch;
    
        while ((ch = fgetc(file)) != EOF) {
            add_char(ch);
        }
        fclose(file);
    }

}

void save_file(char* filename) {
    FILE *file = fopen(filename, "w");
    
    int buffer_amount_lines = get_buffer_size();
    Line** lines = get_buffer();

    for (int i = 0; i < buffer_amount_lines; i++) {
        if (i != 0) {
            fputc('\n', file);
        }
        fputs(lines[i]->line, file);
    }

    
    
    fclose(file);
}