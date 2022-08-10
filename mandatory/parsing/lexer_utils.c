/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:11:54 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/29 10:31:46 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*init_lexer(char *contents)
{
	t_lexer	*lexer;

	lexer = (t_lexer *) malloc(sizeof(t_lexer));
	lexer->contents = ft_strdup(contents);
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c && lexer->i < ft_strlen(lexer->contents))
	{
		lexer->i++;
		lexer->c = lexer->contents[lexer->i];
	}
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\t' || lexer->c == 10
		|| lexer->c == 13)
		lexer_advance(lexer);
}

int	iskeychar(char c)
{
	if (c == '!' || c == '#' || c == '%'
		|| c == '&' || c == '(' || c == ')'
		|| c == '*' || c == '+' || c == ','
		|| c == '-' || c == '.' || c == '/'
		|| c == ':' || c == ';' || c == '='
		|| c == '?' || c == '@' || c == '['
		|| c == '\\' || c == ']' || c == '^'
		|| c == '_' || c == '`' || c == '{'
		|| c == '}' || c == '~')
		return (1);
	return (0);
}

char	*lexer_get_current_char_as_string(t_lexer *lexer)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}
