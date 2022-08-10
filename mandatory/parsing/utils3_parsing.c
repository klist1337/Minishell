/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:46:36 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/29 15:18:06 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_next_red(char **args, int i)
{
	while (args[i])
	{
		if (get_redirect_index(args[i]))
		{
			return (i);
			break ;
		}
		i++;
	}
	return (0);
}

void	init_var(t_var *var)
{
	var->s = NULL;
	var->args = NULL;
	var->n = 0;
	var->flag = 0;
	var->flg = 0;
	var->flg2 = 0;
	var->var = 0;
	var->x = 0;
	var->f = NULL;
	var->lim = NULL;
}

int	get_redirect_index2(t_tkn *token)
{
	if (token)
	{
		if (!ft_strncmp(token->content, "<", 1) && token->type == 4)
			return (1);
		else if (!ft_strncmp(token->content, ">", 1) && token->type == 5)
			return (2);
		else if (!ft_strncmp(token->content, "<<", 2) && token->type == 6)
			return (3);
		else if (!ft_strncmp(token->content, ">>", 2) && token->type == 7)
			return (4);
	}
	return (0);
}
