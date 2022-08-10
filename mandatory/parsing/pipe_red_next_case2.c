/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_red_next_case2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 00:15:57 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/26 00:54:54 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	another_check(t_cmd **cmd, t_tkn **current, t_tkn *tmp, t_var *variable)
{
	t_tkn	*n;
	t_tkn	*token;

	n = tmp;
	while (tmp)
	{
		if (is_pipe_next_is_red(tmp, tmp->next))
		{
			*current = tmp;
			while (n < tmp)
			{
				heredoc_with_cmd_after(cmd, &n, variable);
				token = n;
				n = token;
			}
			break ;
		}
		tmp = tmp->next;
	}
}

void	pipe_next_red_case2(t_cmd **cmd, t_var *variable, t_tkn *tmp)
{
	t_tkn	*current;

	current = NULL;
	if (!get_redirect_index2(tmp) && check_is_a_pipe_next_red(tmp))
	{
		another_check(cmd, &current, tmp, variable);
		current = after_pipe_red_next(cmd, current, variable);
		while (current && is_pipe_next_is_red(current, current->next))
			current = after_pipe_red_next(cmd, current, variable);
	}
}
