#include "../../includes/mini.h"



void *ft_parse_manager()
{
    char *line;
    // char *new_line;

    while (1)
    {
        line = readline("🐧>shell:$");
        // Check for Ctrl+D (EOF) to exit the loop
        if (!line)
            break;
        // Create the line history. 
        add_history(line);
        ft_create_string(line);
        // recieve the line, that was readed.
        free(line);
    }
    return NULL;
}