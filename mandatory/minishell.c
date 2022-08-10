/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:33:23 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/30 23:24:21 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_prompt2(t_cmd **commande, t_settings *settings,
	char *line, t_lextok *lex_tok)
{
	t_tkn	*checker;

	add_history(line);
	checker = NULL;
	g_global.sysntax_err = 0;
	checker = main_parser(lex_tok, line, commande, settings);
	if (!checker)
		g_global.sysntax_err = 1;
	g_global.exit_value = 0;
	start_execution(*commande, settings);
	free_cmd(*commande);
	free_l_lextok(lex_tok);
	*commande = NULL;
	free(line);
}

void	show_prompt(t_cmd **commande, t_settings *settings)
{
	char			*line;
	t_lextok		*lex_tok;
	char			**raw;

	while (1)
	{
		lex_tok = malloc(sizeof(t_lextok));
		lex_tok->token = 0;
		lex_tok->lexer = 0;
		line = readline("minishell> ");
		if (!line)
			exit(0);
		raw = ft_split(line, ' ');
		if (!ft_strncmp(line, "", 1) || !raw[0])
		{
			free_matrice(raw);
			free_l_lextok(lex_tok);
			free(line);
			continue ;
		}
		free_matrice(raw);
		show_prompt2(commande, settings, line, lex_tok);
	}
}

int	main(int argc, char **argv, char **envp)
{	
	t_settings		*settings;
	t_cmd			*commande;

	(void)argc;
	(void)argv;
	settings = NULL;
	commande = NULL;
	init(&settings, envp);
	show_prompt(&commande, settings);
	return (0);
}
