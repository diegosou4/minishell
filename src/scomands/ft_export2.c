/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:01:17 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/04 23:40:21 by diemorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static void	change_value(char **key, char **value, char *str)
{
	*key = get_key(str);
	if (*key == NULL)
		*key = ft_strdup(str);
	else
		*value = ft_substr(str, ft_strlen(*key), ft_strlen(str));
}

static void	change_key(t_env **ptr, char *value, int token)
{
	if ((*ptr)->value != NULL)
		free((*ptr)->value);
	(*ptr)->value = ft_strdup(value);
	(*ptr)->token = token;
}

int	key_exist(t_env **env, char *str, int token)
{
	char	*key;
	char	*value;
	t_env	*ptr;

	value = NULL;
	ptr = *env;
	change_value(&key, &value, str);
	while (ptr != NULL)
	{
		if (ft_strncmp(ptr->key, key, ft_strlen(key)) == 0)
		{
			if(key != NULL)
				free(key);
			if (ft_boolstrchr(str, 61) == 0 || value == NULL
				|| ft_strlen(value) == 0)
				return (EXIT_SUCCESS);
			change_key(&ptr, value, token);
			if(value != NULL)
				free(value);
			return (EXIT_SUCCESS);
		}
		ptr = ptr->next;
	}
	free(key);
	free(value);
	return (EXIT_FAILURE);
}

void	swap_value(t_env **env)
{
	t_env	*ptr;
	t_env	*last;
	t_env	*pen;

	pen = NULL;
	if (*env == NULL || (*env)->next == NULL)
		return ;
	ptr = *env;
	while (ptr->next != NULL)
	{
		last = pen;
		pen = ptr;
		ptr = ptr->next;
	}
	pen->next = NULL;
	ptr->next = pen;
	last->next = ptr;
}

int	export_env(t_env **env, char *str)
{
	int	token;
	int key;
	
	token = 3;
	if (ft_boolstrchr(str, 61) == 1)
		token = 2;
	key = key_exist(env, str, token);
	if (key == 1)
	{
		addbackenv(str, env, token);
		swap_value(env);
	}
	return (EXIT_SUCCESS);
}
