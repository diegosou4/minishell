/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:44:08 by juan-pma          #+#    #+#             */
/*   Updated: 2024/04/15 13:54:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static int	ft_check_close_q(const char *ptr)
{
	if (*ptr == '\'')
	{
		if (!ft_strchr((const char *)(ptr + 1), '\''))
			return (error_syntax("Error Unclosing quotes \' 🔓\n",0));
	}
	else if (*ptr == '\"')
	{
		if (!ft_strchr((const char *)(ptr + 1), '\"'))
			return (error_syntax("Error Unclosing quotes \" 🔓\n",0));
	}
	return (1);
}

static int	ft_check_close(const char *ptr)
{
	char	flag;

	flag = 0;
	while (*ptr)
	{
		if (flag == 0 && (*ptr == '\"' || *ptr == '\''))
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

static char	*ft_string_handle(char *line, char *modified_line)
{
	int		j;
	char	flag;

	flag = 0;
	j = 0;
	while (*line)
	{
		if (flag == 0 && (*line == '\"' || *line == '\''))
			flag = *line;
		else if (flag == *line)
			flag = 0;
		if (flag == 0 && *line == ' ')
			*line = '\2';
		if (flag == 0 && *line == '|')
			*line = '\3';
		modified_line[j++] = *line;
		line++;
	}
	modified_line[j] = '\0';
	return (modified_line);
}
static void ft_free_null(char **ptr, char **line2, t_bash *bash, int num)
{
	if (num == 1)
	{
		free(*ptr);
		free(*line2);
		bash->exit_status = error_syntax("🚫 in-bash: syntax error near unexpected token `\n",2);
	}
	else
	{
		free(line2);
		bash->exit_status =  error_syntax("🚫 in-bash: syntax error near unexpected token `\n",2);
	}
}
char	*ft_create_string(char *line, t_bash *bash)
{
	char	*new_line;
	char	*new_line_2;

	if (!line)
		return (NULL);
	new_line = ft_calloc((ft_strlen(line) * 3), sizeof(char));
	new_line_2 = ft_calloc((ft_strlen(line) * 3), sizeof(char));
	ft_string_handle(line, new_line);
	if (!ft_strcmp(new_line, ">") || !ft_strcmp(new_line, "<"))
	{
		ft_free_null(&new_line, &new_line_2, bash, 1);
		return (NULL);
	}
	ft_string_handle_2(new_line, new_line_2);
	if (!new_line_2)
		ft_free_null(&new_line, &new_line_2, bash, 2);
	else if (ft_check_close(new_line_2) == 1)
	{
		free(new_line_2);
		bash->exit_status = 2;
		new_line_2 = (NULL);
	}
	free(new_line);
	return (new_line_2);
}
