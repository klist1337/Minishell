/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:13:31 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/31 18:42:18 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	string_collect(t_lexer *lexer, char **value)
{
	char	*tmp_value;
	char	*s;

	s = lexer_get_current_char_as_string(lexer);
	s = lexer_get_current_char_as_string(lexer);
	tmp_value = *value;
	*value = ft_strjoin(*value, s);
	free(s);
	free(tmp_value);
	lexer_advance(lexer);
}

char	*replace_val(char *str, t_settings *settings)
{
	char	*item;
	char	*ret;
	char	*sub_str;
	int		i;

	i = -1;
	ret = NULL;
	while (settings->envp[++i])
	{
		item = ft_strchr(settings->envp[i], '=');
		if (item)
		{
			sub_str = ft_substr(settings->envp[i], 0,
					ft_strlen(settings->envp[i]) - ft_strlen(item));
			if (!ft_strncmp(str, sub_str, ft_strlen(str) + 1))
			{
				free(ret);
				ret = ft_strdup(item + 1);
				free(sub_str);
				break ;
			}
			free(sub_str);
		}
	}
	return (ret);
}

void	collect_dollars_211(t_lexer *lexer, char **value, t_settings *settings)
{
	char	*tmp;
	char	*repl;
	char	*s;
	char	*tmp_s;

	while (lexer->c && lexer->c == '$' && lexer->contents[lexer->i + 1])
	{
		repl = ft_calloc(1, sizeof(char));
		s = ft_calloc(1, sizeof(char));
		lexer_advance(lexer);
		while (lexer->c && lexer->c != '$' && !iskeychar(lexer->c))
		{
			tmp = repl;
			tmp_s = s;
			s = lexer_get_current_char_as_string(lexer);
			free(tmp_s);
			repl = ft_strjoin(repl, s);
			free(tmp);
			lexer_advance(lexer);
		}
		free(s);
		freeing(&repl, value, settings);
	}
}

void	collect_dollars_f21(t_lexer *lexer, char **value, t_settings *settings)
{
	char	*s;
	char	*tmp_value;

	collect_dollars_211(lexer, value, settings);
	while (lexer->c && lexer->c != ' ' && lexer->c != '\'' && lexer->c != '"')
	{
		s = lexer_get_current_char_as_string(lexer);
		tmp_value = *value;
		*value = ft_strjoin(*value, s);
		free(s);
		free(tmp_value);
		lexer_advance(lexer);
	}
}

void	lexer_parse_cmd_f2(t_lexer *lexer, char **value,
			t_settings *settings)
{
	char	*tmp_val;
	char	*s;
	t_token	*tmp;

	if (lexer->c != '$' && lexer->c != '"' && lexer->c != '\'')
	{
		tmp_val = *value;
		*value = ft_strjoin(*value, (char []){lexer->c, 0});
		free(tmp_val);
	}
	else if (lexer->c == '"' && lexer->c != '\'')
	{
		lexer_advance(lexer);
		lexer_parse_cmd_f3(lexer, value);
	}
	if (lexer->c == '$')
	{
		tmp = lexer_collect_dollars2(lexer, settings);
		s = tmp->value;
		tmp_val = *value;
		*value = ft_strjoin(*value, s);
		free(s);
		free(tmp_val);
		free(tmp);
	}
}
