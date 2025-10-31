#include <defs.h>

//move cursor based on key press
void handle_cursor_movement(int direction){
    int current_line_length = strlen(editor.text_lines[editor.cursor_y]);

    switch (direction){
        case ARROW_LEFT:
            if (editor.cursor_x > 0) 
                editor.cursor_x--;
            break;
        case ARROW_RIGHT:
            if (editor.cursor_x < current_line_length)
                editor.cursor_x++;
            break;
        case ARROW_DOWN:
            if (editor.cursor_y < editor.total_lines-1){
                editor.cursor_y++;
            }
            break;
        case ARROW_UP:
            if (editor.cursor_y > 0){
                editor.cursor_y--;
                //keep cursor aligned with text
                current_line_length = strlen(editor.text_lines[editor.cursor_y]);
                if (editor.cursor_x > current_line_length){
                    editor.cursor_x = current_line_length;
                }
            }
    }
}



