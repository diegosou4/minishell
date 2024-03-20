/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:01:12 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/19 16:01:13 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"

void error_path(char *str)
{
    ft_putstr_fd(str,2);
    ft_putstr_fd(": command not found\n",2);
}


void expand_path(t_cmd **commands,char **env)
{
    int build;
    t_cmd *ptr;
    char *home;
    home = ft_getpath(env);
    ptr = (*commands);
    while(ptr != NULL)
    {
        build = check_builtings(ptr);
        if(build != 0)
            ptr->path = ft_strdup(ptr->args[0]);
        else
            ptr->path = ask_acess(ptr->args[0],home); 
        if(ptr->path == NULL)
        {
            error_path(ptr->args[0]);
            ptr->executable = -1;
        }
        ptr = ptr->next;
    }

}
