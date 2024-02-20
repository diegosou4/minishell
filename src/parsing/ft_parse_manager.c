#include "../../includes/mini.h"

char *homemade_strtok(char *str, const char *delimiters)
{
    static char *buffer = NULL;
    if (str != NULL)
    {
        buffer = str;
    }
    else if (buffer == NULL)
    {
        return NULL;
    }

    // Skip over leading delimiters
    while (*buffer != '\0' && strchr(delimiters, *buffer) != NULL)
    {
        buffer++;
    }

    // Check for quoted strings
    char *token_start = buffer;
    if (*buffer == '\"')
    {
        token_start++;
        buffer = strchr(token_start, '\"');
        if (buffer != NULL)
        {
            *buffer++ = '\0';
        }
    }
    else if (*buffer == '\'')
    {
        token_start++;
        buffer = strchr(token_start, '\'');
        if (buffer != NULL)
        {
            *buffer++ = '\0';
        }
    }
    else
    {
        // Find the end of the token
        buffer = strpbrk(token_start, delimiters);
        if (buffer != NULL)
        {
            *buffer++ = '\0';
        }
    }
    return token_start;
}

char *ft_lexer_analysis(char *tokens)
{
    char *token;
    const char *delimiter;
    char **delimiter_holder;
    int i = -1;

    delimiter_holder = (char **)malloc(sizeof(char *) * 1000);
    delimiter = "2";
    token = homemade_strtok(tokens, delimiter);
    while (token != NULL)
    {
        if(token[0])
        {
            delimiter_holder[++i] = token;
            printf(":%s:\n", delimiter_holder[i]);
        }
        token = homemade_strtok(NULL, delimiter);
    }
    free(delimiter_holder);

    return NULL;
}

int ft_parse_handler(char *str, const char *delimiters)
{
    char **token_holder;
    int i;

    i = 0;
    token_holder = (char **)ft_calloc((ft_strlen(str) * 3), sizeof(char *));
    // Tokenize the string using homemade_strtok
    char *tokens = homemade_strtok(str, delimiters);
    while (tokens != NULL)
    {
        token_holder[i] = tokens;
        tokens = homemade_strtok(NULL, delimiters);
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

void *ft_parse_manager()
{
    char *line;

    while (1)
    {
        line = readline("🐧>shell:$");
        // Check for Ctrl+D (EOF) to exit the loop
        if (!line)
            break;
        // Create the line history. 
        add_history(line);
        // recieve the line, that was readed.
        ft_parse_handler(line, "|");
        free(line);
    }
    return NULL;
}