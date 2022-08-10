/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:54:28 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/30 19:41:29 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*collect_dollars_f1(t_lexer *lexer, char *value)
{
	char	*s;
	char	*tmp_value;

	while (lexer->c && lexer->c != ' ')
	{
		s = lexer_get_current_char_as_string(lexer);
		tmp_value = value;
		value = ft_strjoin(value, s);
		free(s);
		free(tmp_value);
		lexer_advance(lexer);
	}
	return (init_token(value, TOKEN_DOLLARS));
}

t_token	*collect_dollars_f2(char *value, t_lexer *lexer, t_settings *settings)
{
	char	*s;
	char	*tmp_value;

	while (lexer->c && lexer->c != ' ' && lexer->c != '"' && lexer->c != '\''
		&& !iskeychar(lexer->c) && lexer->c != '$')
	{
		s = lexer_get_current_char_as_string(lexer);
		tmp_value = value;
		value = ft_strjoin(value, s);
		free(s);
		free(tmp_value);
		lexer_advance(lexer);
	}
	tmp_value = value;
	value = replace_val(value, settings);
	free(tmp_value);
	if (lexer->c == '\'' || lexer->c == '"')
		lexer_advance(lexer);
	collect_dollars_f21(lexer, &value, settings);
	return (init_token(value, TOKEN_DOLLARS));
}

void	token_dollars2(int count, char **value)
{
	char	*tmp_value;
	char	*s;

	while (count--)
	{
		s = ft_strdup("?");
		tmp_value = *value;
		*value = ft_strjoin(*value, s);
		free(tmp_value);
		free(s);
	}
}

t_token	*token_dollars(t_lexer *lexer, char **value)
{
	char	*tmp_value;
	int		count;

	count = -1;
	while (lexer->c && lexer->c != ' ')
	{
		if (lexer->c == '?')
			count++;
		lexer_advance(lexer);
	}
	tmp_value = *value;
	*value = ft_itoa(g_global.exit_value);
	free(tmp_value);
	if (count > 0)
		token_dollars2(count, value);
	return (init_token(*value, TOKEN_DOLLARS));
}

t_token	*lexer_collect_dollars2(t_lexer *lexer, t_settings *settings)
{
	char	*value;
	char	next;
	int		count;

	value = ft_calloc(1, sizeof(char));
	count = 0;
	next = lexer->contents[lexer->i + 1];
	if ((lexer->c == '$' && iskeychar(next) && next != '?' && next != '#')
		|| (lexer->c == '$' && next == '\0'))
		return (collect_dollars_f1(lexer, value));
	else if (lexer->c == '$' && ft_isalnum(next) && next != '?' && next != '#')
	{
		lexer_advance(lexer);
		return (collect_dollars_f2(value, lexer, settings));
	}
	else
		return (token_dollars(lexer, &value));
}
