/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_structs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:47:55 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/21 17:16:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

t_redir	*redirnew(void)
{
	t_redir	*redir;

	redir = (t_redir *) ft_calloc(sizeof(t_redir), 1);
	if (redir == NULL)
		return (NULL);
	redir->path = NULL;
	redir->fd = -1;
	redir->token = 0;
	redir->next = NULL;
	return (redir);
}

char	*findpath(char **args, int flag, int location)
{
	char	*path;

	path = NULL;
	if (flag == 1 || flag == 3)
	{
		path = ft_strdup(args[location + 1]);
	}
	return (path);
}

void	ft_flags_tags_assignment(t_word_list *word_list)
{
	while (word_list)
	{
		if (ft_strcmp(word_list->word->word, "<<") == 0 && word_list->next)
		{
			if (word_list->next->word->tags == VARIABLE)
				word_list->next->word->tags = WORD;
		}
		if (word_list->word->flags == here_doc
			|| word_list->word->flags == redir_in
			|| word_list->word->flags == append_out
			|| word_list->word->flags == redir_out
			||word_list->word->flags == inandout)
		{
			if (word_list->next)
				word_list->next->word->tags = PATH;
		}
		word_list = word_list->next;
	}
}

t_redir	*ft_create_node(void)
{
	t_redir	*node;

	node = ft_calloc(1, sizeof(t_redir));
	return (node);
}

void	ft_init_redir_node(t_redir *node, char *path, int token)
{
	node->path = (path);
	node->fd = -1;
	node->token = token;
	node->next = NULL;
}
