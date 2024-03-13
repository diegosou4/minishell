/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:44:02 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/11 23:35:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

// void printstruct(t_cmd *commands)
// {
//     t_cmd *ptr;

//     ptr = commands;

//     while(ptr != NULL)
//     {
//         printf("Path: %s\n", ptr->path);
//         printf("Args: ");
//         printdp(ptr->args);
//         printf("FILE 1 %i \nFILE 2 %i \n", ptr->fd[0], ptr->fd[1]);
//         if(ptr->redir != NULL)
//         {
//             t_redir *pr;
//             pr = ptr->redir;
//             while(pr != NULL)
//             {
//                 printf("Redir string %s", pr->str);
//                 printf("File %i", pr->fd);
//                 pr = pr->next;
//             }
//         }
//         ptr = ptr->next;
//     }
// }

const char *tag_names[] = {
    "WORD",
    "EXECUTOR",
    "VARIABLE",
    "SPECIAL_PAR",
    "SPECIAL_VAR",
    "VARIABLE_CHECK",
    "PATH"};

void ft_print_doble_char(char **argv)
{
    int i = -1;
    while (argv[++i] && argv[i][0])
    {
        printf("Test Element [%d] = :%s:\n", i, argv[i]);
    }
}

void ft_print_list_struct(t_word_list *structure, int i)
{
    // printf(ANSI_COLOR_GREEN "____________START__STRUCT____________\n" ANSI_COLOR_RESET);
    if (structure->redirection == TRUE)
        printf(ANSI_COLOR_YELLOW "Type Structure: " ANSI_COLOR_RESET ANSI_COLOR_GREEN ":%s:\n" ANSI_COLOR_RESET, "EXCECUTOR-TOKEN");
    else if (structure->redirection == FALSE)
        printf(ANSI_COLOR_YELLOW "Type Structure: " ANSI_COLOR_RESET ANSI_COLOR_GREEN ":%s:\n" ANSI_COLOR_RESET, "NORMAL-PARSE");
    printf(ANSI_COLOR_YELLOW "[%d]" ANSI_COLOR_RESET, i);

    while (structure)
    {
        printf(ANSI_COLOR_YELLOW "--" ANSI_COLOR_RESET ANSI_COLOR_GREEN ":%s:\n" ANSI_COLOR_RESET, structure->word->word);
        switch (structure->word->flags)
        {
        case redir_out:
            printf(ANSI_COLOR_YELLOW "--flag:" ANSI_COLOR_RESET ANSI_COLOR_GREEN ":%s:\n" ANSI_COLOR_RESET, "redir_out");
            break;
        case redir_in:
            printf(ANSI_COLOR_YELLOW "--flag:" ANSI_COLOR_RESET ANSI_COLOR_GREEN ":%s:\n" ANSI_COLOR_RESET, "redir_in");
            break;
        case here_doc:
            printf(ANSI_COLOR_YELLOW "--flag:" ANSI_COLOR_RESET ANSI_COLOR_GREEN ":%s:\n" ANSI_COLOR_RESET, "here_doc");
            break;
        case append_out:
            printf(ANSI_COLOR_YELLOW "--flag:" ANSI_COLOR_RESET ANSI_COLOR_GREEN ":%s:\n" ANSI_COLOR_RESET, "append_out");
            break;
        case inandout:
            printf(ANSI_COLOR_YELLOW "--flag:" ANSI_COLOR_RESET ANSI_COLOR_GREEN ":%s:\n" ANSI_COLOR_RESET, "inandout");
            break;
        default:
            printf(ANSI_COLOR_YELLOW "--flag:" ANSI_COLOR_RESET ANSI_COLOR_GREEN ":%s:\n" ANSI_COLOR_RESET, "normal word");
            break;
        }
        switch (structure->word->tags)
        {
        case WORD:
            printf(ANSI_COLOR_YELLOW "--tags:" ANSI_COLOR_RESET ANSI_COLOR_GREEN ":%s:" ANSI_COLOR_RESET, tag_names[WORD]);
            break;
        case EXCECUTOR:
            printf(ANSI_COLOR_YELLOW "--tags:" ANSI_COLOR_RESET ANSI_COLOR_GREEN ":%s:" ANSI_COLOR_RESET, tag_names[EXCECUTOR]);
            break;
        case VARIABLE:
            printf(ANSI_COLOR_YELLOW "--tags:" ANSI_COLOR_RESET ANSI_COLOR_GREEN ":%s:" ANSI_COLOR_RESET, tag_names[VARIABLE]);
            break;
        case SPECIAL_PAR:
            printf(ANSI_COLOR_YELLOW "--tags:" ANSI_COLOR_RESET ANSI_COLOR_GREEN ":%s:" ANSI_COLOR_RESET, tag_names[SPECIAL_PAR]);
            break;
        case SPECIAL_VAR:
            printf(ANSI_COLOR_YELLOW "--tags:" ANSI_COLOR_RESET ANSI_COLOR_GREEN ":%s:" ANSI_COLOR_RESET, tag_names[SPECIAL_VAR]);
            break;
        case VARIABLE_CHECK:
            printf(ANSI_COLOR_YELLOW "--tags:" ANSI_COLOR_RESET ANSI_COLOR_GREEN ":%s:" ANSI_COLOR_RESET, tag_names[VARIABLE_CHECK]);
            break;
        case PATH:
            printf(ANSI_COLOR_YELLOW "--tags:" ANSI_COLOR_RESET ANSI_COLOR_GREEN ":%s:" ANSI_COLOR_RESET, tag_names[PATH]);
            break;
        default:
            printf(ANSI_COLOR_YELLOW "--tags:" ANSI_COLOR_RESET ANSI_COLOR_GREEN ":%s:" ANSI_COLOR_RESET, tag_names[WORD]);
            break;
        }

        // printf("------------------------------------\n");

        structure = structure->next;
        // printf(ANSI_COLOR_YELLOW "|" ANSI_COLOR_RESET ANSI_COLOR_GREEN ":%s:" ANSI_COLOR_RESET, "NULL");
        printf("\n");
        // printf(ANSI_COLOR_CYAN "____________END__STRUCT____________\n\n" ANSI_COLOR_RESET);
    }
}

void ft_print_cmd_struct(t_cmd *cmd)
{
    printf(ANSI_COLOR_CYAN "---------- Command Structure ----------\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "Path: " ANSI_COLOR_RESET ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET, cmd->path);

    printf(ANSI_COLOR_YELLOW "Arguments:\n" ANSI_COLOR_RESET);
    for (int i = 0; cmd->args[i] != NULL; i++)
    {
        printf(ANSI_COLOR_GREEN "- %s\n" ANSI_COLOR_RESET, cmd->args[i]);
    }

    printf(ANSI_COLOR_YELLOW "Redirections:\n" ANSI_COLOR_RESET);
    t_redir *redir = cmd->redir;
    while (redir != NULL)
    {
        printf(ANSI_COLOR_GREEN "- Path: %s, Token: %d, FD: %d\n" ANSI_COLOR_RESET,
               redir->path, redir->token, redir->fd);
        redir = redir->next;
    }

    printf(ANSI_COLOR_CYAN "---------------------------------------\n" ANSI_COLOR_RESET);
}
