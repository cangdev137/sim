#include <defs.h>

//save original terminal settings for exit
struct termios original_terminal_settings;

//initialize editor with empty document
text_editor editor;
void initialize_editor(){
    memset(&editor, 0, sizeof(text_editor));

    editor.total_lines = 1;
    editor.cursor_x = 0;
    editor.cursor_y = 0;
    editor.current_mode = normal_mode;
    editor.command_length = 0;
    editor.has_unsaved_changes = 0;
    strcpy(editor.text_lines[0], "");
    strcpy(editor.filename, "");

    if (sizeof(editor.text_lines) > 0) editor.text_lines[0][0] = '\0';
    editor.filename[0] = '\0';
}

int main(int argc, char* argv[]){
    raw_terminal();
    initialize_editor();

    if(argc >= 2){
        load_file(argv[1]);
    }

    while(1){
        refresh_display();

        int user_input = read_user_input();
        //normal mode input processing
        if (editor.current_mode == normal_mode){
            if (user_input == 'i') { 
                editor.current_mode = insert_mode;
            }
            else if (user_input == ':') { 
                editor.current_mode = command_mode;
            }
            else if (user_input == ARROW_UP || user_input == ARROW_DOWN || 
                     user_input == ARROW_LEFT || user_input == ARROW_RIGHT)
                handle_cursor_movement(user_input);
            else if(user_input == 'x'){
                delete_character_under_cursor();
            }
            else if (user_input == 'o'){
                if (editor.total_lines < MAX_LINES){
                    for(int line = editor.total_lines; line > editor.cursor_y+1; line--){
                        strcpy(editor.text_lines[line], editor.text_lines[line-1]);
                    }
                    strcpy(editor.text_lines[editor.cursor_y+1], "");
                    editor.cursor_y++;
                    editor.cursor_x = 0;
                    editor.total_lines++;
                    editor.current_mode = insert_mode;
                    editor.has_unsaved_changes = 1;
                }
            }
        }
        //insert mode input processing
        else if (editor.current_mode == insert_mode){
            if (user_input == '\x1b'){
                editor.current_mode = normal_mode;
                if (editor.cursor_x > 0) {
                editor.cursor_x--;
                }
            }
            else if(user_input == '\r'){
                split_line_at_cursor();
            }
            else if(user_input == 127 || user_input == ctrl_plus('h')){
                delete_character_before_cursor();
            }
            else if(user_input == ARROW_UP || user_input == ARROW_DOWN ||
                    user_input == ARROW_LEFT || user_input == ARROW_RIGHT){
                handle_cursor_movement(user_input);
            }
            else if(!iscntrl(user_input)){
                insert_char_at_cursor(user_input);
            }
        }
        //command mode input processing
        else if (editor.current_mode == command_mode){
            if (user_input == '\x1b'){
                editor.current_mode = normal_mode;
                editor.command_length = 0;
            }
            else if (user_input == '\r'){
                execute_command();
            }
            else if (user_input == 127 || user_input == ctrl_plus('h')){
                if (editor.command_length > 0){
                    editor.command_length--;
                }
            }
            else if(!iscntrl(user_input) && editor.command_length < sizeof(editor.command_buffer)-1){
                editor.command_buffer[editor.command_length++] = user_input;
            }
        }
     }

    return 0;
}


