#include <stdio.h>
#include <stdlib.h>

typedef struct pipe
{
	char *path;
	char		**args;
	int 	here_doc;
	int		fd[2];
	int 	append;
	struct pipe *next;
	
}				t_pipe;