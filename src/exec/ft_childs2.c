/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childs2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:43:09 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/03 13:43:11 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"


void care_redirect(t_cmd **cmd,t_bash **bash_boss)
{
    (*bash_boss)->fdout = return_out((*cmd));
    (*bash_boss)->fdin = return_in((*cmd));
    if((*cmd)->executable == 0)
    {
        printf("Preciso da free");
        exit(EXIT_FAILURE);
    }
}

void care_expand(t_cmd **cmd,t_bash **bash_boss)
{
    if(expand_path_cpy(cmd,(*bash_boss)->cpyenv) == 1)
    {
        fail_expander((*bash_boss),(*cmd));
        g_exit_status = EXIT_FAILURE;
        exit(EXIT_FAILURE);
    }
}

void dup_final(t_bash *bash_boss)
{
    if(bash_boss->fdin != -1)
    {
        dup2(bash_boss->fdin, STDIN_FILENO);
        close(bash_boss->fdin);
    }
    if(bash_boss->fdout != -1)
    {
        dup2(bash_boss->fdout, STDOUT_FILENO);
        close(bash_boss->fdout);
    } 
}