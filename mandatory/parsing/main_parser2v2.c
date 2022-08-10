/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser2v2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:35:26 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/21 22:08:25 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	heredoc_flw_secondpart_2(t_tkn **tmp, t_var *variable)
{
	while (*tmp && get_redirect_index2(*tmp) && !is_pipe(*tmp))
	{
		init_flag2(*tmp, variable);
		fill_cmd_files_init(variable, (*tmp)->next);
		*tmp = (*tmp)->next->next;
	}
}

void	heredoc_flw_secondpart(t_cmd **cmd, t_var *variable, t_tkn *tmp)
{
	t_tkn	*n;
	t_tkn	*head;

	if (tmp && !is_pipe(tmp))
	{
		head = tmp;
		tmp = tmp->next;
		while (!is_pipe(tmp))
		{
			while (tmp && !get_redirect_index2(tmp) && !is_pipe(tmp))
			{
				lst_addback_args(&variable->args, lst_new_args(tmp->content));
				tmp = tmp->next;
			}
			heredoc_flw_secondpart_2(&tmp, variable);
			n = tmp;
			tmp = n;
		}
		lst_addback(cmd, lst_new_cmd(head->content, variable->args,
				variable->f));
	}
}

void	heredoc_flw_by_red(t_cmd **cmd, t_var *variable, t_tkn *tmp)
{
	t_tkn	*n;

	while (get_redirect_index2(tmp) && !is_pipe(tmp))
	{
		init_flag2(tmp, variable);
		fill_cmd_files_init(variable, tmp->next);
		n = tmp->next->next;
		if (n && get_redirect_index2(n))
		{
			lst_addback(cmd, lst_new_cmd(NULL, NULL, variable->f));
			variable->f = NULL;
		}
		n = tmp->next;
		tmp = tmp->next->next;
	}
	if (tmp && is_pipe(tmp))
	{
		lst_addback(cmd, lst_new_cmd(NULL, NULL, variable->f));
		variable->f = NULL;
	}
	heredoc_flw_secondpart(cmd, variable, tmp);
}

void	heredoc_flw_by_cmd(t_cmd **cmd, t_var *variable, t_tkn *token)
{
	t_tkn	*comd;
	t_tkn	*n;

	comd = token;
	token = token->next;
	while (token && !is_pipe(token))
	{
		while (token && !is_pipe(token) && !get_redirect_index2(token))
		{
			lst_addback_args(&variable->args, lst_new_args(token->content));
			token = token->next;
		}
		while (token && !is_pipe(token) && get_redirect_index2(token))
		{
			init_flag2(token, variable);
			fill_cmd_files_init(variable, token->next);
			token = token->next->next;
		}
		n = token;
		token = n;
	}
	lst_addback(cmd, lst_new_cmd(comd->content, variable->args, variable->f));
}

void	after_pipe_2(t_tkn **token, t_var *variable)
{
	while (*token && !is_pipe(*token) && get_redirect_index2(*token))
	{
		init_flag2(*token, variable);
		fill_cmd_files_init(variable, (*token)->next);
		*token = (*token)->next->next;
	}
}
