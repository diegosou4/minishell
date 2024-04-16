/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parseredir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:33:37 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/19 01:41:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"

int	caseptr(char first, char second)
{
	if (first == '>' && second == '>')
		return (append_out);
	else if (first == '<' && second == '<')
		return (here_doc);
	else if (first == '<' && second == '>')
		return (inandout);
	else if (first == '<' && (second != '>' || second != '<'))
		return (redir_in);
	else if (first == '>' && (second != '>' || second != '<'))
		return (redir_out);
	return(0);
}

char	*ft_parse_redir(char *str)
{
	char	*ptr;
	char	*new;
	int	j;
	int	i;
	int	case_num;

	j = 0;
	i = 0; // initialize 'i' to 0
	ptr = str;
	new =  ft_calloc(sizeof(char ), ft_strlen(str) + 1); // allocate space for null character
	while(ptr[j])
	{
		case_num = caseptr(ptr[j], ptr[j + 1]);
		if (case_num == 0)
			new[i] = ptr[j];
		else if (case_num != 0)
			new[i] = case_num;
		if (case_num >= 3 && case_num <= 5)
		{
			j++;
		}
		i++;
		j++;
	}
	return(new);
}

char	*cleantoken(char *str, int c)
{
	int	i;
	i = 0;
	int	j;
	int	len;

	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			j++;
		i++;
	}
	len = (i - j);
	char *newstr;
	newstr = (char *) ft_calloc(sizeof(char), len);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		newstr[j] = str[i];
		j++;
		i++;
	}
	return (newstr);
}

char	*ft_strrange(char *s, int start, int end)
{
	int	i;
	i = 0;
	int len;
	char	*str;
	len = (end - start) + 1;
	str = (char *) ft_calloc(sizeof(char),len);
	while (i < (len - 1))
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}

char	*findfile(char *cmd)
{
	int	i;
	int	start;
	i = 0;
	char	*file;
	char	*newfile;
	while (cmd[i] != '\0')
	{
		while (cmd[i] > 6 && cmd[i] != '\0')
			i++;
		start = i;
		if (cmd[i] <= 5)
			break ;
	}
	file = ft_strrange(cmd,0,start);
	newfile = cleantoken(file,50);
	free(file);
	return(newfile);
}

int	checkcase(char c)
{
	int	i;
	i = 0;
	while (i < 6)
	{
		if (c == i)
			return (i);
		i++;
	}
	return (0);
}

void	addbackredir(t_redir *redir, char *file, int flag)
{
	t_redir	*ptr;
	t_redir	*last;

	last = redirnew();
	checkpathredir(last, file, flag);
	ptr = redir;
    while (ptr->next != NULL)
    {
	    ptr = ptr->next;
    }
    ptr->next = last;
}

void	initredir(t_redir **redir, int flag, char *file)
{
	if (*redir == NULL)
	{
		*redir = redirnew();
		checkpathredir(*redir, file, flag);
	}
	else
		addbackredir(*redir, file, flag);
}

