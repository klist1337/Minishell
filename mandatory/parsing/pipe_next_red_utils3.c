/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_next_red_utils3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 23:43:54 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/31 18:46:41 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	heredoc_with_no_cmd_after2(t_cmd **cmd, t_tkn **token, t_var *variable)
{
	if (*token && (is_pipe_next_is_red(*token, (*token)->next)
			|| is_pipe(*token)))
	{
		lst_addback(cmd, lst_new_cmd(NULL, NULL, variable->f));
		variable->f = NULL;
	}
	init_command(cmd, token, variable);
	init_pipe_cmd(cmd, token, variable);
}

void	heredoc_with_no_cmd_after(t_cmd **cmd, t_tkn **n, t_var *variable)
{
	t_tkn	*token;
	t_tkn	*checker;

	token = *n;
	while (token && (get_redirect_index2(token))
		&& !is_pipe_next_is_red (token, token->next) && !is_pipe(token))
	{
		init_flag2(token, variable);
		fill_cmd_files_init(variable, token->next);
		checker = token->next->next;
		if (checker && get_redirect_index2(checker))
		{
			lst_addback(cmd, lst_new_cmd(NULL, NULL, variable->f));
			variable->f = NULL;
		}
		token = token->next->next;
	}
	heredoc_with_no_cmd_after2(cmd, &token, variable);
	*n = token;
}

void	heredoc_with_pipe_after(t_cmd **cmd, t_tkn **token, t_var *variable)
{
	t_tkn	*head;

	head = (*token)->next;
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
	lst_addback(cmd, lst_new_cmd(head->content, variable->args, variable->f));
	set_null(variable);
}

void	heredoc_with_cmd_after2(t_cmd **cmd, t_tkn **token, t_var *variable)
{
	t_tkn	*head;
	t_tkn	*n;

	head = (*token)->next;
	*token = (*token)->next->next;
	while (*token && !is_pipe(*token) && !get_redirect_index2(*token))
	{
		lst_addback_args(&variable->args, lst_new_args((*token)->content));
		*token = (*token)->next;
		while (*token && get_redirect_index2(*token) && !is_pipe(*token))
		{
			init_flag2(*token, variable);
			fill_cmd_files_init(variable, (*token)->next);
			*token = (*token)->next->next;
		}
		n = *token;
		*token = n;
	}
	lst_addback(cmd, lst_new_cmd(head->content, variable->args, variable->f));
	set_null(variable);
}

void	collect_args_file(t_tkn **token, t_var *variable)
{
	while (*token && !get_redirect_index2(*token) && !is_pipe(*token))
	{
		lst_addback_args(&variable->args, lst_new_args((*token)->content));
		*token = (*token)->next;
	}
	while (*token && get_redirect_index2(*token) && !is_pipe(*token))
	{
		init_flag2(*token, variable);
		fill_cmd_files_init(variable, (*token)->next);
		*token = (*token)->next->next;
	}
}
