

#include "../Headers/Engine_reader.h"


Status  engine_reader_file_economy(Engine*  engine, char*   namefile){
    if(!engine || !namefile) return ERROR;

    char    line[WORD_SIZE] = "";
    FILE*   file = fopen(namefile, "r");
    if(!file) return ERROR;

    while (fgets(line,WORD_SIZE, file))
    {
        if ()
        {
            /* code */
        }
        
    }
    
}
