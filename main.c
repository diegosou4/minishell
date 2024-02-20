#include "includes/mini.h"

/*
    1. check the access fucntion to get the path
    of te process.

*/

int main(int argc, char *argv[],char **env) 
{
    /*
        1. We can add the signal hanlder, in this part.
    */
   if (argc == 1 && argv[0])
   {
    ft_parse_manager(env);
   }
}