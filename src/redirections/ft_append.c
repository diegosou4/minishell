/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:23:53 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/29 18:23:55 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"


int redirout(char *path)
{
    int fd;
    char *str;
    fd = open(path, O_EXCL | O_WRONLY | O_CREAT, 0644);
    if(fd < 0)
    {
        str = strerror(fd);
        printf("%s \n",str);
        return(fd);
    }
    return(fd);
}

int ft_append(char *path)
{

    int fd;
    fd = open(path, O_APPEND | O_RDWR, 0777);
    if(fd < 0)
        return(fd);
    return(fd);
}