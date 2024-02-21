/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:48:25 by diegmore          #+#    #+#             */
/*   Updated: 2023/10/11 17:48:27 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (!*lst || !del || !(*lst))
		return ;
	ft_lstclear(&(*lst)->next, del);
	del((*lst)->content);
	free(*lst);
	*lst = 0;
}

// Verifica se a stuct nao e nula
// verifica se a funcao nao e nula
// verifica se o ponteiro que aponta para lista nao e nulo
// chama a funcao de forma recursiva ate encontrar o null
// depois executa o del e o free de cada um