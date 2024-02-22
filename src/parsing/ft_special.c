

#include "../../includes/mini.h"

static int ft_check(char *line, char c)
{
    int i;
    char different;

    i = 0;
    if(line[i] == ' ')
    {
        while(*line == ' ' && (*line != '>' && *line != '<'))
            line++;
        if(*line == '>' || *line == '<')
        {
            printf("parse error found near '%c'\n", *line);
            return(-1);
        }
    }
    if(c == '>')
        different = '<';
    if(c == '<')
        different = '>';
    if (c == '<' && *line == different)
        return (0);
    if(*line == different)
    {
        printf("parse error found near '%c'\n", different);
        return(-1);
    }
    return(0);
}

static void ft_space (char **line)
{
    while(**line == ' ')
        (*line)++;
}

int ft_special_case(char *modified_line, int j, char **line)
{
    char c[2];
    c[0] = **line;

    if(c[0] == '>' || c[0] == '<')
    {
        modified_line[j++] = '2';
        modified_line[j++] = c[0];
        (*line)++;
        if (ft_check(*line, c[0]) == -1)
            return(-2);
        ft_space(line);
    }
    else if (c[0] == '|')
    {
        modified_line[j++] = '3';
    }
    while(**line == '>' || **line == '<')
    {
        c[1] = **line;
        if(c[1] == '>' || c[1] == '<')
        {
            modified_line[j++] = c[1];
            (*line)++;
        }
        ft_space(line);
    }  
    if(c[0] == '>' || c[0] == '<')
         modified_line[j++] = '2';
    return(j);  
}
