#include <init.h>
#include <terminal.h>

//save original terminal settings for exit
struct termios original_terminal_settings;

//initialize editor with empty document
void initialize_editor(text_editor* editor){
    editor->total_lines = 1;
    editor->cursor_x = 0;
    editor->cursor_y = 0;
    editor->current_mode = normal_mode;
    editor->command_length = 0;
    editor->has_unsaved_changes = 0;
    strcpy(editor->text_lines[0], "");
    strcpy(editor->filename, "");
}

int main(){
    printf("starting sim...\n");

    //initialize main editor struct
    text_editor editor;
    initialize_editor(&editor);
    
    int c = read_user_input();

    printf("terminating...\n");
    return 0;
}
