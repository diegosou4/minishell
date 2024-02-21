

#include "../../includes/mini.h"


int ft_whitespace(char *line)
{
    if(*line == ' ')
    {
    while(*line == ' ')
    {
        line++;
    }
    if(*line == '>' || *line == '<')
    {
        printf("Error");
        return(-1);
    }
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
        ft_whitespace(*line);
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
