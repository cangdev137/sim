#include <init.h>
#include <terminal.h>

//save original terminal settings for exit
struct termios original_terminal_settings;

//initialize main editor struct
text_editor editor;

int main(){
    printf("starting sim...\n");

    int c = read_user_input();
    printf("recieved %c\n", c);

    printf("terminating.\n");
    return 0;
}
