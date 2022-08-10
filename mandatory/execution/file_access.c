/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:50:24 by achedmi           #+#    #+#             */
/*   Updated: 2022/07/22 11:56:04 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*check_acess2(char *long_path, char *cmd)
{
	char	**paths;
	char	*new_path;
	char	*cmd_path;
	int		i;

	paths = ft_split(long_path, ':');
	i = -1;
	while (paths[++i])
	{
		new_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(new_path, cmd);
		if (access(cmd_path, F_OK) == 0)
		{
			free_matrice(paths);
			free(new_path);
			return (cmd_path);
		}
		free (new_path);
		free (cmd_path);
	}
	free_matrice(paths);
	return (NULL);
}

char	*check_acces(char **envp, char *cmd)
{
	char	*long_path;
	char	*error;
	int		i;

	i = 0;
	if (strchr(cmd, '/'))
		return (cmd);
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			long_path = &envp[i][5];
			i = -1;
			if (check_acess2(long_path, cmd))
				return (check_acess2(long_path, cmd));
			break ;
		}
	}
	error = ft_strjoin(cmd, ": command not found \n");
	write(2, error, ft_strlen(error));
	exit(127);
	free(error);
}
