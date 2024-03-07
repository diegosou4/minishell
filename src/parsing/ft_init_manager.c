#include "../../includes/mini.h"

t_line *ft_init_manager(t_line *line)
{
    line->line = NULL;
    line->color_line = NULL;
    line->usr = NULL;
    line->line_text = NULL;
    
    return line;
}

// t_cmd *ft_init_manager_commands(t_cmd *line)
// {
    
// }
