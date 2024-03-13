/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_structs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:47:55 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/13 17:11:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"

t_redir *redirnew(void)
{
    t_redir *redir;

    redir = (t_redir *) ft_calloc(sizeof(t_redir),1);
    if(redir == NULL)
        return NULL;
    redir->path = NULL;
    redir->fd = -1;
    redir->token = 0;
    redir->next = NULL;
    return(redir);
}

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


void ft_flags_tags_assignment(t_word_list *word_list)
{
    while (word_list)
    {
		if (ft_strcmp(word_list->word->word, "<<") == 0 && word_list->next)
        {
            if (word_list->next->word->tags == VARIABLE)
			    word_list->next->word->tags = WORD;
        }
        if (word_list->word->tags == here_doc || word_list->word->tags == redir_in
                || word_list->word->tags == append_out || word_list->word->tags == redir_out
                ||word_list->word->tags == inandout)
            {
                if (word_list->next)
                    word_list->next->word->tags = PATH;
            }
        word_list = word_list->next;
    }
}

static void ft_free_redir_list(t_redir *redir) {
    while (redir) {
        t_redir *next = redir->next;
        free(redir->path); // Free the path string
        free(redir); // Free the redirection struct
        redir = next;
    }
}

static t_redir *ft_parse_redir_create(t_word_list *token_list)
{
    t_redir *redir;
    t_redir *current_redir;

    redir = NULL;
    current_redir = NULL;

    while (token_list)
    {
        if (token_list->word->tags == EXCECUTOR)
        {
            if (!redir)
            {
                redir = ft_calloc(10, sizeof(t_redir));
                current_redir = redir;
            }
            else
            {
                current_redir->next = ft_calloc(1, sizeof(t_redir));
                if (!current_redir->next)
                {
                    ft_free_redir_list(redir);
                    return NULL;
                }
                current_redir = current_redir->next;
            }
            current_redir->path = (token_list->next->word->word);
            current_redir->token = token_list->word->flags;
            current_redir->next = NULL;
        }
        token_list = token_list->next;
    }
    return redir;
}

t_cmd *ft_parse_array(t_word_list *words_list)
{
    t_cmd *cmd;
    t_redir *redir;
    int args_index;

    cmd = ft_calloc(10, sizeof(t_cmd ));
    cmd->args = (char **)ft_calloc((100), sizeof(char *));
    redir = NULL;
    args_index = 0;

    while (words_list)
    {
        if (words_list->word->tags != EXCECUTOR)
            cmd->args[args_index++] = (words_list->word->word);
        if (!redir)
        {
            redir = ft_parse_redir_create(words_list);
            cmd->redir = redir;
        }
        words_list = words_list->next;
    }
    cmd->args[args_index] = NULL;
    return cmd;
}

void *ft_structure_creation(char *line, t_env *env)
{
    t_word_list **token_list;
    t_cmd *root;
    t_cmd *current_cmd;
    int i;

    token_list = ft_tokenizer_manager(line,env);
    if (!token_list)
        return NULL;
    i = -1;
    while (token_list[++i])
    {
		ft_quotes_remove(token_list[i]);
        if (i == 0)
        {
            root = ft_parse_array(token_list[i]);
            current_cmd = root;
        }
        else
        {
            current_cmd->next = ft_parse_array(token_list[i]);
            current_cmd = current_cmd->next;
        }
        ft_print_list_struct(token_list[i], i);
    }

    while (root)
    {
    ft_print_cmd_struct(root);
        root = root->next;
    }
}

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