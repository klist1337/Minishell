/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part9.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 22:20:17 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/21 23:42:47 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	fill_lst_token(char *line, t_lextok *lex_tok, t_tkn **tkn,
	t_settings *settings)
{
	lex_tok->lexer = init_lexer(line);
	lex_tok->token = lexer_get_next_token(lex_tok->lexer, settings);
	while (lex_tok->token)
	{
		lst_addback_tkn(tkn, lst_new_tkn(lex_tok->token->value,
				lex_tok->token->e_type));
		free(lex_tok->token->value);
		free(lex_tok->token);
		lex_tok->token = lexer_get_next_token(lex_tok->lexer, settings);
	}
}

int	check_redirection_error(t_tkn *token)
{
	while (token)
	{
		if (token->type == 8)
		{
			return (1);
			break ;
		}
		token = token->next;
	}
	return (0);
}
