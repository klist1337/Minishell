/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:44:17 by achedmi           #+#    #+#             */
/*   Updated: 2022/07/31 19:05:53 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	waiting(t_cmd *cmds)
{
	t_cmd	*cmd;
	int		status;
	int		tmp;
	int		built_in;

	cmd = cmds;
	status = 0;
	tmp = g_global.exit_value;
	while (cmd)
	{
		built_in = is_builtins(cmd);
		signal(SIGQUIT, sig_handler);
		waitpid(cmd->id, &status, 0);
		if (WIFEXITED(status) && !built_in)
			tmp = WEXITSTATUS(status);
		if (!WIFEXITED(status) && !built_in)
			tmp = g_global.status;
		if (!WIFEXITED(status) && built_in)
			tmp = g_global.exit_value;
		cmd = cmd->next;
	}
	if (cmds)
		g_global.exit_value = tmp;
	if (cmds && g_global.sysntax_err)
		g_global.exit_value = g_global.sysntax_err;
}

void	executing(t_cmd *cmds, t_settings *settings)
{
	char	**full_cmd;
	char	*error;
	char	*line;
	char	**new_env;

	if (cmds->commande)
	{
		full_cmd = add_cmd_to_args(cmds);
		line = check_acces(settings->envp, cmds->commande);
		new_env = just_env(settings);
		if (line)
			execve(line, full_cmd, new_env);
	}
	else
		exit(0);
	error = ft_strjoin(strerror(errno), "\n");
	write(2, error, ft_strlen(error));
	free(error);
	exit(127);
}

void	forking(t_cmd *cmd, t_settings *settings)
{
	g_global.is_main = 0;
	cmd->id = fork();
	if (cmd->id == 0)
	{
		set_vquit(28);
		dup2(cmd->input, 0);
		dup2(cmd->output, 1);
		close_fd(cmd->input);
		close_fd(cmd->output);
		if (cmd->next)
			close_fd(cmd->next->input);
		executing(cmd, settings);
	}
}

int	start_execution2(t_cmd *tmp_cmd, t_settings *settings, int pipe)
{
	if (open_files(tmp_cmd))
	{
		g_global.exit_value = 1;
		close_fd(tmp_cmd->input);
		close_fd(tmp_cmd->output);
		return (1);
	}
	if (g_global.exit_value == 1)
	{
		close_fd(tmp_cmd->input);
		close_fd(tmp_cmd->output);
		return (-1);
	}
	if (check_built_ins(is_builtins(tmp_cmd), tmp_cmd, settings, pipe))
	{
		close_fd(tmp_cmd->input);
		close_fd(tmp_cmd->output);
		return (1);
	}
	return (0);
}

void	start_execution(t_cmd *cmds, t_settings *settings)
{
	t_cmd	*tmp_cmd;
	int		pipe;
	int		exe2;

	pipe = has_pipe(cmds);
	tmp_cmd = cmds;
	while (tmp_cmd)
	{
		tmp_cmd->m_args = args_to_matrice(tmp_cmd->args);
		piping(tmp_cmd, tmp_cmd->next);
		exe2 = start_execution2(tmp_cmd, settings, pipe);
		if (exe2 == -1)
			break ;
		else if (exe2 == 1)
		{
			tmp_cmd = tmp_cmd->next;
			continue ;
		}
		close_fd(tmp_cmd->input);
		close_fd(tmp_cmd->output);
		tmp_cmd = tmp_cmd->next;
	}
	waiting(cmds);
	set_vquit(0);
	g_global.is_main = 1;
}
