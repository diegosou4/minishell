


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

void set_pipes(t_cmd *ptrcmd)
{
    if(ptrcmd->next != NULL)
        pipe(ptrcmd->pipes);
}


void care_myprev(t_cmd *ptrcmd)
{
    if (ptrcmd->prev)
    {
        close(ptrcmd->prev->pipes[0]);
        close(ptrcmd->prev->pipes[1]);
    }
}

void care_inchild(t_cmd *current, t_bash *bash_boss)
{
    if(!current->prev)
    {
        close(current->pipes[0]);
        bash_boss->fdin = -1;
        bash_boss->fdout = current->pipes[1];
        return;
    }
    close(current->prev->pipes[1]);
    if (current->next)
    {
        close(current->pipes[0]);
        bash_boss->fdout = current->pipes[1];
    }
    bash_boss->fdin = current->prev->pipes[0];
}