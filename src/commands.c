#include <defs.h>

//clear screen and exit cleanly
void clear_screen_and_exit(){
    write(STDOUT_FILENO, "\x1b[2J", 4); //clear screen
    write(STDOUT_FILENO, "\x1b[H", 3); //move cursor home
    exit(0);                                        
}

//execute sim command
void execute_command(){
    editor.command_buffer[editor.command_length] = '\0';

    //quit if no unsaved changes
    if (strcmp(editor.command_buffer, "q") == 0){
        if (editor.has_unsaved_changes){
            editor.current_mode = normal_mode;
            editor.command_length = 0;
            return;
        }
        clear_screen_and_exit();
    }
    //force quit
    else if (strcmp(editor.command_buffer, "q!") == 0){
        clear_screen_and_exit();
    }
    //save to file and quit
    else if (strcmp(editor.command_buffer, "wq") == 0){
        if (strlen(editor.filename) > 0){
            save_to_file();
        }
        clear_screen_and_exit();
    }
    //save to default file
    else if(strncmp(editor.command_buffer, "w ", 2) == 0){
        strcpy(editor.filename, editor.command_buffer+2);
        save_to_file();
    }

    //return to normal mode
    editor.current_mode = normal_mode;
    editor.command_length = 0;
}

