#include "../../includes/mini.h"

void ft_free_double_pointers(char **split_line)
{
    int i;

    i = -1;
    if (split_line == NULL)
        return ;
    while (split_line[++i])
    {
        free(split_line[i]);
        // split_line[i] = NULL;
    }
    free(split_line);
}
void ft_free_env_list(t_env *env)
{
    t_env *current;
    t_env *temp;

    current = env;
    while (current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp->key);
        free(temp);
    }
}

void ft_free_line_struct(t_line *line)
{
    free(line->line_text);
	free(line->color_line);
}

void ft_free_t_word_list(t_word_list *word_list)
{
    t_word_list *temp;

    while (word_list)
    {
        temp = word_list;
        word_list = word_list->next;
        free(temp->word->word);
        free(temp->word);
        free(temp);
    }
    free(word_list);
}
void ft_free_double_word_list(t_word_list **word_desc)
{
    int i;

    i = -1;
    while (word_desc[++i])
    {
        ft_free_t_word_list(word_desc[i]);
    }
    free(word_desc);
}

void ft_free_redir_list(t_redir *redir)
{
    t_redir *temp;

    while (redir)
    {
        temp = redir;
        redir = redir->next;
        // free(temp->path); // Free the path member
        free(temp);
    }
}
void ft_free_cmd_structure(t_cmd *cmd_structure)
{
    t_cmd *temp;

    while (cmd_structure)
    {
        temp = cmd_structure->next;
        // ft_free_double_pointers(cmd_structure->args);
        ft_free_redir_list(cmd_structure->redir);
        free(cmd_structure->path);
        free(cmd_structure);
        cmd_structure = temp;
    }
}

