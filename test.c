#include <unistd.h>
#include <stdio.h>
int main()
{
    char *path = "/bin/ls";
    char *argv[] = {"ls","-l", NULL};
    char *envp[] = {NULL};
    printf("executando\n");
    execve(path, argv, envp);

    return 0;
}