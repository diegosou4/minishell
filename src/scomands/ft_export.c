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

void ft_exp(t_env *env)
{

    t_env *ptr;

    ptr = env;
    if(env ==  NULL)
        return;
    while(ptr != NULL)
    {
        printf("declare -x ");
        printf("%s%s\n",ptr->key,ptr->value);
        ptr = ptr->next;
    }
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
    int j;
    char *newstr;
    t_env *ptr;
    ptr = env;
    char *s;
    s = ft_strchr(str,61);
    if(ft_strlen(s) == 1)
        return(1);
    if(env == NULL)
        return(0);
    i = ft_strintchr(str,61);
    newstr = ft_substr(str,0,i);
    j = ft_indexinenv(env,newstr);
    if(j != -1)
    {
        while(j != 0)
        {
            ptr = ptr->next;
            j--;
        }
        ptr->value = s;
        return(1);
    }
    return(0);
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

void ft_caseequal(t_env **env,char *command)
{
    if(ft_haveinenv(*env,command) == 1)
        return;
    else if(*env == NULL)
        *env = newsenv(command,0,1); 
    else
        ft_putinlast(env,command,1);   
}

void ft_casewithout(t_env **env,char *command)
{
     int j;

    j = ft_indexinenv(*env,command);
    if(j != -1)
        return;
    if(*env == NULL)
        *env = newsenv(command,0,2);
    else
        ft_putinlast(env,command,2);
}


void ft_export(t_env **env,t_cmd *commands)
{
    if(len_darray(commands->args) == 1)
    {
        ft_exp(*env);
        return;
    }
    int index;
    index = ft_strintchr(commands->args[1],61);
    if(ft_strncmp("_=",commands->args[1],2) == 0)
        return;
    if(index > 0 && index != 1)
        return(ft_caseequal(env,commands->args[1]));
    else
        return(ft_casewithout(env,commands->args[1]));
}
