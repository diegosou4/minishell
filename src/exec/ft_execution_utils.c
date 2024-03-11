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
    if(index == -1)
        return;
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



    executor_without(ptrcmd,env,ptrin->fd,ptrout->fd,cpy);
    close(ptrin->fd);
    close(ptrout->fd);

}



void sfirst_executor(t_cmd **cmd,char **env,t_env **cpy)
{
    int index[2];
    t_redir *ptr[2];

    ptr[0] = (*cmd)->redir;
    ptr[1] = (*cmd)->redir;
    index[0] = check_redir(ptr[0],2); // checkin
    index[1] = check_redir(ptr[1],1); // checkout
    givefd_redir(&ptr[0],index[0]);
    givefd_redir(&ptr[1],index[1]);
    if(index[0] != -1 && index[1] != -1)     
        executor_without((*cmd),env,ptr[0]->fd,ptr[1]->fd,cpy);
    else if(index[0] != -1 && index[1] == -1)
        executor_without((*cmd),env,ptr[0]->fd,1,cpy);
    else if(index[0] == -1 && index[1] != -1)
        executor_without((*cmd),env,0,ptr[1]->fd,cpy);
    else if(index[0] == -1 && index[1] == -1)
        executor_without((cmd),env,0,1,cpy);
}

