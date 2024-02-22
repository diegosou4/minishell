/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_structs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:47:55 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/22 11:47:58 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"

t_redir *redirnew(char *filename,int flag,char *path)
{
    t_redir *redir;
    redir = (t_redir *)ft_calloc(sizeof(t_redir),1);
    char *ptr;

    ptr = ft_strjoin(path,filename);
    if (redir == NULL) {
        return NULL;
    }
    redir->str = ft_strdup(filename);
    if (redir->str == NULL) {
        free(redir);
        return NULL;
    }
    if(flag == 1)
    {
        redir->out = open(ptr,O_CREAT,O_TRUNC, O_WRONLY, 0777);
        redir->in = -1;
    }else
    {
        redir->out = -1;
        redir->in = open(ptr,O_CREAT,O_TRUNC, O_WRONLY, 0777);
    }
    redir->next = NULL;

    return(redir);
}

void changeredir(char *filename,t_redir *redir,char *path)
{
    char *ptr;
    ptr = ft_strjoin(path,filename);
    free(redir->str);
    close(redir->out);
    redir->str = ft_strdup(ptr);
    redir->out = open(ptr, O_CREAT,O_TRUNC,O_WRONLY,0777);
    printf("%s \n",ptr);
    close(redir->out);
}

void checkredir(t_cmd **commands)
{
    t_cmd *ptr;
    int i;
    ptr = (*commands);

    while(ptr != NULL)
    {
        i = 0;
        while(ptr->args[i] != NULL)
        {
            if(ft_strcmp(ptr->args[i],">") == 0)
            {
                if(ptr->redir == NULL)
                    ptr->redir = redirnew(ptr->args[i + 1],1,"/home/diegmore/Desktop/git/minishell/");
                else
                    changeredir(ptr->args[i + 1],ptr->redir,"/home/diegmore/Desktop/git/minishell/");
            }
            i++;
        }
        ptr = ptr->next;
    }
    
}