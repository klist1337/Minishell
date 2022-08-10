/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_next_red_utils1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 23:40:56 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/30 18:54:32 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	collect_files(t_tkn **token, t_var *variable)
{
	while (*token && get_redirect_index2(*token)
		&& !is_pipe_next_is_red(*token, (*token)->next))
	{
		init_flag2(*token, variable);
		fill_cmd_files_init(variable, (*token)->next);
		*token = (*token)->next->next;
	}
}

void	set_null(t_var *variable)
{
	variable->args = NULL;
	variable->f = NULL;
}

void	init_command(t_cmd **cmd, t_tkn **token, t_var *variable)
{
	t_tkn	*head;
	t_tkn	*n;

	if (*token && !is_pipe_next_is_red(*token, (*token)->next)
		&& !is_pipe(*token))
	{
		head = *token;
		*token = (*token)->next;
		while (!is_pipe_next_is_red(*token, (*token)->next) && !is_pipe(*token))
		{
			while (!is_pipe_next_is_red(*token, (*token)->next)
				&& !is_pipe(*token) && !get_redirect_index2(*token))
			{
				lst_addback_args(&variable->args,
					lst_new_args((*token)->content));
				*token = (*token)->next;
			}
			collect_files(token, variable);
			n = *token;
			*token = n;
		}
		lst_addback(cmd, lst_new_cmd(head->content,
				variable->args, variable->f));
		set_null(variable);
	}
}

void	init_cmd_pipe2(t_tkn **token, t_var *variable)
{
	while (*token && !is_pipe_next_is_red(*token, (*token)->next)
		&& !is_pipe(*token) && get_redirect_index2(*token))
	{
		init_flag2(*token, variable);
		fill_cmd_files_init(variable, (*token)->next);
		*token = (*token)->next->next;
	}
}

void	init_pipe_cmd(t_cmd **cmd, t_tkn **token, t_var *variable)
{
	t_tkn	*head;
	t_tkn	*n;

	if (!is_pipe_next_is_red(*token, (*token)->next) && is_pipe(*token))
	{
		while (!is_pipe_next_is_red(*token, (*token)->next) && is_pipe(*token))
		{
			*token = (*token)->next;
			head = *token;
			*token = (*token)->next;
			while (*token && !is_pipe_next_is_red(*token, (*token)->next)
				&& !is_pipe(*token) && !get_redirect_index2(*token))
			{
				lst_addback_args(&variable->args,
					lst_new_args((*token)->content));
				*token = (*token)->next;
			}
			init_cmd_pipe2(token, variable);
			n = *token;
			*token = n;
			lst_addback(cmd, lst_new_cmd(head->content,
					variable->args, variable->f));
			set_null(variable);
		}
	}
}
