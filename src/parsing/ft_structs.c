/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_structs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:47:55 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/19 01:37:31 by marvin           ###   ########.fr       */
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
        if (word_list->word->flags == here_doc || word_list->word->flags == redir_in
                || word_list->word->flags == append_out || word_list->word->flags == redir_out
                ||word_list->word->flags == inandout)
            {
                if (word_list->next)
                    word_list->next->word->tags = PATH;
            }
        word_list = word_list->next;
    }
}

static t_redir *ft_create_node(void)
{
    t_redir *node;

    node = ft_calloc(1, sizeof(t_redir));
    return (node);
}

static void ft_init_redir_node(t_redir *node, char *path, int token)
{
    node->path = (path);
    // free(path);
    node->token = token;
    node->next = NULL;
}
static t_redir *ft_parse_redir_create(t_word_list *token_list)
{
    t_redir *redir;
    t_redir *redir_head;
    t_redir *current_redir;

    redir_head = NULL;
    current_redir = NULL;
    while (token_list)
    {
        if (token_list->word->tags == EXCECUTOR)
        {
            redir = ft_create_node();
            ft_init_redir_node(redir, token_list->next->word->word, token_list->word->flags);
            if (!redir_head)
            {
                redir_head = redir;
                current_redir = redir_head;
            }
            else
            {
                current_redir->next = redir;
                current_redir = current_redir->next;
            }
        }
        token_list = token_list->next;
    }
    return redir_head;
}

t_cmd *ft_parse_array(t_word_list *words_list)
{
    t_cmd *cmd;
    t_redir *redir;
    int args_index;

    cmd = ft_calloc(1, sizeof(t_cmd ));
    cmd->args = (char **)ft_calloc((10), sizeof(char *));
    redir = NULL;
    args_index = 0;
    while (words_list)
    {
        if (words_list->word->tags != EXCECUTOR && words_list->word->tags != PATH)
        {
            cmd->args[args_index++] = (words_list->word->word);
        }
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

t_cmd *ft_structure_creation(t_word_list **token_list)
{
    t_cmd *new_cmd;
    t_cmd *root;
    t_cmd *current_cmd;
    int i;

    new_cmd = NULL;
    if (!token_list)
        return NULL;
    i = -1;
    while (token_list[++i])
    {
        new_cmd = ft_parse_array(token_list[i]);
        if (i == 0)
        {
            root = new_cmd;
            current_cmd = root;
        }
        else
        {
            current_cmd->next = new_cmd;
            current_cmd = current_cmd->next;
        }
    }
    t_cmd *temp = root;
    while (temp)
    {
        ft_print_cmd_struct(temp);
        temp = temp->next;
    }
    return (root);
}
