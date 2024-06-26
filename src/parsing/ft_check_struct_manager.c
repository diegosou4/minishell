/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_struct_manager.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:33:05 by juan-pma          #+#    #+#             */
/*   Updated: 2024/04/11 09:27:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

char	*ft_create_token(char *token_line)
{
	int		i;
	char	*token;

	i = -1;
	token = ft_calloc(ft_strlen(token_line) + 1, sizeof(char));
	while (++i < ft_check_token_size(token_line))
	{
		token[i] = token_line[i];
	}
	token[i] = '\0';
	return (token);
}

void	ft_check_variable_quotes_expansion(char *dest)
{
	int	i;

	i = -1;
	while (dest[++i])
	{
		if (dest[i] == '$' && dest[i + 1] == '\'')
		{
			ft_memmove(&dest[i], &dest[i + 1], ft_strlen(&dest[i + 1]) + 1);
		}
	}
}

void	ft_num_init(t_number *num)
{
	num->path = NULL;
	num->double_quote = 0;
	num->in_quotes = 0;
	num->pid = ft_itoa(getpid());
	num->exit_status = ft_itoa(get_file_num()->bash->exit_status);
	num->dolar = ft_strdup("$");
}

void	ft_num_free(t_number *num)
{
	free(num->pid);
	free(num->exit_status);
	free(num->dolar);
}

void	ft_check_variable_expansion(char *src, char *dest, t_env *env)
{
	t_number	num;

	ft_num_init(&num);
	while (*src)
	{
		if (*src == '\"' && ft_strchr(src, '$'))
			num.double_quote = !num.double_quote;
		if (ft_check_variable_helper(&dest, &src, &num))
			continue ;
		if (!num.in_quotes && *src == '$' && (*(src + 1) != '\''
				&& *(src + 1) != '\"'))
		{
			ft_variable_help(&num, src + 1, env);
			while (num.path != NULL && *num.path)
				*dest++ = *num.path++;
			src += ft_strlen(num.token) + 1;
			free(num.token);
		}
		else
			*dest++ = *src++;
	}
	ft_num_free(&num);
	*dest = '\0';
}
