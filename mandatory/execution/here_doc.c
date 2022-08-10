/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:53:56 by achedmi           #+#    #+#             */
/*   Updated: 2022/07/28 19:54:11 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	here_doc2(t_file *file, int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(0);
		if (!ft_strncmp(line, file->lim, ft_strlen(line)))
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
}

void	here_doc(t_cmd *commande, t_file *file)
{
	int		fds[2];
	char	*tmp;
	int		id;
	int		status;

	pipe(fds);
	tmp = file->lim;
	file->lim = ft_strjoin(file->lim, "\n");
	free(tmp);
	g_global.is_main = 0;
	id = fork();
	if (id == 0)
	{
		signal(SIGINT, here_doc_sig_handler);
		here_doc2(file, fds[1]);
		exit(0);
	}
	waitpid(id, &status, 0);
	g_global.is_main = 1;
	close_fd(fds[1]);
	commande->input = fds[0];
	g_global.exit_value = WEXITSTATUS(status);
}
