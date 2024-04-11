/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:08:07 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/10 19:08:09 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

char *removeplus(char *str)
{
    char *newvalue;

    int i;
    i = 0;
    int j;
    j = 0;
    newvalue = ft_calloc(ft_strlen(str), sizeof(char));
    while(str[i] != '\0')
    {
        if(str[i] != '+')
        {
            newvalue[j] = str[i];
            j++;
            i++;
        }
        else
            i++;
    }
    return(newvalue);
}

static void plus_key(t_env **ptr,char *value,int token)
{
    char *plus;

    if((*ptr)->value != NULL)
    {
        plus = ft_strjoin((*ptr)->value,value);
        free((*ptr)->value);
    }
    (*ptr)->value = ft_strdup(plus);
    free(plus);
    (*ptr)->token = token;

}
static void update_key(char **newvalue,char **key,char **value)
{
    *key = get_key(*newvalue);
    *value = ft_substr(*newvalue,ft_strlen(*key),ft_strlen(*newvalue));
    free(*newvalue);
}

static int free_andexit(char **key,char **value)
{
    if(*key != NULL)
        free((*key));
    if(*value != NULL)
        free((*value));
    return(EXIT_FAILURE);
}

int case_plus(t_env **env,char *str,int token)
{
    char *newvalue;
    char *key;
    t_env *ptr;
    char *value;

    newvalue = removeplus(str);
    ptr = *env;
    update_key(&newvalue,&key,&value);
    while(ptr != NULL)
    {
        if(ft_strncmp(ptr->key,key,ft_strlen(key)) == 0)
        {
            if(key != NULL)
                free(key);
            if(value == NULL || ft_strlen(value) == 0)
                return(EXIT_SUCCESS);
            plus_key(&ptr,value,token);
            if(value != NULL)
                free(value);
            return(EXIT_SUCCESS);
        }
        ptr = ptr->next;
    }
    return(free_andexit(&key,&value));
}
