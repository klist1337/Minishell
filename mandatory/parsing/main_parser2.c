/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 15:35:12 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/30 18:42:54 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_pipe(t_tkn *token)
{
	if (!ft_strncmp(token->content, "|", 1) && token->type == 1)
		return (1);
	return (0);
}

int	is_pipe_next_is_red(t_tkn *token, t_tkn *next)
{
	if (is_pipe(token) && next && get_redirect_index2(next))
		return (1);
	return (0);
}

int	check_is_a_pipe_next_red(t_tkn *token)
{
	while (token)
	{
		if (is_pipe_next_is_red(token, token->next))
			return (1);
		token = token->next;
	}
	return (0);
}

int	main_parser2_part2(t_cmd **cmd, t_tkn *token, t_var *variable)
{
	t_tkn	*tmp;
	t_tkn	*tmp2;
	t_tkn	*n;
	t_tkn	*red;

	tmp = token;
	tmp2 = NULL;
	n = NULL;
	red = NULL;
	variable->x = ft_error2(token);
	if (variable->x == 1)
		return (1);
	else if (get_redirect_index2(tmp) && !check_is_a_pipe_next_red(tmp))
		main_parser_p1(cmd, variable, tmp);
	else if (!get_redirect_index2(tmp) && !check_is_a_pipe_next_red(tmp))
		main_parser_p2(cmd, variable, tmp);
	else
	{
		pipe_next_red(cmd, variable, tmp);
		pipe_next_red_case2(cmd, variable, tmp);
	}
	return (0);
}

int	main_parser2(t_cmd **cmd, t_tkn *token)
{
	t_var	variable;

	init_var(&variable);
	variable.x = ft_error(cmd, token, &variable);
	if (variable.x == 1)
		return (1);
	variable.n = 1;
	variable.x = main_parser2_part2(cmd, token, &variable);
	if (variable.x == 1)
		return (1);
	return (0);
}
