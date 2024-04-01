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



static void erro_cd(char *str, char *erro)
{
    ft_putstr_fd("Error: ", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(erro, 2);
    ft_putstr_fd("\n", 2);
}
int case_cd(char *diretory,t_env **env,int flag)
{
    char *str;
    str = NULL;
//     printf("%s diretorio", diretory);
    
    if(ft_strncmp("..",diretory,2) == 0)
            invert_pwd(env,diretory);
    else
    {
        change_old(env,diretory,(flag - 1));
    }
        
            
    return(EXIT_SUCCESS);


}

int ft_cd(t_cmd *comands,t_env **env)
{
    int result;
    char *erro ;
    int len;
    char *str;
    str = NULL;
    len = len_darray(comands->args);
    if(len > 2)
        return(return_error("cd : too many arguments\n"));
    else if(len == 2)
        str = ft_strdup(comands->args[1]);
    else
        str = get_valuepwd(env,"HOME=");
    result = chdir(str);
    if(result == 0)
    {

     case_cd(str,env,len);
    }
    /*
    erro = strerror(errno);
    erro_cd(comands->args[1],erro);*/
    return(EXIT_FAILURE);
}
 
