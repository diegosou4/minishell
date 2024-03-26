/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:22:43 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/27 19:22:44 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"
/*
t_env *find_min_key(t_env *env, char *key)
{
    t_env *min;
    t_env current;
    min = NULL;
    current = env;

    while(current != NULL)
    {
        if(ft_strncmp(current->key,key))

    }


}


void print_sorted(t_env *env)
{
    int index;
    index = len_env(env);
    int i;
    i = 0;
    while(i != index)
    {



    }


}*/

int ft_exp(t_env *env)
{
    t_env *ptr;

    ptr = env;

    
    if(env ==  NULL)
        return(0);
    while(ptr != NULL)
    {
        printf("declare -x ");
        printf("%s%s\n",ptr->key,ptr->value);
        ptr = ptr->next;
    }
    return(1);
}


int ft_indexinenv(t_env *env,char *this)
{
    int index;
    index = 0;
    t_env *ptr;
    ptr = env;
    
    if(env == NULL)
        return(-1);
    while(ptr != NULL)
    {
        if(strncmp(ptr->key,this, ft_strlen(this)) == 0)
            return(index);
        ptr = ptr->next;
        index++;
    }
    return(-1);
}

int ft_haveinenv(t_env *env, char *str)
{
    int i;
    char *newstr;
    t_env *ptr;
    char *s;

    ptr = env;
    s = ft_strchr(str,61);
    if(ft_strlen(s) == 1)
        return(2);
    if(env == NULL)
        return(2);
    i = ft_strintchr(str,61);
    newstr = ft_substr(str,0,i);
    i = ft_indexinenv(env,newstr);
    if(i != -1)
    {
        while(i-- != 0)
            ptr = ptr->next;
        ptr->value = s;
        return(0);
    }
    return(2);
}

void ft_putinlast(t_env **env,char *this,int token)
{
    int i;
    t_env *ptr;
    t_env *last;
    t_env *pen ;
  
    ptr = (*env);
    while(ptr->next != NULL)
    {
        pen = ptr;
        ptr = ptr->next;
    }
    i = ptr->index;
    if(token == 1)
        last = newsenv(this,i,token);
    else
        last = newexp(this,i,token);
    if(pen != NULL)
    {
        pen->next = last;
        last->next = ptr;
    }
    ptr->index += 1;
    update_index(env);  
}

int ft_caseequal(t_env **env,char *command)
{
    if(ft_haveinenv(*env,command) == 0)
        return(0);
    else if(*env == NULL)
        *env = newsenv(command,0,1); 
    else
        ft_putinlast(env,command,1);
    return(0);   
}

int ft_casewithout(t_env **env,char *command)
{
    if(*env == NULL)
        *env = newsenv(command,0,2);
    else
        ft_putinlast(env,command,2);
    return(0);
}*/


int ft_export(t_env **env,t_cmd *commands)
{
    int index;

    if(len_darray(commands->args) == 1)
    {

    }
}
