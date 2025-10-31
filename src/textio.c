#include <defs.h>

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

//insert character at current position of cursor
void insert_char_at_cursor(char insertChar){
    int current_line_length = strlen(editor.text_lines[editor.cursor_y]);
    if(current_line_length >= MAX_LINE_LENGTH-1) return;

    //make space for next character
    memmove(&editor.text_lines[editor.cursor_y][editor.cursor_x+1],
             &editor.text_lines[editor.cursor_y][editor.cursor_x],
             current_line_length - editor.cursor_x + 1);

    //insert next character
    editor.text_lines[editor.cursor_y][editor.cursor_x] = insertChar;
    editor.cursor_x++;
    editor.has_unsaved_changes = 1;
}

//split line at current position of cursor
void split_line_at_cursor(){
    if (editor.total_lines >= MAX_LINES){
        return;
    }

    //move lines down to make space for new line
    for(int line = editor.total_lines; line > editor.cursor_y+1; line--){
        strcpy(editor.text_lines[line], editor.text_lines[line]);
    }
    //split current line
    strcpy(editor.text_lines[editor.cursor_y+1], &editor.text_lines[editor.cursor_y][editor.cursor_x]);
    editor.text_lines[editor.cursor_y][editor.cursor_x] = '\0';
    editor.cursor_y++;
    editor.cursor_x = 0;
    editor.total_lines++;
    editor.has_unsaved_changes = 1;
}

void delete_character_under_cursor(){
    if (editor.cursor_x < strlen(editor.text_lines[editor.cursor_y])) {
        memmove(&editor.text_lines[editor.cursor_y][editor.cursor_x], 
                &editor.text_lines[editor.cursor_y][editor.cursor_x + 1], 
                    strlen(editor.text_lines[editor.cursor_y]) - editor.cursor_x);
        editor.has_unsaved_changes = 1;
    }
}
void delete_character_before_cursor(){
    if (editor.cursor_x == 0 && editor.cursor_y == 0){
        return;
    }

    //delete character in same line
    if (editor.cursor_x > 0){ int current_line_length = strlen(editor.text_lines[editor.cursor_y]);
        //move chars in buffer back by one
        memmove(&editor.text_lines[editor.cursor_y][editor.cursor_x-1],
                &editor.text_lines[editor.cursor_y][editor.cursor_x],
                current_line_length - editor.cursor_x + 1);

        //fix cursor
        editor.cursor_x--;
    }
    //delete char at start of line
    else{
        //fix cursor
        editor.total_lines--;
        editor.cursor_y--;

        //join with previous line
        editor.cursor_x = strlen(editor.text_lines[editor.cursor_y]);
        strcat(editor.text_lines[editor.cursor_y], editor.text_lines[editor.cursor_y+1]);

        //move remaining lines up
        for(int line = editor.cursor_y+1; line < editor.total_lines - 1; line++){
            strcpy(editor.text_lines[line], editor.text_lines[line+1]);
        }

    }

    editor.has_unsaved_changes = 1;
}
