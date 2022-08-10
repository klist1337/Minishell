/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:37:33 by achedmi           #+#    #+#             */
/*   Updated: 2022/07/21 19:12:39 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	env_cmd(char **matrice, t_cmd *commande)
{
	int	i;

	i = -1;
	while (matrice[++i])
	{
		if (ft_strchr(matrice[i], '='))
		{
			ft_putstr_fd(matrice[i], commande->output);
			ft_putchar_fd('\n', commande->output);
		}
	}
}

char	**remove_env(t_settings *settings, char *var)
{
	char	**new_matrice;
	char	**item;
	int		i;
	int		j;

	if (is_valid_key(settings->envp, var))
		new_matrice = malloc(sizeof(char *) * (matrice_len(settings->envp)));
	else
		new_matrice = malloc(sizeof(char *)
				* (matrice_len(settings->envp)) + 1);
	i = 0;
	j = 0;
	while (settings->envp[j])
	{
		item = ft_split(settings->envp[j], '=');
		if (ft_strncmp(item[0], var, ft_strlen(var) + 1))
		{
			new_matrice[i] = ft_strdup(settings->envp[j]);
			i++;
		}
		free_matrice(item);
		j++;
	}
	new_matrice[i] = NULL;
	return (new_matrice);
}

int	get_index_of_envp(char **matrice, char *key)
{
	int		i;
	char	**key_val;

	i = -1;
	if (is_valid_key(matrice, key))
	{
		while (matrice[++i])
		{
			key_val = ft_split(matrice[i], '=');
			if (!ft_strncmp(key_val[0], key, ft_strlen(key) + 1))
			{
				free_matrice(key_val);
				return (i);
			}
			free_matrice(key_val);
		}
	}
	return (-1);
}
