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
    if(flag == 1)
    {
        if(redir->pathin  != NULL)
            free(redir->pathin);
        redir->pathin = ft_strdup(file);
    }
    if(flag == 2 || flag == 4)
    {
        if(redir->pathout  != NULL)
            free(redir->pathout);
        redir->pathout = ft_strdup(file);
    }

}

void checkinoutredir(t_redir *redir, char *file, int flag)
{
    if(flag == 1)
    {
        if(redir->out >= 3)
            close(redir->out);
        redir->out = open(file, O_WRONLY | O_CREAT | O_TRUNC);
    }
    if(flag == 2)
    {
       if(redir->in >= 3)
            close(redir->in);
        redir->in = open(file, O_RDONLY);;
    }
    if(flag == 5)
    {
        if(redir->out >= 3)
            close(redir->out);
        redir->out = open(file, O_WRONLY | O_CREAT | O_APPEND);
    }
}
