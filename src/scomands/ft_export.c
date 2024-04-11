/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:22:43 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/02 17:59:09 by marvin           ###   ########.fr       */
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
		printf("%s", str);
		printf("\n");
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
			print_exp(ptr->key, ptr->value, ptr->token);
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

int	ft_indexinenv(t_env *env, char *this)
{
	int		index;
	t_env	*ptr;

	index = 0;
	ptr = env;
	if (env == NULL)
		return (-1);
	if(ft_strlen(this) == 0) 
		return(-1);
	while (ptr != NULL)
	{
		if (ft_strncmp(ptr->key, this, ft_strlen(this)) == 0)
		{
			return (index);
		}
		ptr = ptr->next;
		index++;
	}
	return (-1);
}

int	check_var(char *arr)
{
	int	prohibited;
	int	i;

	i = 0;
	prohibited = 0;
	while (arr[i] != '\0')
	{
		if(arr[i] == '=')
			break;
		if (arr[i] >= 33 && arr[i] <= 47 && arr[i] != 43)
			prohibited = 1;
		i++;
	}
	i = 0;
	if ((prohibited == 1) || (ft_isalpha(arr[0]) == 0))
	{
		export_msg(arr);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int export_with(char *str,t_env **env)
{
	int i;

	i = 0;
	if(check_var(str) == 1)
		return(EXIT_FAILURE);
	if(ft_strncmp("_=", str, 2) == 0)
		return(EXIT_SUCCESS);
	while(str[i] != '\0' && str[i] != '=')	
		i++;
	if(str[i] == '=' && ft_strlen(str) > 1)
	{
		i--;
		if(ft_isalpha(str[i]) == 0)
		{

			export_msg(str);
			return(EXIT_FAILURE);
		}
	}
	if(str[i] == '+')
		case_plus(env,str,2);
	else
		export_env(env,str);
	return(EXIT_SUCCESS);
}

int export_without(char *str,t_env **env)
{
	int	prohibited;
	int	i;

	i = 0;
	prohibited = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 33 && str[i]  <= 47)
			prohibited = 1;
		i++;
	}
	if ((prohibited == 1) || (ft_isalphatwo(str[0]) == 0))
	{
		export_msg(str);
		return (EXIT_FAILURE);
	}
	return(export_env(env,str));
}

int	ft_export(t_env **env, t_cmd *commands)
{
	int	i;
	int	exit;

	i = 1;
	if (len_darray(commands->args) == 1)
		return (ft_exp((*env)));
	while (commands->args[i] != NULL)
	{	
		if(ft_boolstrchr(commands->args[i],61) == 1)
			exit = export_with(commands->args[i],env);
		else
			exit = export_without(commands->args[i],env);
		i++;
	}
	return (g_exit_status = exit);
}
