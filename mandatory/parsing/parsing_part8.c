/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part8.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 22:15:02 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/21 23:00:08 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	fill_cmd_files_pt1(t_tkn *tmp, t_cmd **cmd, t_var *variable)
{
	t_tkn	*head;
	t_tkn	*n;

	init_flag2(tmp, variable);
	fill_cmd_files_init(variable, tmp->next);
	tmp = tmp->next->next;
	head = tmp;
	if (!tmp)
		lst_addback(cmd, lst_new_cmd(NULL, NULL, variable->f));
	else if (!check_another_red(tmp))
	{
		n = head->next;
		while (n)
		{
			lst_addback_args(&variable->args, lst_new_args(n->content));
			n = n->next;
		}
		lst_addback(cmd, lst_new_cmd(head->content,
				variable->args, variable->f));
	}
	else if (get_redirect_index2(tmp))
		no_cmd_after_but_redirection(cmd, tmp, variable);
	else
		cmd_and_redsymbol(cmd, tmp, head, variable);
}

void	fill_cmd_files_pt2(t_cmd **cmd, t_tkn *tmp, t_var *variable)
{
	t_tkn	*n;
	t_tkn	*head;

	head = tmp;
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
			fill_cmd_files_part2_2(n, variable);
			if (!get_redirect_index2(head))
				lst_addback(cmd, lst_new_cmd(head->content,
						variable->args, variable->f));
			if (variable->flg == 1)
				break ;
		}
		tmp = tmp->next;
	}
}

void	fill_cmd_files(t_tkn *token, t_cmd **cmd)
{
	t_tkn	*tmp;
	t_var	variable;

	tmp = token;
	init_var(&variable);
	if (get_redirect_index2(tmp))
		fill_cmd_files_pt1(tmp, cmd, &variable);
	else
		fill_cmd_files_pt2(cmd, tmp, &variable);
}
