#include "../../includes/mini.h"

static int ft_check_pipes(char **line, t_operations *operations)
{
    int i = -1;
    ft_print_doble_char(line);
    printf("operation : %s", operations->pipe);
    while (line[++i])
    {
        if ((line[i][0] == '|' && line[i + 1][0] == '|') || (line[i][0] == '|' && line[i][1] == '|' ))  
            printf("double pipe found \n");
    }
    if (line[i-1][0] == '|')
        printf("error void pipe found");
    return 1;
}
int ft_check_input(char *line, t_operations *operations)
{
    char **split_line;

    split_line = ft_split(line, ' ');
    ft_init_operations(operations);
    ft_check_pipes(split_line, operations);
    return (0);

}
