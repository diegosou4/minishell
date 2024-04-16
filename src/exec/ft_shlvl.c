/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:39:00 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/16 11:03:47 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static int	shel_exist(char **env)
{
	int		i;
	int		j;
	char	*str;
	char	*value;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			j = ft_atoi(env[i] + 6);
			str = ft_strdup("SHLVL=");
			value = ft_itoa(j + 1);
			free(env[i]);
			env[i] = ft_strjoin(str, value);
			free(value);
			free(str);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**ft_newlvl(char **env, char *newlvl)
{
	char	**new;
	int		i;
	int		j;

	j = 0;
	i = len_darray(env);
	new = ft_calloc(sizeof(char *), i + 2);
	while (j < i)
	{
		new[j] = ft_strdup(env[j]);
		j++;
	}
	if (i > 0)
	{
		new[j - 1] = ft_strdup(newlvl);
		new[j] = ft_strdup(env[j - 1]);
	}
	else
		new[j] = ft_strdup(newlvl);
	return (new);
}

static int	ft_lenenv(t_env *env)
{
	t_env	*ptr;
	int		i;

	i = 0;
	ptr = env;
	if (ptr == NULL)
		return (0);
	while (ptr != NULL)
	{
		if (ptr->token >= 1 && ptr->token <= 2)
			i++;
		ptr = ptr->next;
	}
	return (i);
}

void	ft_shlvl(char **env)
{
	char	**new;

	if (shel_exist(env) == 0)
	{
		new = ft_newlvl(env, "SHLVL=1");
		ft_free_double_pointers(env);
		env = ft_arrcpy(new);
		ft_free_double_pointers(new);
	}
}

char	**newenv_child(t_env *env)
{
	int		i;
	int		j;
	t_env	*ptr;
	char	**new;

	i = 0;
	j = 0;
	i = ft_lenenv(env);
	new = ft_calloc(sizeof(char *), i + 1);
	if (!new)
		return (ft_calloc(sizeof(char *), 1));
	ptr = env;
	while (j != i)
	{
		if (ptr->token >= 1 && ptr->token <= 2)
		{
			new[j] = ft_strjoin(ptr->key, ptr->value);
			j++;
		}
		ptr = ptr->next;
	}
	return (new);
}
