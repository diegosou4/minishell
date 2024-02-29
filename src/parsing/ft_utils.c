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

char *ft_strcpy(char *dest, const char *src);

#include "../../includes/mini.h"

/*
    🚩 check this function as we are alocating 
    memmory here.
*/
t_cmd *cmdnew(char *args)
{
	t_cmd *comands;
    char **newarg;
    int len;
    int i;

    i = -1;
    len = 0;
	comands = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
    newarg = ft_split(args, '2');

    while (newarg[len] != NULL)
        len++;
    char **modified_list = (char **)malloc((len * 5) * sizeof(char *));
    while (++i < len)
    {
        modified_list[i] = (char *)malloc((ft_strlen(newarg[i]) + 1) * sizeof(char));    
        ft_strcpy(modified_list[i], newarg[i]);
    }
    comands->args = modified_list;
	comands->next = NULL;
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

	// printf("CHECK QUOTES ---------> :%s:\n", str);

    len = ft_strlen(str);
    if ((str[0] == '\'' && str[len - 1] == '\'')
        || (str[0] == '\"' && str[len - 1] == '\"'))
    {
        str[len - 1] = '\0';
        ft_memmove(str, (str + 1), len - 1);
    }
}
void ft_quotes_remove(t_word_list *word_list)
{
    while (word_list)   
    {
        ft_checker_quotes(word_list->word->word);
        word_list = word_list->next;
    }
    
}



char	*ft_strtok(char *str, const char *delimiters)
{
	static char	*buffer = NULL;
	char		*token_start;

	if (!str && !buffer)
		return (NULL);

	if (str)
		buffer = str;

	while (*buffer && ft_strchr(delimiters, *buffer))
		buffer++;

	token_start = buffer;

	buffer = ft_strpbrk(token_start, delimiters);
	if (buffer)
		*buffer++ = '\0';
	return (token_start);
}

int ft_whitespace(char *line)
{
    int i;

    i = 0;
    
    while ((line[i] >= '\b' && line[i] <= '\v') || line[i] == ' ')
    {
        i++;
    }
    if (i == (int) ft_strlen(line))
        return (0);
        
    return (1);
}