/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:24:04 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/11 13:24:06 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"


int check_redir(t_redir *redir, int flagtoken)
{
    int index;
    int lastIndex = -1; 
    index = 0;
    t_redir *ptr;
    ptr = redir;
    while(ptr != NULL)
    {
        if(flagtoken == 1)
        {
            if(ptr->token == redir_out || ptr->token == append_out 
            || ptr->token == inandout)
                lastIndex = index;
        }
        if(flagtoken == 2)
        {
            if(ptr->token == redir_in || ptr->token == inandout)
                lastIndex = index;
        }
        ptr = ptr->next;
        index++;
    }
    return lastIndex;
}


int check_all(t_redir *redir)
{
    int index;
    index = 0;
    t_redir *ptr;
    ptr = redir;
    while(ptr != NULL)
    {
        if(ptr->token == redir_out || ptr->token == redir_in 
            || ptr->token == append_out || ptr->token == inandout)
            index++;
        ptr = ptr->next;
    }
    return(index);
}



