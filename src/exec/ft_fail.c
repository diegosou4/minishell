/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fail.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:30:52 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/25 17:31:03 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void fail_expander(t_bash *bash_boss,t_cmd *cmd)
{
  
    if(bash_boss->fdin != -1)
        close(bash_boss->fdin);
    if(bash_boss->fdout != -1)
        close(bash_boss->fdout);
    if(bash_boss->pipein != -1)
        close(bash_boss->pipein);
    if(bash_boss->pipeout != -1)
        close(bash_boss->pipeout);
    ft_free_cmd_structure(cmd);
    exit(EXIT_FAILURE);

}