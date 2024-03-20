/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_erros.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:25:50 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/20 15:25:53 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"


int return_error_exec(t_bash *executor)
{
    if(executor->exit_status == EXIT_FAILURE)
    {
        ft_putstr_fd("Error: File error\n",2);
        return(EXIT_FAILURE);
    }
    if(executor->env == NULL)
    {
        ft_putstr_fd("Error: Env not found\n",2);
        return(EXIT_FAILURE);
    }
    return(0);
}