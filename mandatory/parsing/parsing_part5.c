/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:52:45 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/31 18:46:20 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_flag2(t_tkn *i, t_var *variable)
{
	if (!ft_strncmp(i->content, "<<", 2) && i->type == 6)
		variable->flag = 2;
	else if (!ft_strncmp(i->content, ">>", 2) && i->type == 7)
		variable->flag = 3;
	else if (!ft_strncmp(i->content, "<", 1) && i->type == 4)
		variable->flag = 0;
	else if (!ft_strncmp(i->content, ">", 1) && i->type == 5)
		variable->flag = 1;
	else if (i->type == 8)
		variable->flag = -1;
}

void	fill_cmd_files_init(t_var *variable, t_tkn *j)
{
	if (variable->flag == 2)
		variable->lim = j->content;
	else
		variable->lim = 0;
	lst_addback_f(&variable->f, lst_new_f(j->content,
			variable->flag, variable->lim));
}

int	check_another_red(t_tkn *token)
{
	while (token)
	{
		if (get_redirect_index2(token))
		{
			return (1);
			break ;
		}
		token = token->next;
	}
	return (0);
}

void	no_cmd_after_part2_2_1(t_cmd **cmd, t_tkn **tmp, t_var *variable)
{
	t_tkn	*n;

	while (*tmp && get_redirect_index2(*tmp))
	{	
		init_flag2(*tmp, variable);
		fill_cmd_files_init(variable, (*tmp)->next);
		n = (*tmp)->next->next;
		if ((n && get_redirect_index2(n)))
		{
			lst_addback(cmd, lst_new_cmd(NULL, NULL, variable->f));
			variable->f = NULL;
		}
		n = (*tmp)->next;
		*tmp = (*tmp)->next->next;
	}
}

void	iterator(t_tkn **tmp, t_var *variable)
{
	t_tkn	*n;

	while (tmp)
	{
		while (*tmp && !get_redirect_index2(*tmp))
		{
			lst_addback_args(&variable->args, lst_new_args((*tmp)->content));
			*tmp = (*tmp)->next;
		}
		while (*tmp && get_redirect_index2(*tmp))
		{
			init_flag2(*tmp, variable);
			fill_cmd_files_init(variable, (*tmp)->next);
			*tmp = (*tmp)->next->next;
		}
		if (*tmp == NULL)
			break ;
		n = *tmp;
		*tmp = n;
	}
}
