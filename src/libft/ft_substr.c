/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:29:10 by diegmore          #+#    #+#             */
/*   Updated: 2023/10/11 18:51:43 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	len_s;
	char	*subs;
	char	*subre;

	if (!s)
		return (NULL);
	len_s = ft_strlen((char *)s);
	i = 0;
	subs = (char *)ft_calloc((len + 1), sizeof(char));
	if (!subs)
		return (NULL);
	while (i < len && start < len_s)
	{
		subs[i] = s[start];
		i++;
		start++;
	}
	subs[i] = '\0';
	subre = ft_strdup(subs);
	free(subs);
	return (subre);
}

/*
    A funcao substr retorna uma nova string, ela copia a s no indice do start
    voce precisa verifica se o malloc foi feito e se a s tem algo ou nao
    voce precisa o tamanho do s para proteger quando for fazer a copia 
    The fuction substr return a new string it`s copy from the start (index)
    you need verify if malloc is done and if the s have character
    you need len of s, for protect your copy.
*/
