/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 16:39:13 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/29 22:28:35 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	init_and_print_error(t_cmd **cmd, t_tkn	*token, t_var *variable)
{
	if (!token->next)
	{
		print_error("syntax error unexpected token\n");
		g_global.exit_value = 1;
		return (1);
	}
	init_flag2(token, variable);
	fill_cmd_files_init(variable, token->next);
	lst_addback(cmd, lst_new_cmd(NULL, NULL, variable->f));
	print_error("syntax error unexpected token\n");
	g_global.exit_value = 1;
	return (0);
}

int	redirection_error2(t_cmd **cmd, t_tkn *token, t_var *variable)
{
	while (token)
	{
		if (token->type == 6)
		{
			init_flag2(token, variable);
			fill_cmd_files_init(variable, token->next);
			lst_addback(cmd, lst_new_cmd(NULL, NULL, variable->f));
			variable->f = NULL;
		}
		else if (token->type == 8)
		{
			return (init_and_print_error(cmd, token, variable));
			break ;
		}
		token = token->next;
	}
	return (0);
}

int	redirection_error(t_tkn *token, t_cmd **cmd)
{
	t_var	variable;

	init_var(&variable);
	if (token->type == 8)
	{
		print_error("syntax error unexpected token\n");
		g_global.exit_value = 1;
		return (1);
	}
	return (redirection_error2(cmd, token, &variable));
}
