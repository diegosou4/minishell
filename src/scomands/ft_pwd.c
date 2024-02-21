/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:46:34 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/21 12:46:35 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"

char    *ft_getpwd(char **env,char *str)
{
    char *pwd;
    pwd = ft_getenv(env,str);
    return(pwd);
}



char *ft_ls(char *pwd, char *newlocal)
{
    char *backsplash;
    backsplash = ft_strjoin("/",newlocal);
    char *newpwd;
    newpwd = ft_strjoin(pwd,backsplash);
    if(access(newpwd, F_OK) == 0)
    {
        free(pwd);
        pwd = ft_strdup(newpwd);
    }   
    return(pwd);
}