#include "../../includes/mini.h"

char *ft_lexer_analysis(char *tokens)
{
    char *token;
    const char *delimiter;
    char **delimiter_holder;
    int i = -1;

    delimiter_holder = (char **)malloc(sizeof(char *) * 1000);
    delimiter = "2";
    token = ft_strtok(tokens, delimiter);
    while (token != NULL)
    {
        if(token[0])
        {
            delimiter_holder[++i] = token;
            printf(":%s:\n", delimiter_holder[i]);
        }
        token = ft_strtok(NULL, delimiter);
    }
    free(delimiter_holder);

    return NULL;
}

static char *ft_string_handle(char * line, char *modified_line)
{
    size_t i;
    size_t j;
    char flag;

    flag = 0;
    i = 0;
    j = 0;
    while (line[i])
    {
        if (flag == 0 && (line[i] == '\"' || line[i] == '\''))
            flag = line[i];
        else if (flag == line[i])
            flag = 0; 
        if (flag == 0 && line[i] == ' ') 
            line[i] = '2';
        else if (flag == 0 ) 
            ft_special_char(line);
        modified_line[j++] = line[i++];
    }
    return (modified_line);
}

void ft_create_string(char *line)
{
    line = ft_string_handle(line, ft_calloc(ft_strlen(line), sizeof(char*)));

    printf("new_line: \n%s\n", line);
    free(line);
}