/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special_case.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:45:37 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/20 15:45:38 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"


int ft_special_case(char *modified_line, int j, char **line)
{
    char c;
    c = **line;
    char s;
    if(c == '>' || c == '<')
    {
        modified_line[j++] = '2';
        modified_line[j++] = c;
        (*line)++;
    }
    while(**line == ' ' || **line == '>' || **line == '<')
    {
        s = **line;
        if(s == '>' || s == '<')
        {
            modified_line[j++] = s;
            (*line)++;
        }
        while(**line == ' ')
            (*line)++;
    }  
    if(c == '>' || c == '<')
         modified_line[j++] = '2';
    return(j); 
}
