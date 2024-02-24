/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parseredir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:33:37 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/22 18:33:39 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"


int caseptr(char first, char second)
{
 
    if(first == '>' && second == '>')
        return(4);
    else if(first == '<' && second == '<')
        return(5);
    else if(first == '<' && second == '>')
        return(6);
    else if(first == '<' && (second != '>' || second != '<'))
        return(7);
    else if(first == '>' && (second != '>' || second != '<'))
        return(8);
    return(0);
}


char *ft_parse_redir(char *str)
{
    char *ptr;
    char *new;
    int j;
    j = 0;
    int i = 0; // initialize 'i' to 0
    ptr = str;
    new =  ft_calloc(sizeof(char ), ft_strlen(str) + 1); // allocate space for null character
    while(ptr[j])
    {
        int case_num = caseptr(ptr[j], ptr[j + 1]);
        if(case_num == 0)
            new[i] = ptr[j];
        else if(case_num != 0)
            new[i] = 48 + case_num; 
        if(case_num == 4 || case_num == 5 || case_num == 6)
        {
            j++;
        }
        i++;
        j++;
    }
    return(new);
}
