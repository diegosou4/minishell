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

static int ft_check_close_q(const char *ptr)
{
	if (*ptr == '\'')
	{
		if (!ft_strchr((const char *)(ptr + 1), '\''))
		{
			printf("Error Unclosing quotes \' 🔓\n");
			return (0);
		}
	}
	else if (*ptr == '\"')
	{
		if (!ft_strchr((const char *)(ptr + 1), '\"'))
		{
			printf("Error Unclosing quotes \" 🔓\n");
			return (0);
		}
	}
	return (1);
}
static int ft_check_close(const char *ptr)
{
	printf("this is the line quote :%s:\n", ptr);
	char flag;

	flag = 0;
	while (*ptr)
	{
		if (flag == 0 && (*ptr == '\"' || *ptr == '\'') )
		{
			if (!ft_check_close_q(ptr))
			{
				return (1);
			}
			flag = *ptr;
		}
		else if (flag == *ptr)
			flag = 0;
		ptr++;
	}
	return (0);
}

static char *ft_string_handle(char *line, char *modified_line)
{
	int j;
	char flag;
	char *ptr;

	ptr = line;
	flag = 0;
	j = 0;
	while (*ptr)
	{
		if (flag == 0 && (*ptr == '\"' || *ptr == '\''))
		{
			flag = *ptr;
		}
		else if (flag == *ptr)
			flag = 0;
		if (flag == 0 && *ptr == ' ')
			*ptr = '2';
		else if (flag == 0)
		{
			if ((j = ft_special_case(modified_line, j, &ptr)) == -2)
				return (NULL);
		}
		if (flag == 0 && *ptr == '|')
			*ptr = '3';
		modified_line[j++] = *ptr;
		ptr++;
	}
	return (modified_line);
}
// static char *ft_string_handle(char *line, char *modified_line)
// {
// 	int j;
// 	char flag;

// 	flag = 0;
// 	j = 0;
// 	while (*line)
// 	{
// 		if (flag == 0 && (*line == '\"' || *line == '\''))
// 			flag = *line;
// 		else if (flag == *line)
// 			flag = 0;
// 		if (flag == 0 && *line == ' ')
// 			*line = '2';
// 		else if (flag == 0)
// 		{
// 			if ((j = ft_special_case(modified_line, j, &line)) == -2)
// 				return (NULL);
// 		}
// 		if (flag == 0 && *line == '|')
// 			*line = '3';
// 		modified_line[j++] = *line;
// 		line++;
// 	}
// 	return (modified_line);
// }

char *ft_create_string(char *line)
{
	char *new_line;

	new_line = ft_calloc(ft_strlen(line), sizeof(char *));
	new_line = ft_string_handle(line, new_line);
	printf("this is the line :%s:\n", new_line);
	if (ft_check_close(new_line) == 1)
		new_line = NULL;

	return (new_line);
}
