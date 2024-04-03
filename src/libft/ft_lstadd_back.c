/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:34:39 by diegmore          #+#    #+#             */
/*   Updated: 2023/10/11 14:34:41 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*l;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	l = *lst;
	while (l->next)
	{
		l = l->next;
	}
	l->next = new;
}

//  Verifico se eles sao nulos
//  verifico se o valor dentro do lst e nulo ou nao
// (*lst) acesso o valor apontado pelo ponteiro duplo
