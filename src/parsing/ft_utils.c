/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-pma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:21:34 by juan-pma          #+#    #+#             */
/*   Updated: 2024/02/21 10:49:44 by juan-pma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

t_cmd *cmdnew(char *args)
{
	t_cmd *comands;

	comands = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
	comands->args = ft_split(args,'2');
	comands->next = NULL;
	
	return(comands);
}

void cmdinback(t_cmd **comands,char *args)
{
	t_cmd *ptr;
	t_cmd *last;

	last = cmdnew(args);
	if(last == NULL)
		return;
	ptr = *(comands);
	while(ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	ptr->next = last;

}

static char *ft_strcpy(char *dest, const char *src) {
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return dest;
}

char **ft_doublepointecpy(char **str) {
    if (!str || !str[0]) {
        return NULL;
    }

    int i = 0;
    while (str[i]) {
        i++;
    }

    char **str_copy = (char **)malloc((i + 1) * sizeof(char *));
    if (!str_copy) {
        return NULL;
    }

    int j = 0;
    while (j < i) {
        int len = strlen(str[j]);
        str_copy[j] = (char *)malloc((len + 1) * sizeof(char));
        if (!str_copy[j]) {
            // memory allocation failed, free previously allocated memory
            for (int k = 0; k < j; k++) {
                free(str_copy[k]);
            }
            free(str_copy);
            return NULL;
        }
        ft_strcpy(str_copy[j], str[j]);
        j++;
    }

    // don't forget to terminate the new array with a NULL pointer
    str_copy[i] = NULL;
    return str_copy;
}