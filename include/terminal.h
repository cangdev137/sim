#ifndef TERMINAL_H
#define TERMINAL_H

#include "init.h"

//macros
#define ARROW_UP 1000
#define ARROW_DOWN 1001
#define ARROW_RIGHT 1002
#define ARROW_LEFT 1003

//functions
void show_error_and_exit(const char* message);
void restore_terminal();
void raw_terminal();
int read_user_input();

#endif
