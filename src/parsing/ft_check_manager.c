#include "../../includes/mini.h"

/*
    This function checks for double pipes in the parsed input line.
    It iterates through the array of strings representing the line and 
    checks if two consecutive strings are both pipes or if a pipe is 
    followed by a NULL string, indicating a void character after the pipe.

    Arguments:
        - line: Array of strings representing the parsed input line.
        - operations: Structure containing information about operations.

    Returns:
        - 1 if no double pipes are found, indicating success.
        - 0 if double pipes are found or a pipe is followed by a void character.
*/
static int ft_special_pipe_case(char *line)
{
    int i;

    i = -1;
    if (line[0] == '|' && line[1] == '|')
    {
        printf("parse error near `||' More than one pipe found! 🚰🐟\n");
        return (0);
    }
    return(1);
}
static int ft_check_pipes(char **line, t_operations *operations)
{
    int i = 0;

    while (line[i] != NULL) 
    {
        if (ft_special_pipe_case(line[i]) == 0)
            return (0);
        if (strcmp(line[i], operations->pipe) == 0 &&
             (line[i + 1] == NULL || strcmp(line[i + 1], "|") == 0)) 
        {
            if (line[i + 1] == NULL)
                printf("parse error near `|' (no args) 🚰🙊\n");
            else 
                printf("parse error near `||' More than one pipe found! 🚰🐟\n");
            return 0; // Indicate failure
        }
        i++;
    }
    return 1;
}
/*
    This function checks for syntax errors related to redirection symbols
    (>, <) and specific combinations of redirection symbols and subsequent arguments.
    It counts the number of redirection symbols encountered in the parsed input line,
    ensuring that no more than two redirection symbols are present.

    Arguments:
        - line: Array of strings representing the parsed input line.
        - operations: Structure containing information about operations.

    Returns:
        - 1 if no syntax errors are found, indicating success.
        - 0 if a syntax error is detected.
*/

static int ft_check_directions(char **line, t_operations *operations)
{
    int i;
    int j;
    int count;

    count = 0;
    j = 0;
    i = -1;

    while (line[++i])
    {
        j = 0;
        while (line[i][j])
        {
            if (line[i][j] == '>')
            {
                count++;
                if (count >= 3)
                {
                     printf("shell: syntax error near unexpected token `>' 💥\n");
                     return (0);
                 }
            }
            else if (line[i][j] == '<')
            {
                count++;
                if (count >= 3)
                {
                     printf("shell: syntax error near unexpected token `<' 💥\n");
                     return (0);
                 }
            }
            j++;
        }
    }
    if (ft_strcmp(line[i -1], operations->apppend_out) == 0 
            || ft_strcmp(line[i -1], operations->here_doc) == 0)
        {
            printf("error found void 🚫 args 1. \n");
            return (0);
        }
    else if (ft_strcmp(line[i -1], operations->redir_input) == 0 
            || ft_strcmp(line[i -1], operations->redir_input) == 0)
        {
        printf("error found void 🚫 args.\n");
        return (0);
        }
    return (1);
}

int ft_check_input(char *line, t_operations *operations)
{
    char **split_line;
    
    split_line = ft_split(line, ' ');
    // check void spaces or empty string. 
    if (!split_line || !split_line[0])
        return (0);
    // ft_print_doble_char(split_line);
    ft_init_operations(operations);
    // This check if double pipes are found, or only one pipe, or a pipe without any command. 
    if (!ft_check_pipes(split_line, operations))
        return (0);
    // this check if there is any <<< >>> <>> <<> or any combination. 
    if (!ft_check_directions(split_line, operations))
        return(0);
    return (1);
}
