/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:11:00 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/04 23:41:32 by diemorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	change_pwd(t_env **env)
{
	char	*newpwd;
	char	*slash;
	char	*change;
	
	newpwd = ft_calloc(sizeof(char), FILENAME_MAX);
	newpwd = getcwd(newpwd, FILENAME_MAX);
	slash = ft_strjoin(newpwd, "/");
	change = ft_strjoin("PWD=", slash);	
	
	have_key(change,env,1);
	if(newpwd != NULL)
		free(newpwd);
	if(slash != NULL)
		free(slash);
	if(change != NULL)
		free(change);
}

void	change_old(t_env **env)
{
	char	*pwd;
	char	*oldpwd;

	pwd = get_valuepwd(env, "PWD=");
	if (pwd != NULL)
	{
		oldpwd = ft_strjoin("OLDPWD=", pwd);
		have_key(oldpwd,env,1);
		if(oldpwd != NULL)
			free(oldpwd);
	}
	change_pwd(env);
	if (pwd != NULL)
		free(pwd);
}

void	invert_pwd(t_env **env)
{
	char	*pwd;
	char	*keyold;
	
	pwd = NULL;
	keyold = NULL;
	pwd = get_valuepwd(env, "PWD=");
	if (pwd != NULL)
		keyold = ft_strjoin("OLDPWD=", pwd);
	if (keyold != NULL)
		have_key(keyold,env,1);
	change_pwd(env);
	if (pwd != NULL)
		free(pwd);
	if (keyold != NULL)
		free(keyold);
}

char	*get_valuepwd(t_env **env, char *value)
{
	t_env	*ptr;
	char	*key;
	char	*val;

	if (env == NULL)
		return (NULL);
	ptr = (*env);
	key = ft_strdup(value);
	while (ptr != NULL)
	{
		if (ft_strncmp(ptr->key, key, ft_strlen(key)) == 0)
		{
			if (key != NULL)
				free(key);
			val = ft_strdup(ptr->value);
			return (val);
		}
		ptr = ptr->next;
	}
	if (key != NULL)
		free(key);
	return (NULL);
}
