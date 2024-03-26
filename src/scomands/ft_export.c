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


t_env *insertion_sort(t_env *env) 
{
    t_env *temp;
    t_env *sorted;
    t_env *current;

    if (env == NULL || env->next == NULL)
        return (env); 
    sorted = NULL; 
    while (env != NULL) 
    {
        current = env;
        env = env->next; 
        if (sorted == NULL || ft_strncmp(current->key, sorted->key,ft_strlen(current->key)) <= 0) 
        {
            current->next = sorted;
            sorted = current;
        }else 
        {
            temp = sorted;
            while (temp->next != NULL && ft_strncmp(current->key, temp->next->key,ft_strlen(current->key)) > 0) 
                temp = temp->next;
            current->next = temp->next;
            temp->next = current;
        }
    }
    return(sorted);
}

int ft_exp(t_env *env)
{
    t_env *ptr;

    ptr = insertion_sort(env);
    if(env ==  NULL)
        return(0);
    while(ptr != NULL)
    {
        if(ptr->token == 1)
        {
            printf("declare -x ");
            printf("%s%s\n",ptr->key,ptr->value);
        }
          ptr = ptr->next;
    }
    ptr = env;
    while(ptr != NULL)
    {
        if(ptr->token == 2)
        {
            printf("declare -x ");
            printf("%s%s\n",ptr->key,ptr->value);
        }
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

int check_var(char *arr)
{
    int backslash;
    int i;

    i = 0;
    backslash = 0;
    while(arr[i] != '\0')
    {
        if(arr[i] == 47)
            backslash = 1;
        i++;
    }
    i = 0;
    if(arr[0] == 95 && backslash == 1)
    {
        ft_putstr_fd("export: ",STDERR_FILENO);
        ft_putstr_fd(arr,STDERR_FILENO);
        ft_putstr_fd(" : not a valid identifier",STDERR_FILENO);
        ft_putstr_fd("\n",STDERR_FILENO);
        return(0);
    }
    return(1);
}

int ft_export(t_env **env,t_cmd *commands)
{
    int i;
    i = 0;
    if(len_darray(commands->args) == 1)
        ft_exp((*env));
    while(commands->args[i] != NULL)
    {
        if(check_var(commands->args[i]) == 0)
            return(EXIT_FAILURE);
        else if(ft_strncmp("_=",commands->args[i],2) == 0)
            return(EXIT_SUCCESS);
        else
            export_env(env,commands->args[i]);
        i++;
    }
   
    return(1);
}
