/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:13:49 by juan-pma          #+#    #+#             */
/*   Updated: 2024/03/21 14:14:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

t_line *ft_init_manager(t_line *line)
{
    line->line = NULL;
    line->color_line = NULL;
    line->usr = NULL;
    line->line_text = NULL;
    
    return line;
}
