/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:08:07 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/10 19:08:09 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static int keyedit(t_env **env,char *str, int token)
{

    t_env *ptr;
    ptr = *env;
    
    while(ptr != NULL)
    {
        // if(ft_strncmp(ptr->key,))
        printf("ptr->key %s",ptr->key);
        printf("value %s\n",str);

        ptr = ptr->next;
    }
    return(1);

}

int case_plus(t_env **env,char *str,int token)
{
    int i;
    i = 0;
    while(str[i] != '\0')
    {
        if(str[i] == 43)
            break;
        i++;
    }
    if(i == (ft_strlen(str) - 1))
        return(1);
    printf("chega aqui\n");
  //  keyedit(env,str,token);
    return(0);

}