#include "../../includes/mini.h"

void ft_free_double_pointers(char **split_line)
{
    int i;

    i = -1;
    if (split_line == NULL)
        return ;
    while (split_line[++i])
        free(split_line[i]);
    free(split_line);
}
