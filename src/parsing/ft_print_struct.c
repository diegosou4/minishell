/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:44:02 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/20 13:44:04 by diegmore         ###   ########.fr       */
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
    // if (structure->redirection == FALSE)
    //     printf(ANSI_COLOR_YELLOW "Type Structure: " ANSI_COLOR_RESET ANSI_COLOR_GREEN ":%s:\n" ANSI_COLOR_RESET, "EXCECUTOR-TOKEN");
    // else if (structure->redirection == TRUE)
    //     printf(ANSI_COLOR_YELLOW "Type Structure: " ANSI_COLOR_RESET ANSI_COLOR_GREEN ":%s:\n" ANSI_COLOR_RESET, "NORMAL-PARSE");
    printf(ANSI_COLOR_YELLOW "[%d]" ANSI_COLOR_RESET, i);

    while (structure)
    {
        printf(ANSI_COLOR_YELLOW "|" ANSI_COLOR_RESET ANSI_COLOR_GREEN ":%s:" ANSI_COLOR_RESET, structure->word->word);
        // printf(ANSI_COLOR_RED "Flags:" ANSI_COLOR_RESET ANSI_COLOR_GREEN ":%d:\n" ANSI_COLOR_RESET, structure->word->flags);
        // printf(ANSI_COLOR_RED "Tags: " ANSI_COLOR_RESET ANSI_COLOR_GREEN ":%d:\n" ANSI_COLOR_RESET, structure->word->tags);
        // printf("------------------------------------\n");

        structure = structure->next;
    }
    printf(ANSI_COLOR_YELLOW "|" ANSI_COLOR_RESET ANSI_COLOR_GREEN ":%s:" ANSI_COLOR_RESET, "NULL");
    printf("\n");
    // printf(ANSI_COLOR_CYAN "____________END__STRUCT____________\n\n" ANSI_COLOR_RESET);
}