/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:09:42 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/16 16:23:00 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	print_exp(char *key, char *value, int token)
{
	char	*str;

	if (token == 3)
	{
		printf("declare -x ");
		str = ft_substr(key, 0, (ft_strlen(key) - 1));
		printf("%s\n", str);
		free(str);
		return ;
	}
	printf("declare -x ");
	printf("%s", key);
	printf("\"");
	if (value != NULL)
		printf("%s", value);
	printf("\"");
	printf("\n");
}

int	ft_exp(t_env *env)
{
	t_env	*ptr;

	if (env == NULL)
	{
		ft_putstr_fd("Error env is empty\n", 2);
		return (EXIT_FAILURE);
	}
	ptr = env;
	while (ptr != NULL)
	{
		if (ptr->token == 1)
		{
			print_exp(ptr->key, ptr->value, ptr->token);
		}
		ptr = ptr->next;
	}
	ptr = env;
	while (ptr != NULL)
	{
		if (ptr->token == 3 || ptr->token == 2)
			print_exp(ptr->key, ptr->value, ptr->token);
		ptr = ptr->next;
	}
	return (EXIT_SUCCESS);
}
