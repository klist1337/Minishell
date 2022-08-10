/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 21:40:02 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/29 22:40:23 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	collect_string3_f1(t_lexer *lexer,	char **value, char **s)
{
	char	*tmp_s;
	char	*tmp_value;

	while (ft_isalnum(lexer->c) || iskeychar(lexer->c)
		|| lexer->c == ' ' || lexer->c == '|' || lexer->c == '<'
		|| lexer->c == '>' || lexer->c == '$' || lexer->c == '"')
	{
		tmp_s = *s;
		*s = lexer_get_current_char_as_string(lexer);
		free(tmp_s);
		tmp_value = *value;
		*value = ft_strjoin(*value, *s);
		free(tmp_value);
		lexer_advance(lexer);
	}
}

t_token	*lexer_collect_string3(t_lexer *lexer)
{
	char	*s;
	char	*value;

	value = ft_calloc(1, sizeof(char));
	s = NULL;
	while (lexer->c == '\'')
	{
		lexer_advance((lexer));
		collect_string3_f1(lexer, &value, &s);
		lexer_advance(lexer);
	}
	free(s);
	return (init_token(value, TOKEN_CMD));
}

void	collect_string_f4(char **value)
{
	char	*s;
	char	*tmp_s;
	char	*tmp_value;

	s = ft_strdup("\'");
	tmp_s = s;
	s = ft_strjoin(s, *value);
	free(tmp_s);
	free(*value);
	*value = ft_strdup("\'");
	tmp_value = *value;
	*value = ft_strjoin(s, *value);
	free(tmp_value);
	free(s);
}

t_token	*get_next_token2_1(t_lexer *lexer, char next, t_settings *settings)
{
	char	*value;

	value = NULL;
	if ((lexer->c == '$' && (!next || iskeychar(next))) || (lexer->c == '$'
			&& (ft_isalnum(next) && next != '?' && next != '#')))
		return (lexer_collect_dollars2(lexer, settings));
	else if (lexer->c == '>')
	{
		value = ft_strdup(">");
		return (lexer_advance_with_token(lexer
				, init_token(value, TOKEN_GREAT)));
	}
	else if (ft_isprint(lexer->c))
		return (lexer_get_is_printable(lexer));
	else
		return (lexer_advance_with_token(lexer, init_token(0, TOKEN_EOF)));
}

t_token	*lexer_get_next_token2(t_lexer *lexer, char next, t_settings *settings)
{
	char	*value;

	value = NULL;
	if (lexer->c == '|')
	{
		value = ft_strdup("|");
		return (lexer_advance_with_token(lexer, init_token(value, TOKEN_PIPE)));
	}
	else if (lexer->c == '<' && next != '<')
	{
		value = ft_strdup("<");
		return (lexer_advance_with_token(lexer,
				init_token(value, TOKEN_LESS)));
	}
	else
		return (get_next_token2_1(lexer, next, settings));
}
