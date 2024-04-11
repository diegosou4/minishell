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


static int  shel_exist(char **env)
{
    int i;
    int j;
    i = 0;
    char *str;
    char *value;

	while (env[i] != NULL)
	{
		if(ft_strncmp(env[i],"SHLVL=",6) == 0)
        {
            j = ft_atoi(env[i] + 6);
            str = ft_strdup("SHLVL=");
            value = ft_itoa(j + 1);
            free(env[i]);
            env[i] = ft_strjoin(str,value);
            free(value);
            free(str);
            return(1);
        }
        i++;
	}
	return(0);
}
char **ft_newlvl(char **env, char *newlvl)
{   
    char **new;
    int i;
    int j;
    j = 0;
    i = len_darray(env);
    new = ft_calloc(sizeof(char *), i + 2); 

    while(j < i)
    {
        new[j] = ft_strdup(env[j]);
        j++;
    }
    if(i > 0)
    {
        new[j - 1] = ft_strdup(newlvl);
        new[j] = ft_strdup(env[j - 1]);
    }
    else
        new[j] = ft_strdup(newlvl);
    return(new);
}
void ft_shlvl(char **env)
{
    char **new;
    
    if(shel_exist(env) == 0)
    {
        new = ft_newlvl(env,"SHLVL=1");
        ft_free_double_pointers(env);
        env = ft_arrcpy(new);
        ft_free_double_pointers(new);
    }
}


char **newenv_child(t_env *env)
{
    int i;
    i = 0;
    int j;
    j = 0;
    t_env *ptr;
    char **new;
    ptr = env;
    while(ptr != NULL)
    {
        if(ptr->token >= 1 && ptr->token <= 2)
        {
            i++;
        }
        ptr = ptr->next;
    }
    new = ft_calloc(sizeof(char *), i + 1);
    ptr = env;
    while(j != i)
    {
        if(ptr->token >= 1 && ptr->token <= 2)
              j++;
        ptr = ptr->next;
    }
    return(new);
}