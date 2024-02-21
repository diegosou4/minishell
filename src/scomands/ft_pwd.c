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



char *ft_cd(char *newlocal, char *old)
{

    char *backsplash;
    backsplash = ft_strjoin("/",newlocal);
    char *newpwd;
    newpwd = ft_strjoin(old,backsplash);
    int result = chdir(newpwd);
    if(result == 0)
    {
        free(backsplash);
        old = ft_strdup(newpwd);
    }else
    {
        perror("Error ");
        free(backsplash);
        free(newpwd);
        return(NULL);
    }
    return(NULL);
}


   