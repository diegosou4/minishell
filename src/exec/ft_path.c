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


void expand_path(t_cmd **commands,char **env)
{
    int build;
    t_cmd *ptr;
    char *home;
    home = ft_getpath(env);
    printf("home %s",home);
    ptr = (*commands);
    while(ptr != NULL)
    {
        build = check_builtings(ptr);
        if(build != 0)
            ptr->path = ft_strdup(ptr->args[0]);
        else
            ptr->path = ask_acess(ptr->args[0],home); 
        printf("%s cmd \n", ptr->path);
        ptr = ptr->next;
    }

}
