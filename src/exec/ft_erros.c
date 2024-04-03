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


void printf_error_fd(char *strerror,char *file)
{
    ft_putstr_fd(file,STDERR_FILENO);
    ft_putstr_fd(": ",STDERR_FILENO);
    ft_putstr_fd(strerror,STDERR_FILENO);
    ft_putstr_fd("\n",STDERR_FILENO);
}
