/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_caseredir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:24:25 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/24 12:24:26 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"


void checkpathredir(t_redir *redir, char *file, int flag)
{
    redir->token = flag;
    if(flag == 1)
    {
        redir->pathin = ft_strdup(file);
    }
    if(flag == 2 || flag == 4)
    {
        redir->pathout = ft_strdup(file);
    }

}
