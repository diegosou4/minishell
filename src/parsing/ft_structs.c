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

t_redir *redirnew(void)
{
    t_redir *redir;

    redir = (t_redir *) ft_calloc(sizeof(t_redir),1);
    if(redir == NULL)
        return NULL;
    redir->pathout = NULL;
    redir->pathin = NULL;
    redir->in = -1;
    redir->out = -1;
    redir->token = 0;
    redir->next = NULL;
    return(redir);
}


/*
t_redir *addredirnew(int flag)
{
    t_redir *redir;
    redir = redirnew();
    if(flag == 2 | flag == 4)
        redir->append = 1;
    if(flag == 3 | flag == 4)
        redir->out = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if(flag == 5)
    {
        redir->in;
        redir->out;
    }
}*/
char *findpath(char **args, int flag, int location)
{
    char *path;
    path = NULL;
    if(flag == 1 | flag == 3)
    {
        path = ft_strdup(args[location + 1]);
    }
    return(path);

}
/*
void add_redir(t_cmd **commands)
{
    t_cmd *ptr;
    ptr = (*commands);
    int i;
    int flag;
    char *path;
    while(ptr != NULL)
    {
        i = 0;
        while(ptr->args[i] != NULL)
        {
            flag = flag_redir(ptr->args[i]);
            if(flag != 0)
            {
               path = findpath(ptr->args,flag,i);
               printf("Path--->%s\n",path); 
            }
            i++;
        }
        ptr = ptr->next;
    }
} */














/*
t_redir *redirnew(char *filename,int flag,int append,char *path)
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
    redir->in = -1;
    redir->out = -1;
    redir->append = 0;
    if(flag == 1)
        redir->out = open(ptr,O_CREAT,O_TRUNC, O_WRONLY, 0777);
    else
        redir->in = open(ptr,O_CREAT,O_TRUNC, O_WRONLY, 0777);
    if(append == 1)
        redir->append = 1;
    redir->next = NULL;

    return(redir);
}
*/