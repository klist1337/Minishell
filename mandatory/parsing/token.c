/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassofi <eassofi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:48:04 by eassofi           #+#    #+#             */
/*   Updated: 2022/07/21 22:18:59 by eassofi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*init_token(char *value, int type)
{
	t_token	*token;

	token = (t_token *) malloc(sizeof(t_token));
	token->value = value;
	token->e_type = type;
	return (token);
}

void	print_token(t_tkn **token)
{
	t_tkn	*tmp;

	tmp = *token;
	while (tmp)
	{
		printf("TOKEN(%s, %d)\n", tmp->content, tmp->type);
		tmp = tmp->next;
	}
}
