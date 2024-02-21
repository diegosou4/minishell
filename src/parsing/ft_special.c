

#include "../../includes/mini.h"

static int ft_check(char *line, char c)
{
    int i;
    char special;
    char different;

    i = 0;
    if(line[i] == ' ')
    {
        while(*line == ' ')
            line++;
        special = *line;
        if(special == '>' || special == '<')
        {
            printf("parse error found near '%c'\n", special);
            return(-1);
        }
    }
    if(c == '>')
        different = '<';
    if(c == '<')
        different = '>';
    if(*line == different)
    {
        printf("parse error found near '%c'\n", different);
            return(-1);
    }
    return(0);
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
        {
            return(-2);
        }
        
    }
    while(**line == '>' || **line == '<')
    {
        c[1] = **line;
        if(c[1] == '>' || c[1] == '<')
        {
            modified_line[j++] = c[1];
            (*line)++;
        }
        while(**line == ' ')
            (*line)++;
    }  
    if(c[0] == '>' || c[0] == '<')
         modified_line[j++] = '2';
    return(j);  
}
