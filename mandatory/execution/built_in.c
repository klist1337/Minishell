/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:29:31 by achedmi           #+#    #+#             */
/*   Updated: 2022/07/29 14:54:57 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_builtins(t_cmd *cmd)
{
	if (cmd->commande)
	{
		if (!ft_strncmp(cmd->commande, "echo", ft_strlen("echo") + 1))
			return (1);
		else if (!ft_strncmp(cmd->commande, "export", ft_strlen("exort") + 1))
			return (2);
		else if (!ft_strncmp(cmd->commande, "unset", ft_strlen("unset") + 1))
			return (3);
		else if (!ft_strncmp(cmd->commande, "env", ft_strlen("env") + 1))
			return (4);
		else if (!ft_strncmp(cmd->commande, "pwd", ft_strlen("pwd") + 1))
			return (5);
		else if (!ft_strncmp(cmd->commande, "cd", ft_strlen("cd") + 1))
			return (6);
		else if (!ft_strncmp(cmd->commande, "exit", ft_strlen("exit") + 1))
			return (7);
		else
			return (0);
	}
	return (-1);
}

void	exe_builtins(t_cmd *cmd, t_settings *settings, int builtin_nubmer)
{
	if (builtin_nubmer == 1)
		echo(cmd);
	else if (builtin_nubmer == 2)
	{
		if (cmd->m_args[0])
			export(settings, cmd->m_args);
		else
			empty_export(settings->envp, cmd);
	}
	else if (builtin_nubmer == 3)
		unset(settings, cmd->m_args);
	else if (builtin_nubmer == 4)
		env_cmd(settings->envp, cmd);
	else if (builtin_nubmer == 5)
		current_dir(settings, cmd);
	else
		change_directory(settings, cmd);
}

void	is_built_in_with_pipe(t_cmd *cmd, t_settings *settings,
	int builtin_nubmer, int pipe)
{
	int	id;
	int	status;

	if (pipe == 1)
	{
		id = fork();
		if (id == 0)
		{
			exe_builtins(cmd, settings, builtin_nubmer);
			close_fd(cmd->input);
			close_fd(cmd->output);
			exit(g_global.exit_value);
		}
		waitpid(id, &status, 0);
		g_global.exit_value = WEXITSTATUS(status);
	}
	else
		exe_builtins(cmd, settings, builtin_nubmer);
}

int	check_built_ins(int is_built_in, t_cmd *tmp_cmd,
			t_settings *settings, int pipe)
{
	if (is_built_in > 0)
	{
		if (is_built_in == 7 && costum_exit(tmp_cmd))
			return (1);
		is_built_in_with_pipe(tmp_cmd, settings, is_built_in, pipe);
	}
	else
		forking(tmp_cmd, settings);
	return (0);
}
