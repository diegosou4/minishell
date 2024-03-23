


#include "../../includes/mini.h"

int sizepipe(t_cmd *commands)
{
    int i;
    i = 0;

    t_cmd *ptr;

    ptr = commands;
    while(ptr != NULL)
    {
        i++;
        ptr = ptr->next;
    }
    return(i);
}

int ft_countpipes(t_cmd *cmd)
{
    int i;
    i = 0;
    t_cmd *ptr;

    ptr = cmd;
    while(ptr != NULL)
    {
        i++;
        ptr = ptr->next;
    }
    return(i);
}


void open_pipes(t_cmd **cmd)
{
    t_cmd *ptr;
    ptr = (*cmd);
    while(ptr != NULL)
    {
        pipe(ptr->pipesfd);
        ptr = ptr->next;
    }
}

void close_pipes(t_cmd **cmd)
{
    t_cmd *ptr;

    ptr = (*cmd);
    while(ptr != NULL)
    {
        close(ptr->pipesfd[0]);
        close(ptr->pipesfd[1]);
        ptr = ptr->next;
    }

}

int have_in(t_cmd *ptrcmd)
{
    t_redir *ptr;
    ptr = ptrcmd->redir;

    while(ptr != NULL)
    {
        if(ptr->token == redir_in)
            return(1);
        ptr = ptr->next;
    }
    return(0);


}

int have_out(t_cmd *ptrcmd)
{
    t_redir *ptr;
    ptr = ptrcmd->redir;

    while(ptr != NULL)
    {
        if(ptr->token == redir_out || ptr->token == append_out)
            return(1);
        ptr = ptr->next;
    }
    return(0);
}
void check_pipe(t_cmd *ptrcmd,t_cmd *lastcmd)
{
    int in;
    int out;
    out = have_out(ptrcmd);
    in = have_in(ptrcmd);
    
}