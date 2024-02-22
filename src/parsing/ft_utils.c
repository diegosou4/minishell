/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-pma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:21:34 by juan-pma          #+#    #+#             */
/*   Updated: 2024/02/21 10:49:44 by juan-pma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

t_cmd *cmdnew(char *args)
{
	t_cmd *comands;

	comands = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
	comands->args = ft_split(args,'2');
	comands->next = NULL;
	comands->fd[0] = -1;
	comands->fd[1] = -1;
	comands->redir = NULL;
	
	return(comands);
}

void cmdinback(t_cmd **comands,char *args)
{
	t_cmd *ptr;
	t_cmd *last;

	last = cmdnew(args);
	if(last == NULL)
		return;
	ptr = *(comands);
	while(ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	ptr->next = last;

}
char *ft_strcpy(char *dest, const char *src) 
{
    if (!src)
        return (NULL);
    while (*src) 
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return dest;
}

void ft_checker_quotes(char *str)
{
    int len;

    len = ft_strlen(str);
    if (str[0])
    if (str[len - 1] == '\"' || str[len - 1] == '\'')
        str[len - 1] = '\0';
    printf("checker quotes :%s:\n", str);

}