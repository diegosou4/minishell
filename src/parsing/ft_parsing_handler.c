#include "../../includes/mini.h"


char *ft_lexer_analysis(char *tokens)
{
    char delimiter;
    char **delimiter_holder;
    int i = -1;
    t_cmd token_structure;

    delimiter_holder = (char **)malloc(sizeof(char *) * 1000);
    delimiter = '2';
    delimiter_holder = ft_split(tokens, delimiter);
    while (delimiter_holder[++i])
    {
        delimiter_holder[0];
        printf(":%s:\n", delimiter_holder);
    }
    free(delimiter_holder);
    return NULL;
}

int ft_parse_handler(char *str, const char *delimiters)
{
    char **token_holder;
    
    token_holder = (char **)malloc(sizeof(char *) * ft_strlen(str)); // Allocate memory for 100 pointers
    if (!token_holder && !delimiters)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    token_holder = ft_split(str, '3');
    int j = 0;
    while (token_holder[j] != NULL)
    {
        ft_lexer_analysis(token_holder[j]);
        j++;
    }
    free(token_holder);
    return 0;
}

static char *ft_string_handle(char * line, char *modified_line)
{
    int j;
    char flag;
    char *ptr;

    ptr = line;
    flag = 0;
    j = 0;
    while (*ptr)
    {
        if (flag == 0 && (*ptr == '\"' || *ptr == '\''))
            flag = *ptr;
        else if (flag == *ptr)
            flag = 0; 
        if (flag == 0 && *ptr == ' ') 
            *ptr = '2';
        else if (flag == 0)
        {
            j = ft_special_case(modified_line, j, &ptr);
            if (j == -2)
                return(NULL);
        }
        if (flag == 0 && *ptr == '|')
            *ptr = '3';
        modified_line[j++] = *ptr;
        ptr++;
    }
    return (modified_line);
}

char *ft_create_string(char *line)
{
    char *new_line;
    int i;
    char *ptr = ft_strdup(line);
    i = 0;
    new_line = ft_calloc(ft_strlen(line), sizeof(char*));
    new_line = ft_string_handle(ptr, new_line);
    printf(":%s:\n", new_line);
    if (new_line)
        ft_parse_handler(new_line, "|");
    return (new_line);
    free(line);
}