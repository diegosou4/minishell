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
        modified_line[j++] = *ptr;
        ptr++;
    }
    return (modified_line);
}

int ft_parse_handler(char *str, const char *delimiters)
{
    char **token_holder;
    int i = 0;
    
    token_holder = (char **)malloc(sizeof(char *) * ft_strlen(str)); // Allocate memory for 100 pointers
    if (!token_holder)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Tokenize the string using ft_strtok
    char *tokens = ft_strtok(str, delimiters);
    while (tokens != NULL)
    {
        token_holder[i] = tokens;
        tokens = ft_strtok(NULL, delimiters);
        i++;
    }

    // Set the last element of token_holder to NULL
    token_holder[i] = NULL;

    // Print the tokens
    int j = 0;
    while (token_holder[j] != NULL)
    {
        // printf("token : :%s:\n", token_holder[j]);
        ft_lexer_analysis(token_holder[j]);
        j++;
    }
    free(token_holder);
    return 0;
}

char *ft_create_string(char *line)
{
    char *new_line;

    new_line = ft_calloc(ft_strlen(line), sizeof(char*));
    new_line = ft_string_handle(line, new_line);
    if (new_line)
        ft_parse_handler(new_line, "|");
    return (new_line);
    free(line);
}