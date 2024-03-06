/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-pma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:21:34 by juan-pma          #+#    #+#             */
/*   Updated: 2024/02/21 10:49:44 by juan-pma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *ft_strcpy(char *dest, const char *src);

#include "../../includes/mini.h"

/*
    🚩 check this function as we are alocating
    memmory here.
*/
t_cmd *cmdnew(char *args)
{
    t_cmd *comands;
    char **newarg;
    int len;
    int i;

    i = -1;
    len = 0;
    comands = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
    newarg = ft_split(args, '2');

    while (newarg[len] != NULL)
        len++;
    char **modified_list = (char **)malloc((len * 5) * sizeof(char *));
    while (++i < len)
    {
        modified_list[i] = (char *)malloc((ft_strlen(newarg[i]) + 1) * sizeof(char));
        ft_strcpy(modified_list[i], newarg[i]);
    }
    comands->args = modified_list;
    comands->next = NULL;
    comands->redir = NULL;
    return (comands);
}

void cmdinback(t_cmd **comands, char *args)
{
    t_cmd *ptr;
    t_cmd *last;

    last = cmdnew(args);
    if (last == NULL)
        return;
    ptr = *(comands);
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = last;
}
char *ft_strcpy(char *dest, const char *src)
{
    if (!src)
        return (NULL);
    while (*src)
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return dest;
}
// This line is to move the string one infront and remove the $ when is followed by a '
static void ft_preline(char *line)
{
    int i;
    i = -1;
    while (line[++i])
    {
        if (line[i] == '$' && line[i + 1] == '\'')
        {
            ft_memmove(&line[i], &line[i + 1], ft_strlen(&line[i + 1]) + 1);
            // ft_checker_quotes(&line[i], 2);
        }
    }
    // printf("line without $ :%s:\n", line);
}

// void ft_checker_quotes(char *str)
// {
//     int len;
//     len = ft_strlen(str);

//     while (*str)
//     {
//         if ((str[0] == '\'' && str[len - 1] == '\'') || (str[0] == '\"' && str[len - 1] == '\"'))
//         {
//             str[len - 1] = '\0';
//             ft_memmove(str, (str + 1), len - 1);
//             break;
//         }
//     }
// }

// void ft_checker_quotes_single(char *str)
// {
//     char *src;
//     char *dest;
//     int flag;

//     flag = 0;
//     src = str;
//     dest = str;

//     while (*src)
//     {
//         if (*src == '\'' && !flag)
//         {
//             src++;
//             continue;
//         }
//         if (*src == '\'' && flag)
//             flag = !flag;
//         *dest++ = *src++;
//     }
//     *dest = '\0';
//     printf("this is the dest :%s:\n", dest);
// }

void ft_checker_double_single(char *str, char quote)
{
    char *src;
    char *dest;
    int flag;

    flag = 0;
    src = str;
    dest = str;

    while (*src)
    {
        if (*src == quote && !flag)
        {
            src++;
            continue;
        }
        if (*src == quote && flag)
            flag = !flag;
        *dest++ = *src++;
    }
    *dest = '\0';
    printf("this is the dest :%s:\n", dest);
}
void ft_checker_quotes(char *str)
{
    char *src;
    int flag;

    flag = 0;
    src = str;

    while (*src)
    {
        if (*src == '\'' && !flag)
            ft_checker_double_single(src, '\'');
        else if (*src == '\"' )
        {
            ft_checker_double_single(src, '\"');
            flag = !flag;
        }
        src++;
    }
    printf("this is the dest :%s:\n", src);
}

void ft_quotes_remove(t_word_list *word_list)
{
    char *word;

    while (word_list)
    {
        word = word_list->word->word;
        ft_checker_quotes(word);
        word_list = word_list->next;
    }
}

char *ft_strtok(char *str, const char *delimiters)
{
    static char *buffer = NULL;
    char *token_start;

    if (!str && !buffer)
        return (NULL);
    if (str)
        buffer = str;
    while (*buffer && ft_strchr(delimiters, *buffer))
        buffer++;

    token_start = buffer;
    buffer = ft_strpbrk(token_start, delimiters);
    if (buffer)
        *buffer++ = '\0';
    return (token_start);
}

int ft_whitespace(char *line)
{
    int i;

    i = 0;

    while ((line[i] >= '\b' && line[i] <= '\v') || line[i] == ' ')
    {
        i++;
    }
    if (i == (int)ft_strlen(line))
        return (0);

    return (1);
}
//-----------------------------------Line Handler...........................
void ft_line_handler(t_line *line, t_env *cpyenv)
{
    if (cpyenv == NULL)
        line->value_env = "non-env@user";
    else 
        line->value_env = ft_path_handler(cpyenv, "USER");
    line->color_line = ft_strjoin(ANSI_COLOR_CYAN, (line->value_env));
    line->line_text = ft_strjoin(line->color_line,
                                 "@🐧shell:$ " ANSI_COLOR_RESET);
}