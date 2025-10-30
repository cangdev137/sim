#ifndef TERMINAL_H
#define TERMINAL_H

#include "init.h"

void show_error_and_exit(const char* message);
void restore_terminal();
void raw_terminal();

#endif
