#include "../../includes/mini.h"

t_line *ft_init_manager(t_line *line)
{
    line->line = NULL;
    line->color_line = NULL;
    line->usr = NULL;
    line->line_text = NULL;
    
    return line;
}

// t_word_lists	*ft_init_word_list(char *token)
// {
// 	t_word_lists *word_lists;

// 	word_lists = ft_calloc(1, sizeof(t_word_lists));
// 	word_lists->current_token = NULL;
// 	word_lists->node = NULL;
// 	word_lists->head = NULL;
// 	word_lists->subtoken = ft_strtok(token, "2");
// 	return (word_lists);
// }