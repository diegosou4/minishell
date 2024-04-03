#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>


int main(int ac,char **av, char **env)
{
    int pid;

    pid = fork();

    if(pid == 0)
    {
        char *agv[] = {NULL};
        char **envp = NULL;
        execve("/home/diegmore/Desktop/git/minishell/minishell",agv,envp);



    }
    wait(NULL);
    return(0);

}