/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:52:37 by achedmi           #+#    #+#             */
/*   Updated: 2022/07/31 19:45:19 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	change_directory2(char *new_path, t_settings *settings)
{
	if (chdir(new_path) != 0)
	{
		perror(new_path);
		free(new_path);
		g_global.exit_value = 1;
		return ;
	}
	else
	{
		free(settings->current_dir);
		settings->current_dir = getcwd(NULL, 0);
		if (!settings->current_dir)
		{
			perror(new_path);
			g_global.exit_value = 1;
			free(new_path);
			return ;
		}
	}
	change_value_of_key(settings->envp, "PWD", settings->current_dir);
	free(new_path);
}

void	change_directory(t_settings *settings, t_cmd *cmd)
{
	char	*home;
	char	*new_path;
	char	*path;

	path = cmd->m_args[0];
	change_value_of_key(settings->envp, "OLDPWD", settings->current_dir);
	new_path = ft_strdup(path);
	if (!path)
	{
		home = get_value(settings->envp, "HOME");
		if (home)
			new_path = ft_strdup(home);
		else if (is_valid_key(settings->envp, "HOME"))
			new_path = getcwd(NULL, 0);
		else
		{
			ft_putstr_fd("HOME not set\n", 2);
			g_global.exit_value = 1;
			return ;
		}
	}
	else if (!ft_strncmp(path, "", 1))
		return ;
	change_directory2(new_path, settings);
}
