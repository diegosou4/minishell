/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dups.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:57:57 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/21 13:57:58 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void reset_fd(t_bash *bash_boss)
{
    dup2(bash_boss->in, 0);
    dup2(bash_boss->out,1);
}

void dup_fd(t_bash *bash_boss)
{
    bash_boss->in = dup(0);
    bash_boss->out = dup(1);
}

void init_dup(int fdin,int fdout)
{
    if(fdin != 0)
        dup2(fdin,0);
    if(fdout != 1)
        dup2(fdout,1);
}

void close_fds(t_bash *bash_boss)
{
    if(bash_boss->fdin != 0)
        close(bash_boss->fdin);
    if(bash_boss->fdout != 1)
        close(bash_boss->fdout);
    bash_boss->fdin = -1;
    bash_boss->fdout = -1;
}

void close_dup(t_bash *bash_boss)
{
    close(bash_boss->in);
    close(bash_boss->out);
}