/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_funct_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 22:34:17 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/18 18:55:44 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"  

t_args	*lst_new_args(char *content)
{
	t_args	*args;

	if (!content)
		return (NULL);
	args = (t_args *)malloc(sizeof(t_args));
	args->content = ft_strdup(content);
	args->next = NULL;
	return (args);
}

t_args	*last_lst_args(t_args *args)
{
	if (!args)
		return (NULL);
	while (args->next)
	{
		args = args->next;
	}
	return (args);
}

void	lst_addback_args(t_args **args, t_args *new)
{
	t_args	*lst;

	if (!args && new)
		return ;
	if (!*args)
		*args = new;
	else
	{
		lst = last_lst_args(*args);
		lst->next = new;
	}
}
