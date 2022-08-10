/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_funct_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:17:12 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/20 21:06:38 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_tkn	*lst_new_tkn(char *content, int value)
{
	t_tkn	*tkn;

	if (!content)
		return (NULL);
	tkn = (t_tkn *)malloc(sizeof(t_tkn));
	tkn->content = ft_strdup(content);
	tkn->type = value;
	tkn->next = NULL;
	return (tkn);
}

t_tkn	*last_lst_tkn(t_tkn *tkn)
{
	if (!tkn)
		return (NULL);
	while (tkn->next)
	{
		tkn = tkn->next;
	}
	return (tkn);
}

void	lst_addback_tkn(t_tkn **tkn, t_tkn *new)
{
	t_tkn	*lst;

	if (!tkn && new)
		return ;
	if (!*tkn)
		*tkn = new;
	else
	{
		lst = last_lst_tkn(*tkn);
		lst->next = new;
	}
}
