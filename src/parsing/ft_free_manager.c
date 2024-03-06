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
void ft_free_env_list(t_env *env)
{
    t_env *current;
    t_env *temp;

    current = env;
    while (current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp->key);
        free(temp);
    }
}

void ft_free_line_struct(t_line *line)
{
    free(line->line_text);
	free(line->color_line);
}
