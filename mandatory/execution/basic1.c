/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:20:57 by achedmi           #+#    #+#             */
/*   Updated: 2022/07/21 19:12:18 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	free_matrice(char **matrice)
{
	int	i;

	i = -1;
	if (matrice)
	{
		while (matrice[++i])
			free(matrice[i]);
		free(matrice);
	}
}

int	arg_len(t_args *args)
{
	int	i;

	i = 0;
	while (args)
	{
		i++;
		args = args->next;
	}
	return (i);
}

char	**add_cmd_to_args(t_cmd *cmd)
{
	char	**args;
	int		i;
	int		len;

	len = arg_len(cmd->args);
	args = (char **)malloc(sizeof(char *) * (len + 2));
	args[0] = cmd->commande;
	i = 1;
	while (cmd->args)
	{
		args[i] = cmd->args->content;
		cmd->args = cmd->args->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

char	**args_to_matrice(struct s_args *args)
{
	char	**matrice;
	int		i;

	i = 0;
	matrice = (char **)malloc(sizeof(char *) * (arg_len(args) + 1));
	while (args)
	{
		matrice[i] = ft_strdup(args->content);
		args = args->next;
		i++;
	}
	matrice[i] = NULL;
	return (matrice);
}

int	matrice_len(char **matrice)
{
	int	i;

	i = 0;
	while (matrice[i])
		i++;
	return (i);
}
