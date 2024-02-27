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
    return (1);
}
static int ft_check_pipes(char **line)
{
    int i = 0;

    while (line[i] != NULL)
    {
        if (ft_special_pipe_case(line[i]) == 0)
            return (0);
        if (strcmp(line[i], "|") == 0 &&
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
    if (line[i - 1][ft_strlen(line[i - 1]) - 1] == '|')
    {
        printf("parse error near `|' (no args) 🚰🙊\n");
        return (0);
    }
    return (1);
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
int ft_check_valid_redir(t_word_list *word_list)
{
    while (word_list->next)
    {
        if (word_list->word->word[0] == '>')
        {
            if ((word_list->word->flags != 1 ) && (word_list->word->flags != 4 ))
            {
            printf("🚫 parse error near `>' \n");
            return (0);
            }
        }
        else if (word_list->word->word[0] == '<')
        {
            if ((word_list->word->flags != 2 ) && (word_list->word->flags != 3 ))
            {
            printf("🚫 parse error near `>' \n");
            return (0);
            }
        }
       
        word_list = word_list->next;
    }

    if (word_list->word->word[0] == '<')
    {
        printf("🚫 parse error near `|' \n");
        return (0);
    }
    return (1);
}

int ft_check_redir_pipes(char **line)
{
    int i;
    i = -1;

    if (!line || !*line)
        return (0);
    while (line[++i] && line[i + 1])
    {

        if ((ft_strcmp(line[i], "<<") == 0 || ft_strcmp(line[i], ">>") == 0) &&
            ft_strcmp(line[i + 1], "|") == 0)
        {
            printf("parse error near `|' 🚫. \n");
            return (0);
        }
        else if ((ft_strcmp(line[i], ">") == 0 || ft_strcmp(line[i], "<") == 0) &&
                 ft_strcmp(line[i + 1], "|") == 0)
        {
            printf("parse error near `|' 🚫.\n");
            return (0);
        }
    }

    return (1);
}
static int ft_check_directions(char **line)
{

    int i;

    i = -1;
    while (line[++i])
        ;
    if (ft_strcmp(line[i - 1], "<<") == 0 || ft_strcmp(line[i - 1], ">>") == 0)
    {
        printf("error found void 🚫 args 1. \n");
        return (0);
    }
    else if (ft_strcmp(line[i - 1], "<") == 0 || ft_strcmp(line[i - 1], ">") == 0)
    {
        printf("error found void 🚫 args.\n");
        return (0);
    }

    return (1);
}
/*

    This funciton will check the input as is given by the user, 
    without any pretreatement, in order to find error before creating any 
    structure. 

*/
int ft_check_input(char *line)
{
    char **split_line;
    if (!line)
        return (0);
    split_line = ft_split(line, ' ');
    // check void spaces or empty string.
    if (!split_line || !split_line[0])
        return (0);
    // This check if double pipes are found, or only one pipe, or a pipe without any command.
    if (!ft_check_pipes(split_line) ||
        !ft_check_redir_pipes(split_line) ||
        !ft_check_directions(split_line))
    {

        ft_free_double_pointers(split_line);
        return (0);
    }
    // this check if there is any <<< >>> <>> <<> or any combination.
    ft_free_double_pointers(split_line);
    return (1);
}
