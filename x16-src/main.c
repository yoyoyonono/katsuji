#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <cbm.h>
#include <cx16.h>

#define BUFFER_SIZE 2320

enum MODES {NORMAL, INSERT};
enum MODES current_mode;

int video_width;
int video_height;

char text_buffer[BUFFER_SIZE];
char last_key_in;

int cursor_x;
int cursor_y;

int last_cursor_x;
int last_cursor_y;

void print_mode() {
    gotoxy(0, video_height - 1);
    cclear(video_height - 1);
    switch (current_mode) {
        case NORMAL:
            gotox(video_width - 6);
            cprintf("NORMAL");
            break;
        case INSERT:
            gotox(video_width - 6);
            cprintf("INSERT");
            break;
    }
}

void print_buffer() {
    int i;
    gotoxy(0, 0);
    for (i = 0; i < BUFFER_SIZE; i++) {
        cputc(text_buffer[i]);
    }
}

void display_cursor() {
    gotoxy(last_cursor_x, last_cursor_y);
    cputc(text_buffer[last_cursor_y * video_width + last_cursor_x]);
    gotoxy(cursor_x, cursor_y);
    cputc('_');
}

int main() {

    int i;
    
    for (i = 0; i < BUFFER_SIZE; i++) {
        text_buffer[i] = ' ';
    }

    textcolor(COLOR_WHITE);
    bgcolor(COLOR_BLACK);

    clrscr();

    videomode(VIDEOMODE_80x30);
    video_width = 80;
    video_height = 30;

    current_mode = NORMAL;

    cursor_x = 0;
    cursor_y = 0;

    print_mode();
    display_cursor();

    while (1) {
        last_key_in = cgetc();
        switch (current_mode) {
            case NORMAL:
                switch (last_key_in) {
                    case 'i':
                        current_mode = INSERT;
                        break;
                    case 'q':
                        clrscr();
                        exit(0);
                    case 'h':
                        if (cursor_x > 0) {
                            last_cursor_x = cursor_x;
                            cursor_x--;
                        }
                        break;
                    case 'j':
                        if (cursor_y < video_height - 1) {
                            last_cursor_y = cursor_y;
                            cursor_y++;
                        }
                        break;
                    case 'k':
                        if (cursor_y > 0) {
                            last_cursor_y = cursor_y;
                            cursor_y--;
                        }
                        break;
                    case 'l':
                        if (cursor_x < video_width - 1) {
                            last_cursor_x = cursor_x;
                            cursor_x++;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case INSERT:
                switch (last_key_in) {
                    case CH_ESC:
                        current_mode = NORMAL;
                        break;
                    case CH_ENTER:
                        last_cursor_x = cursor_x;
                        cursor_x = 0;
                        last_cursor_y = cursor_y;
                        cursor_y++;
                        break;
                    case CH_DEL:
                        gotoxy(cursor_x, cursor_y);
                        cputc(' ');
                        text_buffer[cursor_y * video_width + cursor_x] = ' ';
                        last_cursor_x = cursor_x;
                        cursor_x--;
                        if (cursor_x < 0) {
                            cursor_x = 0;
                        }
                        break;
                    default:
                        gotoxy(cursor_x, cursor_y);
                        text_buffer[cursor_y * video_width + cursor_x] = last_key_in;
                        last_cursor_x = cursor_x;
                        cursor_x++;
                        break;
                }
        }
        print_buffer();
        display_cursor();
        print_mode();
    }



    return 0;
}
