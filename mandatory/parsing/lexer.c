/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:20:22 by eassofi           #+#    #+#             */
/*   Updated: 2022/08/02 11:01:19 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*collect_string(t_lexer *lexer, char *s)
{
	char	*tmp_s;
	char	*tmp_value;
	char	*value;

	value = ft_calloc(1, 1);
	while (ft_isalnum(lexer->c) || iskeychar(lexer->c)
		|| lexer->c == ' ' || lexer->c == '|' || lexer->c == '<'
		|| lexer->c == '>' || lexer->c == '$' || lexer->c == '\''
		|| lexer->c == '"' )
	{
		tmp_s = s;
		s = lexer_get_current_char_as_string(lexer);
		free(tmp_s);
		tmp_value = value;
		if (!ft_strncmp(s, "\"", 1))
		{
			lexer_advance(lexer);
			continue ;
		}
		value = ft_strjoin(value, s);
		free(tmp_value);
		lexer_advance(lexer);
	}
	free(s);
	return (value);
}

char	*collect_string2(t_lexer *lexer, char *s)
{
	char	*tmp_s;
	char	*tmp_value;
	char	*value;

	value = ft_calloc(1, 1);
	while ((ft_isalnum(lexer->c) || iskeychar(lexer->c)
			|| lexer->c == ' ' || lexer->c == '|' || lexer->c == '<'
			|| lexer->c == '>' || lexer->c == '$') && lexer->c != '\'')
	{
		tmp_s = s;
		s = lexer_get_current_char_as_string(lexer);
		free(tmp_s);
		tmp_value = value;
		value = ft_strjoin(value, s);
		free(tmp_value);
		lexer_advance(lexer);
	}
	free(s);
	return (value);
}

t_token	*lexer_get_g_great(t_lexer *lexer)
{
	char	*value;
	char	*tmp_value;
	int		count;

	value = ft_calloc(1, sizeof(char));
	count = 0;
	while (lexer->c == '>')
	{
		tmp_value = value;
		value = ft_strjoin(value, (char []){lexer->c, 0});
		free(tmp_value);
		count++;
		lexer_advance(lexer);
	}
	if (count == 2)
		return (init_token(value, TOKEN_G_GREAT));
	else
		return (init_token(value, TOKEN_ERROR));
}

t_token	*lexer_collect_string(t_lexer *lexer, t_settings *settings)
{
	char	*value;
	char	*s;
	char	next;
	int		flag;

	value = ft_calloc(1, sizeof(char));
	flag = 0;
	s = NULL;
	while (lexer->c == '"')
	{
		lexer_advance(lexer);
		if (lexer->c == '\'')
		{
			flag = 1;
			lexer_advance(lexer);
		}
		next = lexer->contents[lexer->i + 1];
		if (lexer->c == '$')
			collect_string_f2(lexer, next, &value, settings);
		else if (lexer->c != '$' && lexer->c)
			collect_string_f3(lexer, &value);
	}
	if (flag == 1)
		collect_string_f4(&value);
	return (init_token(value, TOKEN_DOLLARS));
}

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}
