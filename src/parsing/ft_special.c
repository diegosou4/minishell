/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-pma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 08:34:08 by juan-pma          #+#    #+#             */
/*   Updated: 2024/02/24 08:34:15 by juan-pma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

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
        ft_space(line);
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
