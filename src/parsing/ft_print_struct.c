/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:44:02 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/20 13:44:04 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"

void printdp(char **str)
{
    int i;

    i = 0;

    while(str[i])
    {
        printf("%s ",str[i]);
        i++;
    }
    printf("\n");
}

void printstruct(t_cmd *commands)
{
    t_cmd *ptr;

    ptr = commands;

    while(ptr != NULL)
    {
        printf("Path: %s\n", ptr->path);
        printf("Args: ");
        printdp(ptr->args);
        printf("FILE 1 %i FILE 2 %i \n", ptr->fd[0], ptr->fd[1]);
        if(ptr->redir != NULL)
        {
            t_redir *pr;
            pr = ptr->redir;
            while(pr != NULL)
            {
                printf("Redir string %s", pr->str);
                printf("File %i", pr->fd);
                pr = pr->next;
            }
        }
        ptr = ptr->next;
    }
}
