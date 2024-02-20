/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:07:11 by diegmore          #+#    #+#             */
/*   Updated: 2023/10/12 15:53:57 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*element;
	t_list	*listreturn;
	void	*temp;

	if (!lst || !f || !del)
		return (0);
	element = NULL;
	listreturn = NULL;
	while (lst)
	{
		temp = f(lst->content);
		element = ft_lstnew(temp);
		if (!element)
		{
			del(temp);
			ft_lstclear(&listreturn, del);
			return (listreturn);
		}
		ft_lstadd_back(&listreturn, element);
		lst = lst->next;
	}
	return (listreturn);
}

// Ft lst map
// primeiro criamos duas variaveis
// uma vai receber o valor
// fazemos a allocao usando ft_lstnew
// usamos a funcao f pois ela e responsavel
// por fazer alguma alteracao no content
// a f e executada faz sua alteracao
// depois chamamos a lstnew que aloca e coloca
// e retorna esse valor para o element
// depois verificamos se foi criado ou nao
// se for nulo ela entra lstclear que recebe
// a nossa lista que a gente estava tentando criar
// e limpa ela usando free
// ou seja a funcao meio que copiar uma stuct
// para outra usando a funcao f para fazer
// alteracoes no content e se nao de certo
// fazemos o free
// e interessante lembrar que adicionamos
// no final para fins de organizacao
// E importante frizar caso nossa alocacao
// der errado quando chamamos a ft_lstnew
// nos devemos da um free no nosso temp
// e a lstclear vai da free na 
// lista que vamos rertonar
// pois o comportamento e que 
// devemos retornar um nullo 
// mas temos que ser bem criteriosos
// desta forma faz corre bem
//  void *(*f)(void *) permite que você aponte para
// funções que retornam ponteiros para qualquer tipo de dado.
// void (*del)(void *) permite que você aponte para funções que não
// retornam nenhum valor (retorno void) e são geralmente usadas
//  para operações de limpeza e liberação de recursos.
//