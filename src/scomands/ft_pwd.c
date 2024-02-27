
#include "../../includes/mini.h"



char   *ft_getpwd(char **env,char *str)
{
    char *pwd;
    pwd = ft_getenv(env,str,4);
    if(pwd == NULL)
    {
        write(2, "pwd nao encontrado\n",20);
    }
    return(pwd);
}

void print_pwd(char **env,char *str)
{
    char *pwd;

    pwd = ft_getpwd(env,str);
    printf("%s\n",pwd);
}


void execute_pwd(char **env, t_cmd *commands)
{
    int in;
    int out;
    t_redir *ptr;
    in = dup(0);
    out = dup(1);

    ptr = commands->redir;
    openredir(ptr);
    if(ptr != NULL)
    {
    while(ptr->next != NULL)
    {
        if(ptr->token == 2)
        {
            if(in != 0)
                close(in);
            else
                in = dup(ptr->fd);
        }else if(ptr->token == 1)
        {
            if(out != 1)
                close(out);
            else    
                out = dup(ptr->fd);
        }
           ptr = ptr->next;
    }
    }
    print_pwd(env,"PWD");
}