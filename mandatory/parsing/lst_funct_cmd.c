/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_funct_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 00:33:57 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/20 21:05:50 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd	*lst_new(char *commande, t_args *args)
{
	t_cmd	*cmd;

	if (!commande)
		return (NULL);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->commande = ft_strdup(commande);
	cmd->args = args;
	cmd->input = 0;
	cmd->output = 1;
	cmd->next = NULL;
	cmd->files = NULL;
	return (cmd);
}

t_cmd	*last_lst(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
	{
		cmd = cmd->next;
	}
	return (cmd);
}

void	lst_addback(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*lst;

	if (!cmd && new)
		return ;
	if (!*cmd)
		*cmd = new;
	else
	{
		lst = last_lst(*cmd);
		lst->next = new;
	}
}

t_cmd	*lst_new_cmd(char *commande, t_args *args, t_file *files)
{
	t_cmd	*cmd;

	if (!commande && !files)
		return (NULL);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->commande = ft_strdup(commande);
	cmd->args = args;
	cmd->input = 0;
	cmd->output = 1;
	cmd->next = NULL;
	cmd->files = files;
	return (cmd);
}
