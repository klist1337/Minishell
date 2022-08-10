/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 18:29:53 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/21 22:09:43 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_print_files(t_file **file)
{
	t_file	*tmp;
	int		i;

	i = 0;
	tmp = *file;
	while (tmp)
	{
		printf("file[%d] = %s, type = %d , lim =%s\n",
			i, tmp->name, tmp->type, tmp->lim);
		tmp = tmp->next;
		i++;
	}
}

void	ft_print_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	tmp = *cmd;
	while (tmp)
	{
		printf("CMD[%d] =%s\n", i, tmp->commande);
		ft_print_arg(&tmp->args);
		ft_print_files(&tmp->files);
		tmp = tmp->next;
		i++;
	}
}

void	ft_print_arg(t_args **args)
{
	t_args	*tmp;
	int		i;

	i = 0;
	tmp = *args;
	while (tmp)
	{
		printf("ARG[%d] =%s\n", i, tmp->content);
		tmp = tmp->next;
		i++;
	}
}

void	init_first_cmd_null(t_cmd **cmd)
{
	(*cmd)->commande = NULL;
	(*cmd)->args = NULL;
	(*cmd)->input = 0;
	(*cmd)->output = 1;
	(*cmd)->next = NULL;
	(*cmd)->files = NULL;
}

void	print_error(char *s)
{
	write(2, s, ft_strlen(s));
}
