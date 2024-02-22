/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-pma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:44:08 by juan-pma          #+#    #+#             */
/*   Updated: 2024/02/21 19:55:24 by juan-pma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static	char *ft_string_handle(char *line, char *modified_line)
{
	int	j;
	char	flag;
	char	*ptr;

	ptr = line;
	flag = 0;
	j = 0;
	while (*ptr)
	{
		if (flag == 0 && (*ptr == '\"' || *ptr == '\''))
			flag = *ptr;
		else if (flag == *ptr)
			flag = 0; 
		if (flag == 0 && *ptr == ' ') 
			*ptr = '2';
		if(flag == 0 && *ptr == '|')
			*ptr = '3';
		else if (flag == 0)
		{
			j = ft_special_case(modified_line, j, &ptr);
			if (j == -2)
				return(NULL);
		}
		if (flag == 0 && *ptr == '|')
			*ptr = '3';
		modified_line[j++] = *ptr;
		ptr++;
	}
	return (modified_line);
}

t_cmd	*returnmystruct(char *newline)
{
	t_cmd	*commands;
	char	**arr;
	int	i;
	char	**args;

	arr = ft_split(newline,'3');
	i = 1;
	char **arr_cpy = ft_doublepointecpy(arr);
	while (*arr_cpy)
	{
		printf("hola :%s:\n", *arr_cpy);
		arr_cpy++;
	}
	commands = cmdnew(arr[0]);
	while (arr[i] != NULL && arr_cpy)
	{
		cmdinback(&commands,arr[i]);
		i++;
	}
	t_cmd *ptr;
	ptr = commands;
	while (ptr != NULL)
	{
        args = ptr->args;
        int k;
        k = 0;
        while(args[k] != NULL)
        {
            printf("%s\n",args[k]);
            k++;
        } 
        printf("next struct -->\n");
        ptr = ptr->next;
    }
   return(commands);
}

char	*ft_create_string(char *line)
{
	char *new_line;
	t_cmd *comands;

	new_line = ft_calloc(ft_strlen(line), sizeof(char*));
	new_line = ft_string_handle(line, new_line);
	if (new_line)
		comands = returnmystruct(new_line);
	return (new_line);
}
