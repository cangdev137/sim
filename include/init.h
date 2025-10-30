#ifndef INIT_H
#define INIT_H

//required libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <sys/ioctl.h>

//macros
#define MAX_LINES 1000
#define MAX_LINE_LENGTH 256
#define ESC_KEY 0x1b
#define ctrl_plus(k) ((k) & 0x1f)


//custom types
typedef enum { normal_mode, insert_mode, command_mode } editor_mode;

//main editor data
typedef struct{
    char text_lines[MAX_LINES][MAX_LINE_LENGTH];
    editor_mode mode;
    int total_lines;
    int cursor_x, cursor_y; //
    char filename[256];
    char command_buffer[256];
    int command_length;
    int has_unsaved_changes;
} text_editor;

//global vars
extern struct termios original_terminal_settings;

#endif

