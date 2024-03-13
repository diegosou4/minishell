/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:44:08 by juan-pma          #+#    #+#             */
/*   Updated: 2024/03/13 14:17:04 by marvin           ###   ########.fr       */
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
static int ft_space (char **line)
{
    while(**line == '2')
        (*line)++;
    return (1);
}

static char *ft_string_handle_2(char *line, char *modified_line)
{
	int j;
	char flag_quotes;

	flag_quotes = 0;
	j = 0;
	while (*line)
	{
		if (flag_quotes == 0 && (*line == '\"' || *line == '\''))
			flag_quotes = *line;
		else if (flag_quotes == *line)
			flag_quotes = 0;
		if (flag_quotes == 0 && (*line == '<' || *line == '>'))
		{
			modified_line[j++] = '2';
			while (*line == '<' || *line == '>')
			{
				modified_line[j++] = *line;
				line++;
			}
			ft_space(&line);
			if (*line == '<' ||  *line == '>')
				return NULL;
			modified_line[j++] = '2';
			flag_quotes = *line;
		}
		modified_line[j++] = *line;
		line++;
	}
	modified_line[j] = '\0';
	return (modified_line);
}

static char *ft_string_handle(char *line, char *modified_line)
{
	int j;
	char flag;

	flag = 0;
	j = 0;
	while (*line)
	{
		if (flag == 0 && (*line == '\"' || *line == '\''))
			flag = *line;
		else if (flag == *line)
			flag = 0;
		if (flag == 0 && *line == ' ')
			*line = '2';
		if (flag == 0 && *line == '|')
			*line = '3';
		modified_line[j++] = *line;
		line++;
	}
	modified_line[j] = '\0';
	return (modified_line);
}

char *ft_create_string(char *line)
{
	char *new_line;
	char *new_line_2;

	new_line = ft_calloc((ft_strlen(line) * 5), sizeof(char *));
	new_line_2 = ft_calloc((ft_strlen(line) * 5), sizeof(char *));
	ft_string_handle(line, new_line);
	ft_string_handle_2(new_line, new_line_2);
	printf("this is the line 1 :%s:\n", new_line);
	printf("this is the line 2 :%s:\n", new_line_2);
	if (!new_line_2)
	{
		free(new_line_2);
		printf("🚫 in-bash: syntax error near unexpected token `\n");
	}
	else if (ft_check_close(new_line_2) == 1)
	{
		free(new_line);
		free(new_line_2);
		return (NULL);
	}
	free(new_line);
	return (new_line_2);
}
