/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:21:34 by juan-pma          #+#    #+#             */
/*   Updated: 2024/03/13 13:27:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *ft_strcpy(char *dest, const char *src);

#include "../../includes/mini.h"

/*
    🚩 check this function as we are alocating
    memmory here.
*/

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
        }
    }
}

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
        {
            ft_checker_double_single(src, '\'');
            flag = !flag;
        }
        else if (*src == '\"' && !flag)
        {
            ft_checker_double_single(src, '\"');
            flag = !flag;
        }
        src++;
    }
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
        line->value_env = ft_strdup("non-env@user");
    else
        line->value_env = ft_path_handler(cpyenv, "USER");
    line->color_line = ft_strjoin(ANSI_COLOR_CYAN, (line->value_env));
    line->line_text = ft_strjoin(line->color_line,
                                 "@🐧shell:$ " ANSI_COLOR_RESET);
    free(line->value_env);
}