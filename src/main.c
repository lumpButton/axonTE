#define CTRL_Q 17
#define CTRL_T 20
#define CTRL_S 19


#include <ncurses.h>
#include <stdbool.h>
#include "../include/editor.h"
#include "../include/buffer.h"
#include "../include/file.h"

char* filename = "test.txt";

void local_test(char ch) {
    clear();
    printw("pressed %c %d", ch, ch);
}

void init_project() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    init(filename);
    print_buffer(false);
    refresh();
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        filename = argv[1];
    } 
    init_project();
    bool test_mode = false;
    int ch;
    while ((ch = getch()) != CTRL_Q) { 
        // if (test_mode) {
        //     test_mode = false;
        //     print_buffer();
        //     refresh();
        // }
        if (ch == CTRL_T) {
            //test();
            if (test_mode) {
                test_mode = false;
            } else {
                test_mode = true;
            }
            print_buffer(test_mode);


        }
        else if (ch == CTRL_S) {
            save_file(filename);
        }
        else {
            if (ch == KEY_BACKSPACE) {
                rem_char();
            }
            else if (ch == KEY_LEFT) {
                mov_pos_left();
            }
            else if (ch == KEY_RIGHT) {
                mov_pos_right();
            }
            else if (ch == KEY_UP) {
                mov_pos_up();
            }
            else if (ch == KEY_DOWN) {
                mov_pos_down();
            }
            else {
                // local_test(ch);
                add_char(ch);
            }
            print_buffer(test_mode);
            
            refresh();
        }
    }

    endwin();
    return 0;
}
