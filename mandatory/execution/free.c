/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:11:24 by achedmi           #+#    #+#             */
/*   Updated: 2022/07/29 22:26:57 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	free_l_lextok(t_lextok *lex_tok)
{
	if (lex_tok)
	{
		if (lex_tok->lexer)
		{
			if (lex_tok->lexer->contents)
				free(lex_tok->lexer->contents);
			free(lex_tok->lexer);
		}
		if (lex_tok->token)
			free(lex_tok->token);
		free(lex_tok);
	}
}

void	free_args(t_args *args)
{
	t_args	*tmp;

	tmp = args;
	while (args)
	{
		tmp = args;
		args = args->next;
		free(tmp->content);
		free(tmp);
	}
}

void	free_files(t_file *files)
{
	t_file	*tmp;

	tmp = files;
	while (files)
	{
		tmp = files;
		files = files->next;
		free(tmp->lim);
		free(tmp->name);
		free(tmp);
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free_args(tmp->args);
		free_files(tmp->files);
		free(tmp->commande);
		free_matrice(tmp->m_args);
		free(tmp);
		tmp = NULL;
	}
}
