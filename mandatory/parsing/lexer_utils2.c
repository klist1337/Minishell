/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:18:40 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/31 02:27:10 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	lexer_parse_cmd_f3(t_lexer *lexer, char **value)
{
	char	*tmp_val;

	while (lexer->c && lexer->c != '"')
	{
		tmp_val = *value;
		*value = ft_strjoin(*value, (char []){lexer->c, 0});
		free(tmp_val);
		lexer_advance(lexer);
	}
}

void	lexer_parse_cmd_f12(t_lexer *lexer, char **s, int *flag)
{
	char	*tmp_s;

	if (lexer->c == '"' || lexer->c == '\'')
	{
		if (lexer->c == '"')
		{
			*s = ft_calloc(1, sizeof(char));
			lexer_advance(lexer);
			lexer_advance(lexer);
			*flag = 1;
			while (lexer->c && lexer->c != '"')
			{
				tmp_s = *s;
				*s = ft_strjoin(*s, (char []){lexer->c, 0});
				free(tmp_s);
				lexer_advance(lexer);
			}
			lexer_advance(lexer);
		}
		else
			lexer_advance(lexer);
	}
}

void	lexer_parse_cmd_f13(t_lexer *lexer, char **value, int *flag)
{
	char	*tmp;

	if (*flag == 0)
	{
		tmp = *value;
		*value = ft_strjoin(*value, (char []){lexer->c, 0});
		free(tmp);
		lexer_advance(lexer);
	}
}

void	lexer_parse_cmd_f1(t_lexer *lexer, char **value, t_settings *settings)
{
	int		flag;
	char	*s;
	char	*tmp_s;
	char	*tmp;

	flag = 0;
	s = NULL;
	while (lexer->c)
	{
		lexer_parse_cmd_f12(lexer, &s, &flag);
		if (flag == 1)
		{
			tmp_s = s;
			s = replace_val(s, settings);
			free(tmp_s);
			tmp = *value;
			*value = ft_strjoin(*value, s);
			free(tmp);
			free(s);
		}
		lexer_parse_cmd_f13(lexer, value, &flag);
	}
}

t_token	*lexer_parse_cmd(t_lexer *lexer, t_settings *settings)
{
	char	*value;

	value = ft_calloc(1, sizeof(char));
	while (ft_isalnum(lexer->c) || iskeychar(lexer->c)
		|| lexer->c == '"' || lexer->c == '\'' || lexer->c == '$')
	{
		if (lexer->c == '=' && (lexer->contents[lexer->i + 1] == '"'
				|| lexer->contents[lexer->i + 1] == '\'')
			&& lexer->contents[lexer->i + 2] == '$')
			lexer_parse_cmd_f1(lexer, &value, settings);
		lexer_parse_cmd_f2(lexer, &value, settings);
		lexer_advance(lexer);
	}
	return (init_token(value, TOKEN_CMD));
}
