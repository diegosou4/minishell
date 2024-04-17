/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:22:20 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/17 16:55:39 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	ft_env(t_env *env)
{
	t_env	*ptr;

	ptr = env;
	if (env == NULL)
		return (1);
	while (ptr != NULL)
	{
		if (ptr->token == 1 || ptr->token == 2)
		{
			if (ft_strlen(ptr->value) > 0)
				printf("%s%s\n", ptr->key, ptr->value);
		}
		ptr = ptr->next;
	}
	return (2);
}

int	execute_env(t_env *env, t_cmd *commands)
{
	int	exit;

	exit = 0;
	if (env == NULL)
		exit = return_error("Error env is empty\n");
	else if (len_darray(commands->args) > 1)
		exit = return_error("Error two or more arguments!!\n");
	else
		exit = ft_env(env);
	return (get_file_num()->exit_code = exit);
}
