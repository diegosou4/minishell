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


/*
 * 1. This function will create tokens, based 
 * on a string. The return value, is a pointer (char *) 
 * that represent the token that is created based 
 * on a separator.The funcion can handle multiple separators.
 * 2. This function is optimized to skip the single quotes ('') and double quotes ("")
 * and the use is to create the tokens based on a pipe. (|)
 * 3. Description. 
 * 	The first while. 
 *		// Skip over leading delimiters
 * */

char	*ft_help(char *str, char *token_start)
{
	char *buffer;

	buffer = str;
	if (*buffer == '\"')
		buffer = ft_strchr(token_start, '\"');
	else if (*buffer == '\'')
		buffer = ft_strchr(token_start, '\'');
	if (buffer != NULL)
		*buffer++ = '\0';
	return(buffer);
}

char	*ft_strtok(char *str, const char *delimiters)
{
	static char *buffer = NULL;
	char        *token_start;
	if (str != NULL)
		buffer = str;
	else if (buffer == NULL)
		return (NULL);
	while (*buffer != '\0' && ft_strchr(delimiters, *buffer) != NULL)
		buffer++;
	token_start = buffer;
	if (*buffer == '\"' || *buffer == '\'')
	{
		token_start++;
		buffer = ft_help(buffer, token_start);
	}
	else
	{
		buffer = ft_strpbrk(token_start, delimiters);
		if (buffer != NULL)
			*buffer++ = '\0';
	}
	return (token_start);
}

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

