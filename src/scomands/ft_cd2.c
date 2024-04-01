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


void change_pwd(t_env **env, char *str, char *pwd,int flag)
{
    char *newpwd;
    char *slash;
    char *change;
    
    if(pwd != NULL && flag == 1)
    {
        slash = ft_strjoin(pwd,"/");
        newpwd = ft_strjoin(slash,str);
        change = ft_strjoin("PWD=",newpwd);
        export_env(env,change);
        free(change);
        free(slash);
        free(newpwd);
    }
    if(pwd != NULL && flag == 0)
    {   
        change = ft_strjoin("PWD=",str);
        export_env(env,change);
        free(change);
    }
    
}
void change_old(t_env **env,char *str, int flag)
{
    char *pwd;
    char *oldpwd;
    printf("%i flag \n",flag);
   pwd = get_valuepwd(env,"PWD=");
   if(pwd != NULL)
   {
    oldpwd = ft_strjoin("OLDPWD=",pwd);
    export_env(env,oldpwd);
    free(oldpwd);
   }
  
   change_pwd(env,str,pwd,flag);
    if(pwd != NULL)
        free(pwd);
}

void invert_pwd(t_env **env,char *str)
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