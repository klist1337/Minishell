/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:23:15 by achedmi           #+#    #+#             */
/*   Updated: 2022/07/21 19:12:22 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*get_value(char **matrice, char *key)
{
	int		i;
	char	**key_value;

	i = -1;
	while (matrice[++i])
	{
		key_value = ft_split(matrice[i], '=');
		if ((key_value[0] && key_value[1])
			&& !ft_strncmp(key_value[0], key, ft_strlen(key) + 1))
		{
			free_matrice(key_value);
			return (ft_strchr(matrice[i], '=') + 1);
		}
		free_matrice(key_value);
	}
	return (NULL);
}

int	is_valid_key(char **matrice, char *key)
{
	int		i;
	char	**key_value;

	i = -1;
	while (matrice[++i])
	{
		key_value = ft_split(matrice[i], '=');
		if (!ft_strncmp(key_value[0], key, ft_strlen(key) + 1))
		{
			free_matrice(key_value);
			return (1);
		}
		free_matrice(key_value);
	}
	return (0);
}

void	remove_value_of_key(char **matrice, char *key)
{
	char	*tmp;
	int		i;
	char	*new_item;

	i = get_index_of_envp(matrice, key);
	if (i > -1)
	{
		new_item = ft_strdup(key);
		tmp = matrice[i];
		matrice[i] = new_item;
		free(tmp);
	}
}

void	change_value_of_key(char **matrice, char *key, char *value)
{
	char	*tmp;
	int		i;
	char	*new_item;

	i = get_index_of_envp(matrice, key);
	if (i > -1)
	{
		new_item = ft_strjoin(key, "=");
		tmp = new_item;
		new_item = ft_strjoin(new_item, value);
		free(tmp);
		tmp = matrice[i];
		matrice[i] = new_item;
		free(tmp);
	}
}

int	has_pipe(t_cmd *cmd)
{
	if (!cmd || !cmd->next)
		return (0);
	else if (cmd->next)
		return (1);
	return (0);
}
