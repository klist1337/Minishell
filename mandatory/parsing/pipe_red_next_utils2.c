/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_red_next_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:52:55 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/25 23:37:07 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_pipe_cmd_after_pipe_red(t_cmd **cmd, t_tkn **tk, t_var *variable)
{
	t_tkn	*h;
	t_tkn	*n;

	if (!is_pipe_next_is_red(*tk, (*tk)->next) && is_pipe(*tk))
	{
		while (*tk && !is_pipe_next_is_red(*tk, (*tk)->next)
			&& is_pipe(*tk))
		{
			*tk = (*tk)->next;
			h = *tk;
			*tk = (*tk)->next;
			while (*tk && !is_pipe_next_is_red(*tk, (*tk)->next)
				&& !is_pipe(*tk) && !get_redirect_index2(*tk))
			{
				lst_addback_args(&variable->args, lst_new_args((*tk)->content));
				*tk = (*tk)->next;
			}
			init_cmd_pipe2(tk, variable);
			n = *tk;
			*tk = n;
			lst_addback(cmd, lst_new_cmd(h->content,
					variable->args, variable->f));
			set_null(variable);
		}
	}
}

void	init_cmd_after_pipe_red(t_cmd **cmd, t_tkn **token, t_var *variable)
{
	t_tkn	*h;
	t_tkn	*n;

	if (*token && !is_pipe_next_is_red(*token, (*token)->next)
		&& !is_pipe(*token))
	{
		h = *token;
		*token = (*token)->next;
		while (*token
			&& !is_pipe_next_is_red(*token, (*token)->next) && !is_pipe(*token))
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
		lst_addback(cmd, lst_new_cmd(h->content, variable->args, variable->f));
		set_null(variable);
	}
}

void	after_pipe_red2(t_cmd **cmd, t_tkn **current, t_var *variable)
{
	if (*current && (is_pipe_next_is_red(*current, (*current)->next)
			|| is_pipe(*current)))
	{
		lst_addback(cmd, lst_new_cmd(NULL, NULL, variable->f));
		variable->f = NULL;
	}
	init_cmd_after_pipe_red(cmd, current, variable);
	init_pipe_cmd_after_pipe_red(cmd, current, variable);
}

void	after_pipe_red1(t_cmd **cmd, t_tkn **current, t_var *variable)
{
	t_tkn	*checker;

	while (*current && (get_redirect_index2(*current))
		&& !is_pipe_next_is_red (*current, (*current)->next)
		&& !is_pipe(*current))
	{
		init_flag2(*current, variable);
		fill_cmd_files_init(variable, (*current)->next);
		checker = (*current)->next->next;
		if (checker && get_redirect_index2(checker))
		{
			lst_addback(cmd, lst_new_cmd(NULL, NULL, variable->f));
			variable->f = NULL;
		}
		*current = (*current)->next->next;
	}
}
/////-----after_pipe_red_ if there is a pipe ----------/////////

void	after_red_pipe_with_pipe_after(t_cmd **cmd, t_tkn **token,
	t_var *variable)
{
	t_tkn	*h;
	t_tkn	*n;

	while (*token && is_pipe(*token))
	{	
		h = (*token)->next;
		*token = (*token)->next->next;
		while (*token && !is_pipe_next_is_red(*token, (*token)->next)
			&& !is_pipe(*token) && !get_redirect_index2(*token))
		{
			lst_addback_args(&variable->args, lst_new_args((*token)->content));
			*token = (*token)->next;
		}
		while (*token && !is_pipe_next_is_red(*token, (*token)->next)
			&& get_redirect_index2(*token))
		{
			init_flag2(*token, variable);
			fill_cmd_files_init(variable, (*token)->next);
			*token = (*token)->next->next;
		}
		lst_addback(cmd, lst_new_cmd(h->content, variable->args, variable->f));
		set_null(variable);
		n = *token;
		*token = n;
	}
}
