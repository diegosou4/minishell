/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_manager_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:55:06 by juan-pma          #+#    #+#             */
/*   Updated: 2024/03/28 08:55:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	ft_lstsize_(t_word_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_word_list	*ft_lstlast_(t_word_list *lst)
{
	int	tamlist;
	int	i;

	i = 0;
	tamlist = ft_lstsize_(lst);
	while (i < tamlist - 1)
	{
		i++;
		lst = lst->next;
	}
	return (lst);
}

int	ft_check_token_size(char *token_line)
{
	int i;

	i = 0;
	while (token_line[i] != '\0' && ((ft_isalnum(token_line[i])
				|| ft_isdigit(token_line[i]) || ft_isalnum(token_line[i])
				|| token_line[i] == '_')))
		i++;
	return (i);
}