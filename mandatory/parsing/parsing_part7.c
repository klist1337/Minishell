/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part7.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 22:13:45 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/23 07:04:38 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	no_cmd_after_but_red_part1(t_tkn *tmp, t_var *variable)
{
	while (tmp)
	{
		if (get_redirect_index2(tmp))
		{
			init_flag2(tmp, variable);
			fill_cmd_files_init(variable, tmp->next);
			tmp = tmp->next->next;
		}
		if (tmp && !get_redirect_index2(tmp))
			lst_addback_args(&variable->args, lst_new_args(tmp->content));
		if (tmp)
			tmp = tmp->next;
	}
}

void	no_cmd_after_but_red_part2(t_cmd **cmd, t_tkn *tmp, t_var *variable)
{
	t_tkn	*head;

	lst_addback(cmd, lst_new_cmd(NULL, variable->args, variable->f));
	variable->f = NULL;
	tmp = tmp->next->next;
	if (!get_redirect_index2(tmp))
	{
		head = tmp;
		tmp = tmp->next;
		no_cmd_after_but_red_part1(tmp, variable);
		lst_addback(cmd, lst_new_cmd(head->content,
				variable->args, variable->f));
	}
	else if (get_redirect_index2(tmp))
		no_cmd_after_but_red_part2_2(cmd, tmp, variable);
}

void	no_cmd_after_but_redirection(t_cmd **cmd, t_tkn *tmp, t_var *variable)
{
	t_tkn	*head;
	t_tkn	*n;

	head = NULL;
	n = NULL;
	lst_addback(cmd, lst_new_cmd(NULL, NULL, variable->f));
	variable->f = NULL;
	if (get_redirect_index2(tmp))
	{
		init_flag2(tmp, variable);
		fill_cmd_files_init(variable, tmp->next);
		if (!tmp->next->next)
			lst_addback(cmd, lst_new_cmd(NULL, variable->args, variable->f));
		else if (tmp->next->next && !tmp->next->next->next)
			lst_addback(cmd, lst_new_cmd(tmp->next->next->content,
					variable->args, variable->f));
		else
			no_cmd_after_but_red_part2(cmd, tmp, variable);
	}
}

void	cmd_and_redsymbol_2(t_tkn *n, t_var *variable)
{
	t_tkn	*tmp2;

	while (n)
	{
		if (get_redirect_index2(n))
		{
			init_flag2(n, variable);
			fill_cmd_files_init(variable, n->next);
			tmp2 = n->next->next;
			while (tmp2 && !get_redirect_index2(tmp2))
			{
				lst_addback_args(&variable->args, lst_new_args(tmp2->content));
				tmp2 = tmp2->next;
			}
		}
		n = n->next;
	}
}

void	cmd_and_redsymbol(t_cmd **cmd, t_tkn *tmp, t_tkn *head, t_var *variable)
{
	t_tkn	*n;

	while (tmp)
	{
		if (get_redirect_index2(tmp))
		{
			variable->flg = 1 ;
			n = head->next;
			while (n && n < tmp && !get_redirect_index2(n))
			{
				lst_addback_args(&variable->args, lst_new_args(n->content));
				n = n->next;
			}
			n = tmp;
			cmd_and_redsymbol_2(n, variable);
			if (!get_redirect_index2(head))
				lst_addback(cmd, lst_new_cmd(head->content,
						variable->args, variable->f));
			else
				lst_addback(cmd, lst_new_cmd(NULL, NULL, variable->f));
			if (variable->flg == 1)
				break ;
		}
		tmp = tmp ->next;
	}
}
