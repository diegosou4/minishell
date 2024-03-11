/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:54:14 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/05 11:54:15 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"


int have_out(t_redir *redir)
{
    int have;
    have = 0;
    t_redir *ptr;
    ptr = redir;
    while(ptr != NULL)
    {
        if(ptr->token == 1 | ptr->token == 4)
            have++;
        ptr = ptr->next;
    }
    return(have);
}



