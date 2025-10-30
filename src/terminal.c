#include "terminal.h"

//print error message and quit program
void show_error_and_exit(const char* message){
    perror(message);
    exit(1);
}

//restore orignal terminal on exit
void restore_terminal(){
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_terminal_settings) == -1){
        show_error_and_exit("tcsetatrr");
    }
}

//set up terminal for raw input
void raw_terminal(){
    if (tcgetattr(STDIN_FILENO, &original_terminal_settings) == -1){
        show_error_and_exit("tcgetattr");
    }

    //restore orignal terminal settings on exit
    atexit(restore_terminal);

    //update terminal settings
    struct termios raw_settings = original_terminal_settings;
    raw_settings.c_iflag &= ~(ICRNL | IXON);
    raw_settings.c_oflag &= ~(OPOST);
    raw_settings.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    raw_settings.c_cc[VMIN] = 0;
    raw_settings.c_cc[VTIME] = 1;

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_settings) == -1){
        show_error_and_exit("tcsetattr");
    }
}

