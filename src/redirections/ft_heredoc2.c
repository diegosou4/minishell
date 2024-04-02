/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:14:44 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/02 16:14:45 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"


void check_heredoc(t_redir **redirect)
{
    t_redir *ptr;
    t_redir *fdclose;
    fdclose = (*redirect);
    ptr = (*redirect);

    while(ptr != NULL)
    {
        if(ptr->token == here_doc)
        {
            ptr->fd = case_here(ptr->path,fdclose);
            ptr->token = open_here;
        }
        ptr = ptr->next;
    }
}