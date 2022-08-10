/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 21:44:28 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/30 21:13:42 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*lexer_collect_string2(t_lexer *lexer)
{
	char	*s;
	char	*value;
	char	*tmp_value;

	value = ft_calloc(1, sizeof(char));
	s = NULL;
	while (lexer->c == '"')
	{
		lexer_advance((lexer));
		tmp_value = value;
		value = collect_string(lexer, s);
		free(tmp_value);
		lexer_advance(lexer);
	}
	return (init_token(value, TOKEN_CMD));
}

t_token	*get_next_token1(t_lexer *lexer, char next, char n_next,
						t_settings *settings)
{
	if ((ft_isalnum(lexer->c) || iskeychar(lexer->c))
		|| ((ft_isalnum(lexer->c) || iskeychar(lexer->c)) && next == '$'))
		return (lexer_parse_cmd(lexer, settings));
	else if ((lexer->c == '"' && next == '$')
		|| (lexer->c == '"' && next == '\'' && n_next == '$'))
		return (lexer_collect_string(lexer, settings));
	else if (lexer->c == '"' && next != '$')
		return (lexer_collect_string2(lexer));
	else if (lexer->c == '\''
		|| (lexer->c == '\'' && next == '"' && n_next == '$'))
		return (lexer_collect_string3(lexer));
	else if (lexer->c == '<' && next == '<')
		return (lexer_get_heredoc(lexer));
	else if (lexer->c == '>' && next == '>')
		return (lexer_get_g_great(lexer));
	else
		return (lexer_get_next_token2(lexer, next, settings));
}

t_token	*lexer_get_next_token(t_lexer *lexer, t_settings *settings)
{
	char	next;
	char	n_next;

	while (lexer->c && lexer->i < ft_strlen(lexer->contents))
	{
		next = lexer->contents[lexer->i + 1];
		n_next = lexer->contents[lexer->i + 2];
		if (lexer->c == ' ' || lexer->c == '\t' || lexer->c == 10
			|| lexer->c == 13)
			lexer_skip_whitespace(lexer);
		else
			return (get_next_token1(lexer, next, n_next, settings));
	}
	return (NULL);
}

void	collect_string_f2(t_lexer *lexer, char next, char **value,
	t_settings *settings)
{
	char	*s;
	char	*tmp_value;

	s = NULL;
	if ((lexer->c == '$' && iskeychar(next) && next != '?' && next != '#')
		|| (lexer->c == '$' && next == '\"'))
	{
		free(*value);
		*value = collect_string(lexer, s);
		lexer_advance(lexer);
	}
	else if (lexer->c == '$' && ft_isalnum(next) && next != '?' && next != '#')
	{
		lexer_advance(lexer);
		free(*value);
		*value = collect_string2(lexer, s);
		lexer_advance(lexer);
		tmp_value = *value;
		*value = replace_val(*value, settings);
		free(tmp_value);
	}
}

void	collect_string_f3(t_lexer *lexer, char **value)
{
	char	*s;

	s = NULL;
	free(*value);
	*value = collect_string(lexer, s);
	lexer_advance(lexer);
}
