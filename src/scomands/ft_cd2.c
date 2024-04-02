/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:11:00 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/28 16:11:02 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"


void change_pwd(t_env **env)
{
    char *newpwd;
    char *slash;
    char *change;
    
    newpwd = ft_calloc(sizeof(char), FILENAME_MAX);
    newpwd = getcwd(newpwd,FILENAME_MAX);
    slash = ft_strjoin(newpwd,"/");
    change = ft_strjoin("PWD=",slash);
    export_env(env,change);
    free(newpwd);
    free(slash);
    free(change);
    
}
void change_old(t_env **env,char *str, int flag)
{
    char *pwd;
    char *oldpwd;

   pwd = get_valuepwd(env,"PWD=");
   if(pwd != NULL)
   {
    oldpwd = ft_strjoin("OLDPWD=",pwd);
    export_env(env,oldpwd);
    free(oldpwd);
   }
   change_pwd(env);
    if(pwd != NULL)
        free(pwd);
}

void invert_pwd(t_env **env,char *str)
{
    char *pwd;
    char *keyold;
    pwd = NULL;
    
    pwd = get_valuepwd(env,"PWD=");
    if(pwd != NULL)
        keyold = ft_strjoin("OLDPWD=", pwd);
    if(keyold != NULL)
        export_env(env,keyold);
    change_pwd(env);
    if(pwd != NULL)
        free(pwd);
    if(keyold != NULL)
        free(keyold);
}

char *get_valuepwd(t_env **env, char *value)
{
    t_env *ptr;
    char *key;
    char *val;
    if(env == NULL)
        return(NULL);
    ptr = (*env);
    key  = ft_strdup(value);
    while(ptr != NULL)
    {
        if(ft_strncmp(ptr->key,key,ft_strlen(key)) == 0)
        {   
            if(key != NULL)
                free(key);
            val = ft_strdup(ptr->value);
            return(val);
        }
        ptr = ptr->next;
    }
    if(key != NULL)
        free(key);
    return(NULL);
}