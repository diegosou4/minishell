/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:02:50 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/11 13:02:51 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void givefd_redir(t_redir **redir, int index)
{
    while(index > 0)
    {   
        (*redir) = (*redir)->next;
        index--;
    }

}




void executor_redir(t_cmd **cmd,char **env,t_env **cpy)
{
    int indexin;
    int indexout;
    t_redir *ptr;
    t_redir *ptrin;
    t_redir *ptrout;
    t_cmd *ptrcmd;

    ptr = (*cmd)->redir;
    ptrcmd = (*cmd);
    indexin = check_redir(ptr,2);
    indexout = check_redir(ptr,1);
    ptrout = (*cmd)->redir;
    ptrin = (*cmd)->redir;
    givefd_redir(&ptrin,indexin);
    givefd_redir(&ptrout,indexout);


    executor_without(ptrcmd,env,ptrin->fd,ptrout->fd,cpy);
    close(ptrin->fd);
    close(ptrout->fd);

}