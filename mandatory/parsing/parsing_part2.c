/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:54:05 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/30 18:45:56 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parsing_simple_cmd_2(t_cmd **cmd, t_tkn *token)
{
	t_tkn	*tmp;
	t_var	variable;

	tmp = last_lst_tkn(token);
	init_var(&variable);
	if ((get_redirect_index2(tmp) && !tmp)
		|| ((get_redirect_index2(token) && !token->next)))
	{
		print_error("syntax error\n");
		g_global.exit_value = 1;
		return (1);
	}
	else if (ft_error(cmd, token, &variable))
		return (1);
	fill_cmd_files(token, cmd);
	return (0);
}

int	parsing_simple_cmd(t_tkn *token, t_cmd **cmd)
{
	t_var	variable;
	t_tkn	*tmp;

	tmp = token;
	variable.args = NULL;
	if (tmp != NULL && !check_redirect2(tmp))
	{
		while (tmp->next)
		{
			lst_addback_args(&variable.args, lst_new_args(tmp->next->content));
			tmp = tmp->next;
		}
		lst_addback(cmd, lst_new(token->content, variable.args));
	}
	else
	{
		variable.x = parsing_simple_cmd_2(cmd, token);
		return (variable.x);
	}
	return (0);
}

void	join_arg(t_args **arg, t_tkn *n, t_tkn *j)
{
	while (n < j)
	{
		lst_addback_args(arg, lst_new_args(n->content));
		n = n->next;
	}
}

void	parse_cmd_pipe_p2(t_tkn *token, t_cmd **cmd, t_var *var,
	t_tkn_var tkn_var)
{
	tkn_var.j = tkn_var.i;
	var->s = ft_calloc(1, sizeof(char));
	join_arg(&var->args, tkn_var.n, tkn_var.j);
	lst_addback(cmd, lst_new(token->content, var->args));
}

void	parse_cmd_pipe(t_tkn *token, t_cmd **cmd)
{
	t_var		variable;
	t_tkn_var	tkn_var;

	tkn_var.i = token;
	tkn_var.n = token->next;
	variable.args = NULL;
	while (tkn_var.i)
	{
		if (!ft_strncmp(tkn_var.i->content, "|", 1)
			&& tkn_var.i->type == 1 && tkn_var.i->next)
		{
			tkn_var.j = tkn_var.i;
			join_arg(&variable.args, tkn_var.n, tkn_var.j);
			lst_addback(cmd, lst_new(token->content, variable.args));
			break ;
		}
		else if ((!ft_strncmp(tkn_var.i->content, "|", 1)
				&& tkn_var.i->type == 1 && !tkn_var.i->next))
		{
			parse_cmd_pipe_p2(token, cmd, &variable, tkn_var);
			break ;
		}
		tkn_var.i = tkn_var.i->next;
	}
	fill_next_cmd(token, cmd);
}
