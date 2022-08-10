/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_red_next.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 01:57:24 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/26 01:45:36 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	heredoc_with_cmd_after(t_cmd **cmd, t_tkn **token, t_var *variable)
{
	t_tkn	*head;
	t_tkn	*tmp;

	head = *token;
	*token = (*token)->next;
	while (*token && !is_pipe_next_is_red(*token, (*token)->next)
		&& !is_pipe(*token))
	{
		collect_args_file(token, variable);
		tmp = *token;
		*token = tmp;
	}
	lst_addback(cmd, lst_new_cmd(head->content,
			variable->args, variable->f));
	set_null(variable);
	while (*token && !is_pipe_next_is_red(*token, (*token)->next)
		&& is_pipe(*token))
	{
		heredoc_with_cmd_after2(cmd, token, variable);
		tmp = *token;
		*token = tmp;
	}
}

void	checker1(t_cmd **cmd, t_tkn *n, t_tkn *tmp, t_var *variable)
{
	t_tkn	*token;

	while (n < tmp)
	{
		heredoc_with_no_cmd_after(cmd, &n, variable);
		token = n;
		n = token;
	}
}

void	checker2(t_cmd **cmd, t_tkn *n, t_tkn *tmp, t_var *variable)
{
	t_tkn	*token;

	token = n;
	if (token && !is_pipe_next_is_red(token, token->next) && is_pipe(token))
	{
		lst_addback(cmd, lst_new_cmd(NULL, NULL, variable->f));
		variable->f = NULL;
		while (n < tmp)
		{
			heredoc_with_pipe_after(cmd, &token, variable);
			n = token;
		}
	}
	else if (!get_redirect_index2(token)
		&& !is_pipe_next_is_red(token, token->next) && !is_pipe(token))
	{
		while (n < tmp)
		{
			heredoc_with_cmd_after(cmd, &token, variable);
			n = token;
		}
	}
}

void	checker(t_cmd **cmd, t_tkn **current, t_tkn *tmp, t_var *variable)
{
	t_tkn	*n;

	n = tmp;
	while (tmp)
	{
		if (is_pipe_next_is_red(tmp, tmp->next))
		{
			*current = tmp;
			if (n && get_redirect_index2(n))
			{
				lst_addback(cmd, lst_new_cmd(NULL, NULL, variable->f));
				variable->f = NULL;
				checker1(cmd, n, tmp, variable);
				break ;
			}
			else
			{
				checker2(cmd, n, tmp, variable);
				break ;
			}
		}
			tmp = tmp->next;
	}
}

void	pipe_next_red(t_cmd **cmd, t_var *variable, t_tkn *tmp)
{
	t_tkn	*current;

	current = NULL;
	if (get_redirect_index2(tmp) && check_is_a_pipe_next_red(tmp))
	{
		init_flag2(tmp, variable);
		fill_cmd_files_init(variable, tmp->next);
		tmp = tmp->next->next;
		checker(cmd, &current, tmp, variable);
		current = after_pipe_red_next(cmd, current, variable);
		while (current && is_pipe_next_is_red(current, current->next))
		{
			current = after_pipe_red_next(cmd, current, variable);
		}
	}
}
