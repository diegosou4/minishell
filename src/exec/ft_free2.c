/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:41:46 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/03 15:41:48 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	free_cpyenv(t_env *cpyenv)
{
	t_env	*ptr;
	t_env	*next;

	ptr = cpyenv;
	while (ptr != NULL)
	{
		if (ptr->key != NULL)
			free(ptr->key);
		if (ptr->value != NULL)
			free(ptr->value);
		next = ptr->next;
		free(ptr);
		ptr = next;
	}
}
