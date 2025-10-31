#include <init.h>

//load file into editor
void load_file(const char* filename){
    //cache name for later saves
    strcpy(editor.filename, filename);

    FILE* fp = fopen(filename, "r");

    //if no file is provided, start with empty editor
    if (!fp){
        strcpy(editor.text_lines[0], "");
        editor.total_lines = 1;
        return;
    }

    //otherwise count lines based on data in provided file
    editor.total_lines = 0;
    while (fgets(editor.text_lines[editor.total_lines], MAX_LINE_LENGTH, fp) && editor.total_lines < MAX_LINES){
        //replace trailing newline with null terminator
        size_t line_length = strlen(editor.text_lines[editor.total_lines]);
        if (line_length > 0 && editor.text_lines[editor.total_lines][line_length-1] == '\n'){
            editor.text_lines[editor.total_lines][line_length-1] = '\0';
        }

        editor.total_lines++;
    }

    //handle empty file
    if (editor.total_lines == 0){
        strcpy(editor.text_lines[0], "");
        editor.total_lines = 1;
    }

    fclose(fp);
}

//save text to file
void save_to_file(){
    //don't allow save to empty file
    if (strlen(editor.filename) == 0){
        return;
    }
    //open file
    FILE* fp = fopen(editor.filename, "w");
    if (!fp){
        return;
    }
    //write lines to file
    for (int line = 0; line < editor.total_lines; line++){
        fprintf(fp, "%s\n", editor.text_lines[line]);
    }
    //mark work as saved
    fclose(fp);
    editor.has_unsaved_changes = 0;
}








