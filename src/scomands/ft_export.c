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

void print_exp(char *key,char *value, int token)
{
    char *str;
   
    if(token == 3)
    {
        printf("declare -x ");
        str = ft_substr(key,0,(ft_strlen(key) - 1));
        printf("%s",str);
        printf("\n");
        free(str);
        return;
    }
    printf("declare -x ");
    printf("%s",key);
    printf("\"");
    if(value != NULL)
        printf("%s",value);
    printf("\"");
    printf("\n");
    

}


int ft_exp(t_env *env)
{
    t_env *ptr;
    if(env ==  NULL)
        return(EXIT_FAILURE);
    ptr = env;
    while(ptr != NULL)
    {
        if(ptr->token == 1)
            print_exp(ptr->key,ptr->value,ptr->token);
        ptr = ptr->next;
    }
    ptr = env;
    while(ptr != NULL)
    {
        if(ptr->token == 3 || ptr->token == 2)
            print_exp(ptr->key,ptr->value,ptr->token);       
        ptr = ptr->next;
    }
    return(EXIT_SUCCESS);
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
        if(ft_strncmp(ptr->key,this, ft_strlen(this)) == 0)
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
    if((arr[0] == 95 && backslash == 1) || (ft_isalpha(arr[0]) == 0))
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
    i = 1;
    int exit;
    if(len_darray(commands->args) == 1)
        return(ft_exp((*env)));
    while(commands->args[i] != NULL)
    {
        if(check_var(commands->args[i]) == 0)
            exit = EXIT_FAILURE;
        else if(ft_strncmp("_=",commands->args[i],2) == 0)
            exit = EXIT_SUCCESS;
        else
            exit = export_env(env,commands->args[i]);
        i++;
    }
    return(exit);
}
