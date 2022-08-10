/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:49:22 by achedmi           #+#    #+#             */
/*   Updated: 2022/07/30 13:13:36 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	close_fd(int fd)
{
	if (fd != 0 && fd != 1 && fd != 2)
		close (fd);
}

int	re_out(t_cmd *commande, t_file *file)
{
	close_fd (commande->output);
	if (file->type == 1)
		commande->output = open(file->name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	else if (file->type == 3)
		commande->output = open(file->name, O_WRONLY | O_APPEND
				| O_CREAT, 0777);
	if (commande->output == -1)
	{
		perror("Error ");
		return (1);
	}
	return (0);
}

int	re_in(t_cmd *commande, t_file *file)
{
	close_fd (commande->input);
	commande->input = open(file->name, R_OK, 0777);
	if (commande->input == -1)
	{
		perror("Error ");
		return (1);
	}
	return (0);
}

int	open_files(t_cmd *cmd)
{
	t_file	*file;

	if (!cmd->files)
		return (0);
	file = cmd->files;
	while (file)
	{
		if (file->type == 0)
		{
			if (re_in(cmd, file))
				return (1);
		}
		else if (file->type == 2)
			here_doc(cmd, file);
		else if (file->type == 1 || file->type == 3)
		{
			if (re_out(cmd, file))
				return (1);
		}
		else if (file->type == -1)
			break ;
		file = file->next;
	}
	return (0);
}

void	piping(t_cmd *prev, t_cmd *next)
{
	int	fds[2];

	if (next)
	{
		pipe(fds);
		next->input = fds[0];
		prev->output = fds[1];
	}
}
