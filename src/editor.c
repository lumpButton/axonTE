#include <ncurses.h>
#include "../include/buffer.h"


//void test() {
//    clear();
//    printw("%s", "axonTE started. Press ^q to quit.\nClear_screen\n");
//    int buffer_size = get_buffer_size();
//    const char* buffer = get_buffer();
//    for (int i=0; i<buffer_size; i++) {
//        printw("%c %d\n", buffer[i], buffer[i]);
//    }
//    refresh();
//}

void print_buffer(bool test) {
    int count = 1;
    clear();
    printw("%s", "axonTE started. Press ^q to quit.\n");
    
    int buffer_amount_lines = get_buffer_size();
    int buffer_pos = get_buffer_pos();
    int buffer_line = get_buffer_line();
    Line** lines = get_buffer();
    
    for (int i = 0; i < buffer_amount_lines; i++) {
        if (test) {
            printw("\n%d %d| ", count, lines[i]->length);
        } else {
            printw("\n%d| ", count);

        }
        count++;
        
        if (i == buffer_line) {
            for (int j = 0; j < lines[i]->length; j++) {
                if (j == buffer_pos) {
                    attron(A_REVERSE);
                }
                printw("%c", lines[i]->line[j]);
                if (j == buffer_pos) {
                    attroff(A_REVERSE);
                }
            }
            if (buffer_pos == lines[i]->length) {
                attron(A_REVERSE);
                printw(" ");
                attroff(A_REVERSE);
            }
        } else {
            printw("%s", lines[i]->line);
        }
    }
    
    printw("\n\n\n\nlines: %d, line: %d, pos: %d", buffer_amount_lines, buffer_line, buffer_pos);
    if (test) {
        printw("\n TEST MODE %d %c", lines[buffer_line]->line[buffer_pos], lines[buffer_line]->line[buffer_pos]);
    }
}