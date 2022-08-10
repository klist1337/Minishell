/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 22:04:52 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/25 22:29:51 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	main_parser_p1111(t_cmd **cmd, t_var *variable, t_tkn *n, t_tkn *tmp)
{
	lst_addback(cmd, lst_new_cmd(NULL, NULL, variable->f));
	variable->f = NULL;
	while (n < tmp)
	{
		heredoc_flw_by_red(cmd, variable, n);
		n = tmp;
	}
}

void	main_parser_p111(t_tkn **tmp, t_tkn *n, t_cmd **cmd, t_var *variable)
{
	t_tkn	*current;

	while (*tmp)
	{
		if (is_pipe(*tmp))
		{
			current = *tmp;
			if (get_redirect_index2(n))
			{
				main_parser_p1111(cmd, variable, n, *tmp);
				break ;
			}
			else if (!get_redirect_index2(n) && !is_pipe(n))
			{
				heredoc_flw_by_cmd(cmd, variable, n);
				break ;
			}
			else
			{
				lst_addback(cmd, lst_new_cmd(NULL, NULL, variable->f));
				break ;
			}
		}
		*tmp = (*tmp)->next;
	}
}

void	main_parser_p11(t_tkn **tmp, t_cmd **cmd, t_var *variable)
{
	t_tkn	*n;

	n = *tmp;
	main_parser_p111(tmp, n, cmd, variable);
}

void	main_parser_p1(t_cmd **cmd, t_var *variable, t_tkn *token)
{
	t_tkn	*tmp;
	t_tkn	*n;
	t_tkn	*current;

	init_flag2(token, variable);
	fill_cmd_files_init(variable, token->next);
	tmp = token->next->next;
	main_parser_p11(&tmp, cmd, variable);
	current = tmp;
	n = after_pipe(cmd, variable, current);
	while (n && is_pipe(n))
	{
		current = after_pipe(cmd, variable, n);
		n = current;
	}
}

void	main_parser_p2(t_cmd **cmd, t_var *variable, t_tkn *token)
{
	t_tkn	*comd;
	t_tkn	*current;

	comd = token;
	token = token->next;
	current = fill_args_files_cmd(cmd, variable, token, comd);
	while (current && is_pipe(current))
	{
		token = after_pipe(cmd, variable, current);
		current = token;
	}
}
