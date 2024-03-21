/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openfd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:17:43 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/19 11:17:45 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"


int open_redir_fd(t_redir *redir)
{
    t_redir *ptr;
    int flag;
    ptr = redir;
    if(ptr == NULL)
        return(EXIT_SUCCESS);
    flag = open_fd(&ptr);
    if(flag == 0)
    {
        ft_putstr_fd("Error for open file",2);
        return(EXIT_FAILURE);
    }
    return(EXIT_SUCCESS);
}