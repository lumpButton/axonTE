#define CTRL_Q 17
#define CTRL_T 20
#define CTRL_S 19


#include <ncurses.h>
#include <stdbool.h>
#include "../include/editor.h"
#include "../include/buffer.h"
#include "../include/file.h"

char* filename = "test.txt";
bool dirty = false;

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
    print_buffer(false, filename, dirty);
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
            print_buffer(test_mode, filename, dirty);


        }
        else if (ch == CTRL_S) {
            save_file(filename);
            dirty = false;
            print_buffer(test_mode, filename, dirty);
        }
        else {
            switch (ch) {
                // NAVIGATION
                case KEY_LEFT:
                    mov_pos_left();
                    break;
                case KEY_RIGHT:
                    mov_pos_right();
                    break;
                case KEY_UP:
                    mov_pos_up();
                    break;
                case KEY_DOWN:
                    mov_pos_down();
                    break;

                //CHANGES
                case KEY_BACKSPACE:
                    rem_char();
                    dirty = true;
                    break;
                default:
                    add_char(ch);
                    dirty = true;
                    break;
            }
            print_buffer(test_mode, filename, dirty);
            refresh();
        }
    }

    endwin();
    return 0;
}
