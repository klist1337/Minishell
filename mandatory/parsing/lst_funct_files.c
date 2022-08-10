/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_funct_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 00:34:30 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/18 18:57:03 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_file	*lst_new_f(char *name, int type, char *lim)
{
	t_file	*file;

	if (!name)
		return (NULL);
	file = (t_file *)malloc(sizeof(t_file));
	file->name = ft_strdup(name);
	file->type = type;
	file->lim = ft_strdup(lim);
	file->next = NULL;
	return (file);
}

t_file	*last_lst_f(t_file *file)
{
	if (!file)
		return (NULL);
	while (file->next)
	{
		file = file->next;
	}
	return (file);
}

void	lst_addback_f(t_file **file, t_file *new)
{
	t_file	*lst;

	if (!file && new)
		return ;
	if (!*file)
	{
		*file = new;
	}
	else
	{
		lst = last_lst_f(*file);
		lst->next = new;
	}
}
