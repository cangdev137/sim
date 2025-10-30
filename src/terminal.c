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

    //disable ENTER and CTRL+S/CTRL+Q
    raw_settings.c_iflag &= ~(ICRNL | IXON);     
    //disable output post-processing
    raw_settings.c_oflag &= ~(OPOST);
    //disable character echoing, CTRL+C/CTRL+Z
    raw_settings.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN); 
    //set min character count and timeout for read()
    raw_settings.c_cc[VMIN] = 0;
    raw_settings.c_cc[VTIME] = 1;

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_settings) == -1){
        show_error_and_exit("tcsetattr");
    }
}

//read a single key press from the user
int read_user_input(){
    int bytes_read;
    char input_char;

    //read next byte
    while ((bytes_read = read(STDIN_FILENO, &input_char, 1)) != 1){
        if (bytes_read == -1 && errno != EAGAIN){
            show_error_and_exit("read");
        }
    }

    //check for escape sequence
    if (input_char == ESC_KEY){
        char escape_sequence[3];
        if (read(STDIN_FILENO, &escape_sequence[0], 1) != 1)
            return ESC_KEY;
        if (read(STDIN_FILENO, &escape_sequence[1], 1) != 1)
            return ESC_KEY;
        if (escape_sequence[0] == '['){
            switch(escape_sequence[1]){
                case 'A': 
                    return ARROW_UP;
                case 'B': 
                    return ARROW_DOWN;
                case 'C': 
                    return ARROW_RIGHT;
                case 'D': 
                    return ARROW_LEFT;
            }
        }

        return ESC_KEY;
    }
    
    return input_char;
}
    

