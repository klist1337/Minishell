/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:46:49 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/21 23:04:28 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_tkn	*get_index_end(t_tkn *i)
{
	while (i)
		i = i->next;
	return (i);
}

t_tkn	*get_index(t_tkn *j, char *s)
{
	while (j)
	{
		if (!ft_strncmp(j->content, s, ft_strlen(s)) && j->type == 1)
		{
			return (j);
			break ;
		}
		j = j->next;
	}
	return (0);
}

t_tkn	*check_next_pipe(t_tkn *token)
{
	t_tkn	*tmp;

	tmp = token;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "|", 1) && tmp->type == 1)
		{
			return (tmp);
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	get_reverse_index(char **args, int i, char *s)
{
	while (args[i])
	{
		if (!ft_strncmp(args[i], s, ft_strlen(s)))
		{
			return (i);
			break ;
		}
		i--;
	}
	return (0);
}

int	get_redirect_index(char *args)
{
	if (!ft_strncmp(args, "<", 1))
		return (1);
	else if (!ft_strncmp(args, ">", 1))
		return (2);
	else if (!ft_strncmp(args, "<<", 2))
		return (3);
	else if (!ft_strncmp(args, ">>", 2))
		return (4);
	return (0);
}
