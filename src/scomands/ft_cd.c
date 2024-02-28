/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:20:27 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/27 16:20:28 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void changepwd_andold(char **env,char *str)
{
    char *old_path;
    char *new_path;
    char *envold;
    envold = ft_getenv(env,"PWD",4);
    old_path = ft_strjoin("OLDPWD=",envold);
    have_inenv(env,old_path);
    if(str[0] == '/')
    { 
        new_path = ft_strjoin("PWD=",str);
        have_inenv(env,new_path);
    }else
    {
        new_path = ft_strstrjoin("PWD=",envold,'/',str);
        have_inenv(env,new_path);
    }

}



int ft_cd(char ***env,t_cmd *comands)
{
    char *str;
    int i;
    int result;
    i = 0;
    if(len_darray(comands->args) > 2)
    {
        write(2, "cd: too many arguments\n",43);
        return(4);
    }
    result = chdir(comands->args[1]);
    if(result == 0)
    { 
       changepwd_andold(*env,comands->args[1]);
        return(1);
        
    }else
    {
        perror("Error ");
    }
    return(3);
}   
