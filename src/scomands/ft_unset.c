/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:33:19 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/03 18:59:40 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static int	free_keyandvalue(t_env **ptr, char *key)
{
	free(key);
	if ((*ptr)->key != NULL)
		free((*ptr)->key);
	if ((*ptr)->value != NULL)
		free((*ptr)->value);
	free((*ptr));
	return (EXIT_SUCCESS);
}

static void	unset_value(char **key, char **value, char *str)
{
	(*key) = NULL;
	(*value) = NULL;
	*key = get_key(str);
	if (*key == NULL)
		*key = ft_strdup(str);
	else
		*value = ft_substr(str, ft_strlen(*key), ft_strlen(str));
}

static int	free_keyvalue(char *value, char *key, int exit)
{
	if (key != NULL)
		free(key);
	if (value != NULL)
		free(value);
	return (exit);
}

int	unset_env(t_env **env, char *str, int i, int len)
{
	char	*key;
	char	*value;
	t_env	*ptr;
	t_env	*last;

	last = NULL;
	ptr = *env;
	unset_value(&key, &value, str);
	if (value != NULL)
		return (free_keyvalue(value, key, EXIT_SUCCESS));
	while (ptr != NULL)
	{
		len = (int)ft_strlen(ptr->key) + i;
		if (ft_strncmp(ptr->key, key, len) == 0)
		{
			if (last == NULL)
				*env = (*env)->next;
			else
				last->next = ptr->next;
			return (free_keyandvalue(&ptr, key));
		}
		last = ptr;
		ptr = ptr->next;
	}
	return (free_keyvalue(key, value, EXIT_SUCCESS));
}
