#include "../../includes/mini.h"

char *ft_lexer_analysis(char *tokens)
{
    char *token;
    const char *delimiter;
    char **delimiter_holder;
    int i = -1;

    delimiter_holder = (char **)malloc(sizeof(char *) * 1000);
    delimiter = "2";
    token = ft_strtok(tokens, delimiter);
    while (token != NULL)
    {
        if(token[0])
        {
            delimiter_holder[++i] = token;
            printf(":%s:\n", delimiter_holder[i]);
        }
        token = ft_strtok(NULL, delimiter);
    }
    free(delimiter_holder);

    return NULL;
}


static char *ft_string_handle(char * line, char *modified_line)
{
    int j;
    char flag;
    char *ptr;

    ptr = line;
    flag = 0;
    j = 0;
    while (*ptr)
    {
        if (flag == 0 && (*ptr == '\"' || *ptr == '\''))
            flag = *ptr;
        else if (flag == *ptr)
            flag = 0; 
        if (flag == 0 && *ptr == ' ') 
            *ptr = '2';
        if(flag == 0 && *ptr == '|')
            *ptr = '3';
        else if (flag == 0)
        {
            j = ft_special_case(modified_line, j, &ptr);
            if (j == -2)
                return("NUlo");
        }
        modified_line[j++] = *ptr;
        ptr++;
    }
    return (modified_line);
}
/*
int ft_parse_handler(char *str, const char *delimiters)
{
    char **token_holder;
    int i = 0;
    
    token_holder = (char **)malloc(sizeof(char *) * ft_strlen(str)); // Allocate memory for 100 pointers
    if (!token_holder)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Tokenize the string using ft_strtok
    char *tokens = ft_strtok(str, delimiters);
    while (tokens != NULL)
    {
        token_holder[i] = tokens;
        tokens = ft_strtok(NULL, delimiters);
        i++;
    }

    // Set the last element of token_holder to NULL
    token_holder[i] = NULL;

    // Print the tokens
    int j = 0;
    while (token_holder[j] != NULL)
    {
        // printf("token : :%s:\n", token_holder[j]);
        ft_lexer_analysis(token_holder[j]);
        j++;
    }
    free(token_holder);
    return 0;
}*/

t_cmd   *returnmystruct(char *newline)
{
    t_cmd *commands;
   
    char **arr;
    arr = ft_split(newline,'3');
    int i;
    i = 1;
    commands = cmdnew(arr[0]);
    while(arr[i] != NULL)
    {
        cmdinback(&commands,arr[i]);
        i++;
    }
    t_cmd *ptr;

    ptr = commands;

    while(ptr != NULL)
    {
        char **args;
        args = ptr->args;
        int k;
        k = 0;
        while(args[k] != NULL)
        {
            printf("%s\n",args[k]);
            k++;
        } 
        printf("next struct -->\n");
        ptr = ptr->next;
    }
   return(commands);
}

char *ft_create_string(char *line, char **env)
{
    char *new_line;
    int i;
    t_cmd *comands;
    i = 0;
    new_line = ft_calloc(ft_strlen(line), sizeof(char*));
    new_line = ft_string_handle(line, new_line);
    comands = returnmystruct(new_line);
    ft_expand(&comands,env);
    return (new_line);
}
#include "../../includes/mini.h"


char *ft_lexer_analysis(char *tokens)
{
    char delimiter;
    char **delimiter_holder;
    int i = -1;
    t_cmd token_structure;

    delimiter_holder = (char **)malloc(sizeof(char *) * 1000);
    delimiter = '2';
    delimiter_holder = ft_split(tokens, delimiter);
    while (delimiter_holder[++i])
    {
        delimiter_holder[0];
        printf(":%s:\n", delimiter_holder);
    }
    free(delimiter_holder);
    return NULL;
}

int ft_parse_handler(char *str, const char *delimiters)
{
    char **token_holder;
    
    token_holder = (char **)malloc(sizeof(char *) * ft_strlen(str)); // Allocate memory for 100 pointers
    if (!token_holder && !delimiters)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    token_holder = ft_split(str, '3');
    int j = 0;
    while (token_holder[j] != NULL)
    {
        ft_lexer_analysis(token_holder[j]);
        j++;
    }
    free(token_holder);
    return 0;
}

static char *ft_string_handle(char * line, char *modified_line)
{
    int j;
    char flag;
    char *ptr;

    ptr = line;
    flag = 0;
    j = 0;
    while (*ptr)
    {
        if (flag == 0 && (*ptr == '\"' || *ptr == '\''))
            flag = *ptr;
        else if (flag == *ptr)
            flag = 0; 
        if (flag == 0 && *ptr == ' ') 
            *ptr = '2';
        if(flag == 0 && *ptr == '|')
            *ptr = '3';
        else if (flag == 0)
        {
            j = ft_special_case(modified_line, j, &ptr);
            if (j == -2)
                return("NUlo");
        }
        if (flag == 0 && *ptr == '|')
            *ptr = '3';
        modified_line[j++] = *ptr;
        ptr++;
    }
    return (modified_line);
}

/*
int ft_parse_handler(char *str, const char *delimiters)
{
    char **token_holder;
    int i = 0;
    
    token_holder = (char **)malloc(sizeof(char *) * ft_strlen(str)); // Allocate memory for 100 pointers
    if (!token_holder)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Tokenize the string using ft_strtok
    char *tokens = ft_strtok(str, delimiters);
    while (tokens != NULL)
    {
        token_holder[i] = tokens;
        tokens = ft_strtok(NULL, delimiters);
        i++;
    }

    // Set the last element of token_holder to NULL
    token_holder[i] = NULL;

    // Print the tokens
    int j = 0;
    while (token_holder[j] != NULL)
    {
        // printf("token : :%s:\n", token_holder[j]);
        ft_lexer_analysis(token_holder[j]);
        j++;
    }
    free(token_holder);
    return 0;
}*/

t_cmd   *returnmystruct(char *newline)
{
    t_cmd *commands;
   
    char **arr;
    arr = ft_split(newline,'3');
    int i;
    i = 1;
    commands = cmdnew(arr[0]);
    while(arr[i] != NULL)
    {
        cmdinback(&commands,arr[i]);
        i++;
    }
    t_cmd *ptr;

    ptr = commands;

    while(ptr != NULL)
    {
        char **args;
        args = ptr->args;
        int k;
        k = 0;
        while(args[k] != NULL)
        {
            printf("%s\n",args[k]);
            k++;
        } 
        printf("next struct -->\n");
        ptr = ptr->next;
    }
   return(commands);
}
char *ft_create_string(char *line)
{
    t_cmd *comands;
    i = 0;
    new_line = ft_calloc(ft_strlen(line), sizeof(char*));
    new_line = ft_string_handle(line, new_line);
    comands = returnmystruct(new_line);
    char *ptr = ft_strdup(line);
    i = 0;
    new_line = ft_calloc(ft_strlen(line), sizeof(char*));
    new_line = ft_string_handle(ptr, new_line);
    printf(":%s:\n", new_line);
    if (new_line)
        ft_parse_handler(new_line, "|");
}