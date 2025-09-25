#include <ncurses.h>
#include <stdatomic.h>
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

void print_buffer(bool test, char* filename, bool dirty) {
    int digits = 0;
    int max_y;
    max_y = getmaxy(stdscr);
    int available = max_y - 4;
    if (test) {available--;}
    int current_y = get_current_y();
    clear();
    attron(A_REVERSE);
    printw("axonTE started in %s. Press ^q to quit ^s to save ^t to test mode.\n", filename);
    attroff(A_REVERSE);
    int buffer_amount_lines = get_buffer_size();
    int buffer_amount_lines_copy = get_buffer_size();
    while (buffer_amount_lines_copy != 0) {
        buffer_amount_lines_copy /= 10;
        digits++;
    }
    if (buffer_amount_lines == 0) digits = 1;
    int buffer_pos = get_buffer_pos();
    int buffer_line = get_buffer_line();
    int current_y_offset = get_current_y_offset();
    Line** lines = get_buffer();

    int cmp_print;
    if (buffer_amount_lines-current_y_offset < available) {cmp_print = buffer_amount_lines-current_y_offset;} else {cmp_print = available;}
    for (int i = 0; i < cmp_print; i++) {
        printw("\n");
        int line_num = i + current_y_offset + 1;
        
        // Calculate current line number digits
        int current_digits = 0;
        int temp_num = line_num;
        while (temp_num != 0) {
            temp_num /= 10;
            current_digits++;
        }
        
        for (int j = 0; j < digits - current_digits; j++) {
            printw("0");
        }
        
        if (i + current_y_offset >= buffer_amount_lines) {
            printw("%d| ", line_num);
            continue;
        }
        
        if (test) {
            printw("%d %d| ", line_num, lines[i + current_y_offset]->length);
        } else {
            printw("%d| ", line_num);

        }
        
        if (i + current_y_offset == buffer_line) {
            for (int j = 0; j < lines[i + current_y_offset]->length; j++) {
                if (j == buffer_pos) {
                    attron(A_REVERSE);
                }
                printw("%c", lines[i + current_y_offset]->line[j]);
                if (j == buffer_pos) {
                    attroff(A_REVERSE);
                }
            }
            if (buffer_pos == lines[i + current_y_offset]->length) {
                attron(A_REVERSE);
                printw(" ");
                attroff(A_REVERSE);
            }
        } else {
            printw("%s", lines[i + current_y_offset]->line);
        }
    }
    attron(A_REVERSE);
    mvprintw(max_y-1, 0, "lines: %d, line: %d, pos: %d, current_y_offset: %d, current_y: %d, available%d%s", buffer_amount_lines, buffer_line, buffer_pos, current_y_offset, current_y, available, dirty ? ", dirty" : "");
    if (test) {
        mvprintw(max_y - 2, 0, "TEST MODE %d %c", lines[buffer_line]->line[buffer_pos], lines[buffer_line]->line[buffer_pos]);
    }
    attroff(A_REVERSE);
}