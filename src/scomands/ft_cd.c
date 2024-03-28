/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:20:27 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/08 11:01:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static void change_pwd(t_env **env, char *str, char *pwd)
{
    char *newpwd;
    char *slash;
    char *change;
    
    slash = ft_strjoin(pwd,"/");
    newpwd = ft_strjoin(slash,str);
    change = ft_strjoin("PWD=",newpwd);
    export_env(env,change);
    free(change);
    free(slash);
    free(newpwd);
}
static void change_old(t_env **env,char *str)
{
    char *pwd;
    char *oldpwd;

    pwd = get_valuepwd(env,"PWD=");
    oldpwd = ft_strjoin("OLDPWD=",pwd);
    export_env(env,oldpwd);
    free(oldpwd);
    change_pwd(env,str,pwd);
    free(pwd);
}

static void invert_pwd(t_env **env,char *str)
{
    char *pwd;
    char *oldpwd;
    char *keypwd;
    char *keyold;
    
    pwd = get_valuepwd(env,"PWD=");
    oldpwd = get_valuepwd(env,"OLDPWD=");
    keypwd = ft_strjoin("PWD=",oldpwd);
    keyold = ft_strjoin("OLDPWD=", pwd);

    export_env(env,keypwd);
    export_env(env,keyold);
    free(pwd);
    free(oldpwd);
    free(keyold);
    free(keypwd);
}


static void erro_cd(char *str, char *erro)
{
    ft_putstr_fd("Error: ", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(erro, 2);
    ft_putstr_fd("\n", 2);
}

int ft_cd(t_cmd *comands,t_env **env)
{
    int result;
    char *erro ;
    if(len_darray(comands->args) > 2)
        return(return_error("cd : too many arguments\n"));
    if(comands->args[1] == NULL)
        return(return_error("relative or absuloted path\n"));
    result = chdir(comands->args[1]);
    if(result == 0)
    {
        if(ft_strncmp("..",comands->args[1],2) != 0)
            change_old(env,comands->args[1]);
        else
            invert_pwd(env,comands->args[1]);
        return(EXIT_SUCCESS);
    }
    erro = strerror(errno);
    erro_cd(comands->args[1],erro);
    return(EXIT_FAILURE);
}
 
