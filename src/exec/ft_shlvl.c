/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:39:00 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/10 11:39:03 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"


static void	change_key(t_env **ptr, int token)
{
    int shelvl;
    char *newvalue;

    shelvl = 0;
	if ((*ptr)->value != NULL)
	{
        shelvl = ft_atoi((*ptr)->value);
        shelvl += 1;
        free((*ptr)->value);
    }
    else
        shelvl = 1;
    
    newvalue = ft_itoa(shelvl);
    (*ptr)->value = ft_strdup(newvalue);
    free(newvalue);    
	(*ptr)->token = token;
}

static int  shel_exist(t_env **env)
{
	t_env	*ptr;
    int i;
    i = 0;
    
	ptr = *env;
	while (ptr != NULL)
	{
		if (ft_strncmp(ptr->key, "SHLVL", 5) == 0)
		{
			change_key(&ptr, 1);
			return (EXIT_SUCCESS);
		}
		ptr = ptr->next;
	}
	return(EXIT_FAILURE);
}
void ft_shlvl(t_env **env)
{
    if(shel_exist(env) == 1)
    {
        addbackenv("SHLVL=1",env,1);
    }

}