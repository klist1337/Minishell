/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:48:53 by achedmi           #+#    #+#             */
/*   Updated: 2022/07/21 19:12:32 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	echo2(t_cmd *commande, char **arguments, int has_next_line, int i)
{
	while (arguments[i])
	{
		ft_putstr_fd(arguments[i], commande->output);
		if (arguments[i + 1])
			ft_putstr_fd(" ", commande->output);
		i++;
	}
	if (has_next_line)
		ft_putstr_fd("\n", commande->output);
}

void	echo(t_cmd *cmd)
{
	int	i;
	int	j;
	int	has_next_line;

	i = 0;
	has_next_line = 1;
	while (cmd->m_args[i] && !ft_strncmp(cmd->m_args[i], "-n", 2))
	{
		j = 1;
		while (cmd->m_args[i][j] == 'n')
			j++;
		if (cmd->m_args[i][j] == '\0')
		{
			has_next_line = 0;
			i++;
		}
		else
			break ;
	}
	echo2(cmd, cmd->m_args, has_next_line, i);
}
