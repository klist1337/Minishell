/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:55:44 by achedmi           #+#    #+#             */
/*   Updated: 2022/07/28 23:14:48 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	current_dir(t_settings *settings, t_cmd *cmd)
{
	if (!settings->current_dir)
	{
		perror("");
		g_global.exit_value = 1;
	}
	else
	{
		if (cmd->args && !ft_strncmp(cmd->args->content, "-", 1)
			&& ft_strlen(cmd->args->content) > 1)
		{
			ft_putstr_fd("invalid option\n", 1);
			g_global.exit_value = 1;
			return ;
		}
		ft_putstr_fd(settings->current_dir, cmd->output);
		ft_putstr_fd("\n", cmd->output);
	}
}
