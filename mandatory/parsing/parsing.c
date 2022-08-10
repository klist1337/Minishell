/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 22:27:16 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/31 18:52:34 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	fill_next_cmd(t_tkn *token, t_cmd **cmd)
{
	t_tkn	*i;
	t_tkn	*x;
	t_var	variable;

	i = token ;
	init_var(&variable);
	while (i)
	{
		if (!ft_strncmp(i->content, "|", 1) && i->type == 1
			&& i->next)
		{
			x = check_next_pipe(i->next);
			if (x)
			{
				if (x->next)
					fill_next_cmd_part1(cmd, i->next);
				else
					fill_next_cmd_part2(cmd, i->next);
			}
			else
				fill_next_cmd_part3(cmd, i->next);
		}
		i = i->next;
	}
}

int	main_parser1(t_cmd **cmd, t_tkn *token)
{
	t_var	variable;

	variable.x = ft_syntax_error(token);
	if (variable.x == 1)
		return (1);
	parse_cmd_pipe(token, cmd);
	return (0);
}

int	main_parsing(t_cmd **cmd, t_tkn *tkn, t_var variable)
{
	if (!check_redirect2(tkn))
	{
		variable.x = main_parser1(cmd, tkn);
		if (variable.x == 1)
		{
			free_token_lst(tkn);
			return (1);
		}
	}
	else if (check_pipe2(tkn) && check_redirect2(tkn))
	{
		variable.x = main_parser2(cmd, tkn);
		if (variable.x == 1)
		{
			free_token_lst(tkn);
			return (1);
		}
	}
	return (0);
}

int	second_part(t_cmd **cmd, t_tkn *tkn, t_var variable)
{
	if (!check_pipe2(tkn))
	{
		variable.x = parsing_simple_cmd(tkn, cmd);
		if (variable.x)
		{
			free_token_lst(tkn);
			return (1);
		}
	}
	else if (check_pipe2(tkn))
	{
		variable.x = main_parsing(cmd, tkn, variable);
		if (variable.x == 1)
			return (1);
	}
	return (0);
}

t_tkn	*main_parser(t_lextok *lex_tok, char *line, t_cmd **cmd,
				t_settings *settings)
{
	t_var	variable;
	t_tkn	*tkn;

	init_var(&variable);
	tkn = NULL;
	fill_lst_token(line, lex_tok, &tkn, settings);
	if (check_redirection_error(tkn))
	{
		variable.x = redirection_error(tkn, cmd);
		if (variable.x == 1)
		{
			free_token_lst(tkn);
			return (NULL);
		}
	}
	else
	{
		variable.x = second_part(cmd, tkn, variable);
		if (variable.x == 1)
			return (NULL);
	}
	free_token_lst(tkn);
	return (tkn);
}
