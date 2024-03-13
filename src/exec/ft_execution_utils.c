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














