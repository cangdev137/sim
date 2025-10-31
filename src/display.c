#include <defs.h>

//get terminal window size
void get_terminal_dimensions(int* rows, int* columns){
    struct winsize window_size;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size) == -1 || window_size.ws_col == 0){
        *rows = 24;
        *columns = 80;
    }
    else{
        *rows = window_size.ws_row;
        *columns = window_size.ws_col;
    }
}

//redraw screen
void refresh_display(){
    int terminal_rows, terminal_columns;
    get_terminal_dimensions(&terminal_rows, &terminal_columns);

    //clear screen, return cursor
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1bH", 3);

    int visible_rows = terminal_rows - 2;

    //display all text lines
    for(int row = 0; row < visible_rows; row++){
        //write line numbers next to content
        if (row < editor.total_lines){
            char line_info[32];
            int info_length = snprintf(line_info, sizeof(line_info), "%4d ", row+1);

            write(STDOUT_FILENO, line_info, info_length);
            write(STDOUT_FILENO, editor.text_lines[row], strlen(editor.text_lines[row]));
        }
        else{
            write(STDOUT_FILENO, "   ~", 4);
        }

        //clear to end of line
        write(STDOUT_FILENO, "\x1b[K", 3); 
        if (row < visible_rows-1){
            write(STDOUT_FILENO, "\r\n", 2);
        }
    }

    //display status line at bottom
    char position_buffer[32];
    char status_line[512];

    snprintf(position_buffer, sizeof(position_buffer), "\x1b[%d;1H", terminal_rows-1);
    write(STDOUT_FILENO, position_buffer, strlen(position_buffer));
    write(STDOUT_FILENO, "\x1b[7m", 4); //invert colors for status bar
    int status_length = snprintf(status_line, sizeof(status_line), " %s %s", 
                                 (strlen(editor.filename) > 0 ? editor.filename :
                                  (editor.has_unsaved_changes ? "[+]" : "")));

    //position cursor
    char position_info[32];
    snprintf(position_info, sizeof(position_info), "%d,%d", editor.cursor_y+1, editor.cursor_x+1);

    int padding = terminal_columns - status_length - strlen(position_info);
    if (padding < 0) padding = 0;

    write(STDOUT_FILENO, status_line, status_length);
    for (int i = 0; i < padding; i++) {
        write(STDOUT_FILENO, " ", 1);
    }
    write(STDOUT_FILENO, position_info, strlen(position_info));
    write(STDOUT_FILENO, "\x1b[m", 3);

    //command and mode line
    snprintf(position_buffer, sizeof(position_buffer), "\x1b[%d;1H", terminal_rows);
    write(STDOUT_FILENO, position_buffer, strlen(position_buffer));
    
    if (editor.current_mode == command_mode) {
        write(STDOUT_FILENO, ":", 1);
        write(STDOUT_FILENO, editor.command_buffer, editor.command_length);
    } else if (editor.current_mode == insert_mode) {
        write(STDOUT_FILENO, "-- INSERT --", 12);
    }
    write(STDOUT_FILENO, "\x1b[K", 3); 

    char cursor_position[32];
    snprintf(cursor_position, sizeof(cursor_position), "\x1b[%d;%dH", editor.cursor_y+1, editor.cursor_x+6);
    write(STDOUT_FILENO, cursor_position, strlen(cursor_position));
}
    


