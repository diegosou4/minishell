/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:09:13 by diegmore          #+#    #+#             */
/*   Updated: 2023/10/11 13:09:15 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*diego;

	diego = (t_list *)malloc(sizeof(t_list));
	if (diego == NULL)
		return (NULL);
	diego->content = content;
	diego->next = NULL;
	return (diego);
}

//    Criamos uma lista fazemos a
//     allocao de memoria  verificamos se foi alocado
//    e colocamos o content dentro da nossa estrutura
// e informamos que a proxima vai ser nula
