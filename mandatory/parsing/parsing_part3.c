/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:49:58 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/30 18:26:42 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_error2(t_tkn *i)
{
	if (get_redirect_index2(i)
		&& !ft_strncmp(i->next->content, "|", 1) && i->next->type == 1)
	{
		print_error("syntax error\n");
		g_global.exit_value = 1;
		return (1);
	}
	return (0);
}

void	init_flag(t_tkn *i, int *flag)
{
	if (!ft_strncmp(i->content, "<<", 2) && i->type == 6)
		*flag = 2;
	else if (!ft_strncmp(i->content, ">>", 2) && i->type == 7)
		*flag = 3;
	else if (!ft_strncmp(i->content, "<", 1) && i->type == 4)
		*flag = 0;
	else if (!ft_strncmp(i->content, ">", 1) && i->type == 5)
		*flag = 1;
}

void	ft_join_arg(t_tkn *i, t_tkn *token, t_var *variable, t_cmd **cmd)
{
	t_tkn	*n;

	n = token->next;
	variable->args = NULL;
	while (n < i)
	{
		lst_addback_args(&variable->args, lst_new_args(n->content));
		n = n->next;
	}
	if (!get_redirect_index2(token))
		lst_addback(cmd, lst_new(token->content, variable->args));
}

void	init_first_file(t_file **file)
{
	*file = (t_file *)malloc(sizeof(t_file));
	(*file)->lim = 0;
	(*file)->name = 0;
	(*file)->type = 0;
	(*file)->next = NULL;
}
