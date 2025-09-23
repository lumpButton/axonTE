#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#define BUFFER_SIZE 5000
#define LINE_SIZE 1000

#include "../include/file.h"
#include "../include/buffer.h"


Buffer buffer = {
    .lines = {NULL},
    .amount_lines = 0,
    .current_pos = 0,
    .current_line = 0
};

Line* create_line() {
    Line* new_line = malloc(sizeof(Line));
    new_line->line = malloc(LINE_SIZE * sizeof(char));
    new_line->line[0] = '\0';
    new_line->length = 0;
    return new_line;
}

void init_buffer() {
    buffer.lines[0] = create_line();
    buffer.amount_lines = 1;
    buffer.current_line = 0;
    buffer.current_pos = 0;
}

void free_line(Line* line) {
    if (line) {
        free(line->line);
        free(line);
    }
}

void init(char* filename) {
    init_buffer();
    load_buffer(filename);
    buffer.current_line = 0;
    buffer.current_pos = 0;
}

void add_char(char ch) {
    if (ch == '\n') {
        for (int i = buffer.amount_lines + 1; i > buffer.current_line; i--) {
        buffer.lines[i] = buffer.lines[i - 1];
        }
        buffer.lines[buffer.current_line + 1] = create_line();
        char* move_data = &buffer.lines[buffer.current_line]->line[buffer.current_pos];
        strcpy(buffer.lines[buffer.current_line + 1]->line, move_data);
        buffer.lines[buffer.current_line + 1]->length = strlen(move_data);
        buffer.lines[buffer.current_line]->line[buffer.current_pos] = '\0';
        buffer.lines[buffer.current_line]->length = buffer.current_pos;
        buffer.amount_lines++;
        buffer.current_line++;
        buffer.current_pos = 0;
    }
    else {
        for (int i = buffer.lines[buffer.current_line]->length + 1; i > buffer.current_pos; i--) {
            buffer.lines[buffer.current_line]->line[i] = buffer.lines[buffer.current_line]->line[i - 1];
        }
        buffer.lines[buffer.current_line]->line[buffer.current_pos] = ch;
        buffer.current_pos++;
        buffer.lines[buffer.current_line]->length++;
    }
}

void rem_char() {
    if (buffer.current_pos == 0 && buffer.current_line != 0) {
        strcat(buffer.lines[buffer.current_line - 1]->line, buffer.lines[buffer.current_line]->line);
        buffer.current_pos = buffer.lines[buffer.current_line - 1]->length;
        buffer.lines[buffer.current_line - 1]->length += buffer.lines[buffer.current_line]->length;
        for (int i = buffer.current_line; i < buffer.amount_lines; i++) {
            buffer.lines[i] = buffer.lines[i + 1];
        }
        free_line(buffer.lines[buffer.amount_lines]);
        buffer.current_line--;
        buffer.amount_lines--;
    }
    else if (buffer.current_pos != 0) {
        for (int i = buffer.current_pos - 1; i < buffer.lines[buffer.current_line]->length; i++) {
            buffer.lines[buffer.current_line]->line[i] = buffer.lines[buffer.current_line]->line[i + 1];
        }
        buffer.lines[buffer.current_line]->line[buffer.current_pos] = '\0';
        buffer.current_pos--;
        buffer.lines[buffer.current_line]->length--;
    }
}

void mov_pos_left() {
    if (buffer.current_pos>0) {
        buffer.current_pos--;
    }
    else if (buffer.current_line > 0) {
        buffer.current_line--;
        buffer.current_pos = buffer.lines[buffer.current_line]->length;
    }
}

void mov_pos_right() {
    if (buffer.current_pos<buffer.lines[buffer.current_line]->length) {
        buffer.current_pos++;
    }
    else if (buffer.current_line < buffer.amount_lines - 1) {
        buffer.current_line++;
        buffer.current_pos = 0;
    }
}

void mov_pos_up() {
    if (buffer.current_line != 0) {
        buffer.current_line--;
        if (buffer.current_pos > buffer.lines[buffer.current_line]->length) {
            buffer.current_pos = buffer.lines[buffer.current_line]->length;
        }
    }
}

void mov_pos_down() {
    if (buffer.current_line < buffer.amount_lines - 1) {
        buffer.current_line++;
        if (buffer.current_pos > buffer.lines[buffer.current_line]->length) {
            buffer.current_pos = buffer.lines[buffer.current_line]->length;
        }
    }
}

Line** get_buffer() {
    return buffer.lines;
}

int get_buffer_pos() {
    return buffer.current_pos;
}

int get_buffer_line() {
    return buffer.current_line;
}

int get_buffer_size() {
    return buffer.amount_lines;
}
