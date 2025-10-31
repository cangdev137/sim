#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <sys/ioctl.h>

/* MACROS */
#define MAX_LINES 1000
#define MAX_LINE_LENGTH 256
#define ARROW_UP 1000
#define ARROW_DOWN 1001
#define ARROW_RIGHT 1002
#define ARROW_LEFT 1003
#define ESC_KEY 0x1b
#define ctrl_plus(k) ((k) & 0x1f)

/* FUNCTIONS */
//terminal.c
//display an error and terminate program
void show_error_and_exit(const char* message);
//restore default terminal settings
void restore_terminal();
//configure raw terminal for program
void raw_terminal();

//fileio.c
//load file contents into editor
void load_file(const char* filename);
//save editor contents to file
void save_to_file();

//textio.c
//read a single byte from the user input
int read_user_input();

//cursor.c
//move cursor based on key press
void handle_cursor_movement(int direction);

//commands.c
//clear screen and smoothly exit
void clear_screen_and_exit();
//execute editor command
void execute_command();

/* TYPEDEF */
//editor mode
typedef enum { normal_mode, insert_mode, command_mode } editor_mode;

//main editor data
typedef struct{
    char text_lines[MAX_LINES][MAX_LINE_LENGTH];
    editor_mode current_mode;
    int total_lines;
    int cursor_x, cursor_y; //
    char filename[256];
    char command_buffer[256];
    int command_length;
    int has_unsaved_changes;
} text_editor;

/* GLOBAL VARIABLES */
extern struct termios original_terminal_settings;
extern text_editor editor;

#endif

