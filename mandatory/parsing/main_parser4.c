/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 22:07:05 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/21 22:58:10 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_tkn	*fill_args_files_cmd(t_cmd **cmd, t_var *variable, t_tkn *token,
				t_tkn *comd)
{
	t_tkn	*n;

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
	return (token);
}

t_tkn	*after_pipe(t_cmd **cmd, t_var *variable, t_tkn *token)
{
	t_tkn	*comd;
	t_tkn	*n;

	token = token->next;
	comd = token;
	token = token->next;
	variable->f = NULL;
	variable->args = NULL;
	while (token && !is_pipe(token))
	{
		while (token && !is_pipe(token) && !get_redirect_index2(token))
		{
			lst_addback_args(&variable->args, lst_new_args(token->content));
			token = token->next;
		}
		after_pipe_2(&token, variable);
		n = token;
		token = n;
	}
	lst_addback(cmd, lst_new_cmd(comd->content, variable->args, variable->f));
	return (token);
}
