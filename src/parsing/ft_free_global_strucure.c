/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_global_strucure.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:12:48 by juan-pma          #+#    #+#             */
/*   Updated: 2024/04/16 11:41:18 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	ft_free_list_tokens(t_word_list **word_list, char **tokens,
		char *new_string, t_bash *bash)
{
	if (bash)
		bash->exit_status = 2;
	if (new_string)
		ft_free_wd_list_char(word_list, new_string);
	else
		ft_free_double_word_list(word_list);
	ft_free_double_pointers(tokens);
}


static void freenull(t_word_desc *ptr)
{
	free(ptr);
	ptr = NULL;
}
static void freewdlst(t_word_list *list)
{
	free(list);
	list = NULL;
}

void	ft_free_t_word_list(t_word_list *word_list)
{
	t_word_list	*temp;

	if (!word_list)
		return ;
	temp = word_list;
	while (temp != NULL)
	{
		word_list = word_list->next;
		if(temp->word->word != NULL)
		{
			free(temp->word->word);
			temp->word->word = NULL;
		}
		if(temp->word != NULL)
			freenull(temp->word);
		if(temp != NULL)
			freewdlst(temp);
		temp = word_list;
	}
	if(word_list != NULL)
		freewdlst(word_list);
}

void	ft_free_double_word_list(t_word_list **word_desc)
{
	int	i;

	if (!word_desc)
		return ;
	i = 0;
	while (word_desc[i] != NULL)
	{
		ft_free_t_word_list(word_desc[i]);
		i++;
	}
	free(word_desc);
	word_desc = NULL;
}

void	ft_free_redir_list(t_redir *redir)
{
	t_redir	*temp;
	while (redir !=  NULL)
	{
		temp = redir;
		if(temp->path != NULL)
		{
			free(temp->path);
			temp->path = NULL;
		}
		redir = redir->next;
		free(temp);
	}
}

void	ft_free_cmd_structure(t_cmd *cmd_structure)
{
	t_cmd	*temp;
	
	close_allfd(cmd_structure);
	end_pipes(cmd_structure);
	if (!cmd_structure)
		return ;
	while (cmd_structure)
	{
		temp = cmd_structure->next;
		if(cmd_structure->path != NULL)
			free(cmd_structure->path);
		if (cmd_structure->args != NULL)
			ft_free_double_pointers(cmd_structure->args);
		if(cmd_structure->redir != NULL)
		{
			ft_free_redir_list(cmd_structure->redir);
			cmd_structure->redir = NULL;
		}
		if(cmd_structure != NULL)
			free(cmd_structure);
		cmd_structure = temp;
	}
}
