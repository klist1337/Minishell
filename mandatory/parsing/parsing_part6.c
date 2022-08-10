/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:51:22 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/31 18:46:10 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	fill_next_cmd_part1(t_cmd **cmd, t_tkn *i)
{
	t_tkn			*j;
	t_tkn			*n;
	t_tkn			*var;
	t_var			variable;

	j = i;
	var = get_index(j, "|");
	n = j->next;
	variable.args = NULL;
	while (n < var)
	{
		lst_addback_args(&variable.args, lst_new_args(n->content));
		n = n->next;
	}
	lst_addback(&(*cmd)->next, lst_new(j->content, variable.args));
}

void	fill_next_cmd_part2(t_cmd **cmd, t_tkn *i)
{
	t_tkn	*j;
	t_tkn	*n;
	t_tkn	*var;
	t_var	variable;

	j = i;
	var = get_index(j, "|");
	n = j->next;
	while (n <= var)
	{
		lst_addback_args(&variable.args, lst_new_args(n->content));
		n = n->next;
	}
	lst_addback(&(*cmd)->next, lst_new(j->content, variable.args));
}

void	fill_next_cmd_part3(t_cmd **cmd, t_tkn *i)
{
	t_tkn		*j;
	t_tkn		*n;
	t_tkn		*var;
	t_var		variable;

	j = i;
	var = last_lst_tkn(i);
	n = i->next;
	variable.args = NULL;
	while (n <= var && n)
	{
		lst_addback_args(&variable.args, lst_new_args(n->content));
		n = n->next;
	}
	lst_addback(&(*cmd)->next, lst_new(j->content, variable.args));
}

void	init_cmd(t_cmd **cmd, t_tkn *head, t_var *variable)
{
	if (head)
		lst_addback(cmd, lst_new_cmd(head->content,
				variable->args, variable->f));
}

void	no_cmd_after_but_red_part2_2(t_cmd **cmd, t_tkn *tmp, t_var *variable)
{
	t_tkn	*head;
	t_tkn	*n;

	head = NULL;
	while (tmp && get_redirect_index2(tmp))
	{
		no_cmd_after_part2_2_1(cmd, &tmp, variable);
		n = tmp;
		if (!tmp)
		{
			lst_addback(cmd, lst_new_cmd(NULL, NULL, variable->f));
			variable->f = NULL;
		}
		if (tmp && !get_redirect_index2(tmp))
		{
			head = tmp;
			tmp = tmp->next;
			iterator(&tmp, variable);
		}
		if (tmp == NULL)
			break ;
		n = tmp;
		tmp = n;
	}
	init_cmd(cmd, head, variable);
}
