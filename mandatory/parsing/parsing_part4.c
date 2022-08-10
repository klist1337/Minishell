/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:21:22 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/30 18:50:42 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_error_part1(t_cmd **cmd, t_tkn *n, t_tkn *token, t_var *variable)
{
	if ((n && get_redirect_index2(n))
		|| (n && !ft_strncmp(n->content, "|", 1) && n->type == 1))
	{
		if (n && get_redirect_index2(n))
		{
			print_error("syntax error\n");
			init_flag2(token, variable);
			fill_cmd_files_init(variable, token->next);
			lst_addback(cmd, lst_new_cmd(NULL, NULL, variable->f));
			g_global.exit_value = 1;
			return (1);
		}
		else
		{
			print_error("syntax error\n");
			g_global.exit_value = 1;
			return (1);
		}
	}
	return (0);
}

int	ft_error(t_cmd **cmd, t_tkn *token, t_var *variable)
{
	t_tkn	*n;

	n = last_lst_tkn(token);
	variable->x = ft_error_part1(cmd, n, token, variable);
	if (variable->x == 1)
		return (1);
	while (token)
	{
		if (get_redirect_index2(token) && token->next && is_pipe(token->next))
		{
			print_error("syntax error\n");
			g_global.exit_value = 1;
			return (1);
		}
		else if (get_redirect_index2(token) && token->next
			&& get_redirect_index2(token->next))
		{
			print_error("syntax error\n");
			g_global.exit_value = 1;
			return (1);
		}
		token = token->next;
	}
	return (0);
}

void	ft_join_arg2(t_tkn *j, t_var *variable, t_tkn *n)
{
	variable->args = NULL;
	while (n && j && !get_redirect_index2(n))
	{
		if (ft_strncmp(n->content, "|", 1) && n->type != 1)
			lst_addback_args(&variable->args, lst_new_args(n->content));
		else
			break ;
		n = n->next;
	}
}

void	join_args3(t_cmd **cmd, t_tkn *i, t_var *variable)
{
	t_tkn	*j;
	t_tkn	*var;
	t_tkn	*n;

	j = i->next;
	var = get_index(j, "|");
	n = j->next;
	variable->args = NULL;
	while (n < var)
	{
		if (!get_redirect_index2(n))
			lst_addback_args(&variable->args, lst_new_args(n->content));
		else
			break ;
		n = n->next;
	}
	lst_addback(cmd, lst_new(j->content, variable->args));
}

void	fill_cmd_files_part2_2(t_tkn *n, t_var *variable)
{
	t_tkn	*tmp2;

	while (n)
	{
		if (get_redirect_index2(n))
		{
			init_flag2(n, variable);
			fill_cmd_files_init(variable, n->next);
			tmp2 = n->next->next;
			while (tmp2 && !get_redirect_index2(tmp2))
			{
				lst_addback_args(&variable->args, lst_new_args(tmp2->content));
				tmp2 = tmp2->next;
			}
		}
		n = n->next;
	}
}
