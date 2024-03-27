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
void ft_exit(t_cmd *comands)
{
    char *str;
    int i;
    i = 0;
    printf("exit\n");
    if(len_darray(comands->args) > 2)
        ft_putstr_fd("exit: too many arguments\n",2);
    str = ft_strdup(comands->args[1]);
    while(str[i] != '\0')
    {
        if(ft_isdigit(str[i]) != 1)
        {
            ft_putstr_fd("exit: numeric argument required\n",2);
            return;
        }
    i++;
    }
    ft_numberforexit(str);
}
