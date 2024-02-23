#include "../../includes/mini.h"

void ft_init_operations(t_operations *operations)
{
    operations->apppend_out = ">>";
    operations->pipe = "|";
    operations->redir_input = "<";
    operations->redir_output = ">";
    operations->here_doc = "<<";
}