/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:51:23 by achedmi           #+#    #+#             */
/*   Updated: 2022/07/31 19:11:20 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	costum_exit(t_cmd *cmd)
{
	int		exit_code;
	char	**args;

	exit_code = 0;
	if (cmd->args)
		exit_code = ft_atoi(cmd->args->content);
	args = args_to_matrice(cmd->args);
	if (matrice_len(args) > 1)
	{
		printf("exit: too many arguments\n");
		g_global.exit_value = 1;
		free_matrice(args);
		return (1);
	}
	free_matrice(args);
	exit(exit_code);
}
