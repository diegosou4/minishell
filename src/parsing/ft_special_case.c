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
    if(**line == '>')
    {
        modified_line[j++] = '2';
        modified_line[j++] = '>';
        (*line)++;
        if(**line == '>')
        {
            modified_line[j++] = '>';
            (*line)++;
        }
        while(**line == ' ')
            (*line)++;
            
        modified_line[j++] = '2';
    }
    return(j);
}
