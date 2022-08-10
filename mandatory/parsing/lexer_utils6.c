/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 01:15:23 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/31 18:42:41 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*lexer_get_heredoc(t_lexer *lexer)
{
	char	*value;
	char	*tmp_value;
	int		count;

	value = ft_calloc(1, sizeof(char));
	count = 0;
	while (lexer->c == '<')
	{
		tmp_value = value;
		value = ft_strjoin(value, (char []){lexer->c, 0});
		free(tmp_value);
		count++;
		lexer_advance(lexer);
	}
	if (count == 2)
		return (init_token(value, TOKEN_HEREDOC));
	else
		return (init_token(value, TOKEN_ERROR));
}

t_token	*lexer_get_is_printable(t_lexer *lexer)
{
	char	*value;
	char	*tmp_value;

	value = ft_calloc(1, sizeof(char));
	while (ft_isprint(lexer->c))
	{
		tmp_value = value;
		value = ft_strjoin(value, (char []){lexer->c, 0});
		free(tmp_value);
		lexer_advance(lexer);
	}
	return (init_token(value, TOKEN_CMD));
}
