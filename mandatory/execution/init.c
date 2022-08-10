/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:24:35 by achedmi           #+#    #+#             */
/*   Updated: 2022/07/22 12:37:04 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	init(t_settings **settings, char **envp)
{
	int	i;

	(*settings) = malloc(sizeof(t_settings));
	(*settings)->current_dir = getcwd(NULL, 0);
	(*settings)->env_len = matrice_len(envp);
	(*settings)->envp = malloc((sizeof(char *) * (*settings)->env_len) + 1);
	i = -1;
	while (envp[++i])
		(*settings)->envp[i] = ft_strdup(envp[i]);
	(*settings)->envp[i] = NULL;
	remove_value_of_key((*settings)->envp, "OLDPWD");
	g_global.is_main = 1;
	tcgetattr(STDIN_FILENO, &g_global.termios);
	set_vquit(0);
	init_signal();
}
