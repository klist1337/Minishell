/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:46:42 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/29 16:03:40 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_pipe(char *line)
{
	if (*line == '|')
		return (2);
	while (*line)
	{
		if (*line == '|')
			return (1);
		line++;
	}
	return (0);
}

int	check_redirect(char *line)
{
	if (*line == '|')
		return (2);
	while (*line)
	{
		if (*line == '|')
			return (1);
		line++;
	}
	return (0);
}

int	check_pipe2(t_tkn *token)
{
	while (token)
	{
		if (!ft_strncmp(token->content, "|", 1) && token->type == 1)
			return (1);
		token = token->next;
	}
	return (0);
}

int	check_redirect2(t_tkn *token)
{
	while (token)
	{
		if ((!ft_strncmp(token->content, "<", 1) && token->type == 4)
			|| (!ft_strncmp(token->content, ">", 1) && token->type == 5)
			|| (!ft_strncmp(token->content, "<<", 2) && token->type == 6)
			|| (!ft_strncmp(token->content, ">>", 2) && token->type == 7))
			return (1);
		token = token->next;
	}
	return (0);
}

int	ft_syntax_error(t_tkn *token)
{
	t_var	variable;
	t_tkn	*x;

	init_var(&variable);
	x = last_lst_tkn(token);
	if (!ft_strncmp(token->content, "|", 1)
		&& token->type == 1)
	{
		print_error("syntax error near unexpected token `|'\n");
		g_global.exit_value = 1;
		return (1);
	}
	else if (!ft_strncmp(x->content, "|", 1) && x->type == 1)
	{
		print_error("syntax error \n");
		g_global.exit_value = 1;
		return (1);
	}
	return (0);
}
