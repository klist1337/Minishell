/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:37:25 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/30 20:15:56 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_token_lst(t_tkn *token)
{
	t_tkn	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->content);
		free(tmp);
	}
}

void	free_arg_lst(t_args *args)
{
	t_args	*tmp;

	while (args)
	{
		tmp = args;
		args = args->next;
		free(tmp);
	}
}

void	free_files_lst(t_file *file)
{
	t_file	*tmp;

	while (file)
	{
		tmp = file;
		free(tmp);
		file = file->next;
	}
}

void	free_cmd_lst(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		free(tmp);
		cmd = cmd->next;
	}
}

void	freeing(char **repl, char **value, t_settings *settings)
{
	char	*tmp;
	char	*tmp_value;

	tmp_value = *value;
	tmp = *repl;
	*repl = replace_val(*repl, settings);
	free(tmp);
	*value = ft_strjoin(*value, *repl);
	free(tmp_value);
	free(*repl);
}
