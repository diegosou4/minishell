#include "../../includes/mini.h"

char *ft_strtok(char *str, const char *delimiters)
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
    while (*buffer != '\0' && ft_strchr(delimiters, *buffer) != NULL)
    {
        buffer++;
    }

    // Check for quoted strings
    char *token_start = buffer;
    if (*buffer == '\"')
    {
        token_start++;
        buffer = ft_strchr(token_start, '\"');
        if (buffer != NULL)
        {
            *buffer++ = '\0';
        }
    }
    else if (*buffer == '\'')
    {
        token_start++;
        buffer = ft_strchr(token_start, '\'');
        if (buffer != NULL)
        {
            *buffer++ = '\0';
        }
    }
    else
    {
        // Find the end of the token
        buffer = ft_strpbrk(token_start, delimiters);
        if (buffer != NULL)
        {
            *buffer++ = '\0';
        }
    }
    return token_start;
}
