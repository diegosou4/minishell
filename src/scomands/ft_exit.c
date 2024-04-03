/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:30:40 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/29 16:30:41 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void ft_numberforexit(char *str)
{
    int i;
    
    i = ft_atoi(str);
    if(ft_strlen(str) > 1)
    {
        if(!(str[1] >= '0' && str[1] <= '9'))
        {
            ft_putstr_fd("exit: ", 2);
            ft_putstr_fd(str,2);
            ft_putstr_fd(" numeric argument required\n",2);
            exit(2);
        }
    }
    unsigned char res;
    res = (unsigned char)i;
    exit(res);
}

void free_all_exit(t_cmd *comands,t_env *cpy)
{
    ft_free_env_list(cpy);

    if(comands->path != NULL)
    {
        free(comands->path);
    }
}

void ft_exit(t_cmd *comands, t_env **cpy)
{
    char *str;
    int i;
    int int_len;

    i = 0;
    int_len = len_darray(comands->args);
    if(int_len > 2)
        ft_putstr_fd("exit: too many arguments\n",2);
    else if (int_len == 2)
    {
        str = ft_strdup(comands->args[1]);
        while(str[i] != '\0' )
        {
            if(ft_isdigit(str[i]) != 1)
            {
                ft_putstr_fd("exit: numeric argument required\n",2);
                exit(EXIT_FAILURE);
                return;
            }
        i++;
        }

        ft_numberforexit(str);
    }
    else 
    {
        free_all_exit(comands,(*cpy));
        exit(EXIT_SUCCESS);
    }
}
