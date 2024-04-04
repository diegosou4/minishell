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
    int int_len;

    t_bash *bash_boss;


    ft_putstr_fd(ANSI_COLOR_GREEN"exit, see you 😉\n"ANSI_COLOR_RESET, 2);
    bash_boss = (get_file_num()->bash);
    ft_free_exit_status(bash_boss->line, bash_boss->cpyenv, bash_boss->env);
    ft_free_double_word_list(get_file_num()->list);
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
        exit(EXIT_SUCCESS);
}
