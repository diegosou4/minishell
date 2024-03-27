/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:33:19 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/28 14:33:20 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"

int unset_env(t_env **env,char *str)
{
    int i;
    char *key;
    char *value;
    t_env *ptr;
    t_env *last;
    ptr = (*env);
    i = ft_boolstrchr(str,61);
    if(i == 1)
        key = get_key(str);
    printf(" DENTRO DA HILUXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
    while(ptr != NULL)
    {
        last = ptr;
        if(ft_strncmp(ptr->key,key,ft_strlen(ptr->key)) == 0)
        {
            last->next = ptr->next;
            if(ptr->key != NULL)
                free(ptr->key);
            if(ptr->value != NULL)
                free(ptr->value);
            free(ptr);
            return(EXIT_SUCCESS);
        }
        ptr = ptr->next;
    }
    return(1);
}

int ft_unset(t_env **env,t_cmd *commands)
{
    int exit;
    int i;
    i = 1;
    if(*env == NULL)
        return(EXIT_FAILURE);
    if(len_darray(commands->args) == 1)
        return(EXIT_SUCCESS);
    while(commands->args[i] != NULL)
    {
        if(ft_strncmp("_=",commands->args[i],2) == 0)
            exit = (EXIT_SUCCESS);
        else 
            exit = unset_env(env,commands->args[i]);
        i++;
    }

  

    return(exit);
}
