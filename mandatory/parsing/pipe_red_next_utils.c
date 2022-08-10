/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_red_next_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 23:37:12 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/25 23:37:24 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/////---after_pipe_red_if if there is a cmd -------//////

void	aft_pipred_with_cmd_after2(t_cmd **cmd, t_tkn **token, t_var *variable)
{
	t_tkn	*head;

	head = (*token)->next;
	*token = (*token)->next->next;
	while (*token && !is_pipe(*token) && !get_redirect_index2(*token))
	{
		lst_addback_args(&variable->args, lst_new_args((*token)->content));
		*token = (*token)->next;
	}
	while (*token && get_redirect_index2(*token))
	{
		init_flag2(*token, variable);
		fill_cmd_files_init(variable, (*token)->next);
		*token = (*token)->next->next;
	}
	lst_addback(cmd, lst_new_cmd(head->content, variable->args, variable->f));
	set_null(variable);
}

void	after_pipred_with_cmd_after(t_cmd **cmd, t_tkn **token, t_var *variable)
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
	while (*token && !is_pipe_next_is_red(*token, (*token)->next))
	{
		aft_pipred_with_cmd_after2(cmd, token, variable);
		tmp = *token;
		*token = tmp;
	}
}
///////------after_pipe_red_next_main_funct-----------/////

t_tkn	*after_pipe_red_next(t_cmd **cmd, t_tkn *current, t_var *variable)
{
	current = current->next;
	init_flag2(current, variable);
	fill_cmd_files_init(variable, current->next);
	current = current->next->next;
	if ((current && is_pipe_next_is_red(current, current->next)) || !current)
		lst_addback(cmd, lst_new_cmd(NULL, NULL, variable->f));
	else if (current && get_redirect_index2(current))
	{
		after_pipe_red1(cmd, &current, variable);
		after_pipe_red2(cmd, &current, variable);
	}
	else if (current && !is_pipe_next_is_red(current, current->next)
		&& is_pipe(current))
	{
		lst_addback(cmd, lst_new_cmd(NULL, NULL, variable->f));
		variable->f = NULL;
		after_red_pipe_with_pipe_after(cmd, &current, variable);
	}
	else if (current && !get_redirect_index2(current)
		&& !is_pipe_next_is_red(current, current->next) && !is_pipe(current))
		after_pipred_with_cmd_after(cmd, &current, variable);
	set_null(variable);
	return (current);
}
