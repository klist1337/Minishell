/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:36:19 by achedmi           #+#    #+#             */
/*   Updated: 2022/07/28 23:30:50 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	**just_env(t_settings *settings)
{
	char	**just_env;
	int		i;
	int		c;
	int		j;

	i = -1;
	c = 0;
	while (settings->envp[++i])
		if (ft_strchr(settings->envp[i], '='))
			c++;
	just_env = malloc((sizeof(char *) * c) + 1);
	i = -1;
	j = 0;
	while (settings->envp[++i])
	{
		if (ft_strchr(settings->envp[i], '='))
		{
			just_env[j] = settings->envp[i];
			j++;
		}
	}
	just_env[j] = NULL;
	return (just_env);
}

int	search_env(t_settings *settings, char *line)
{
	int		i;
	char	*res;

	i = -1;
	while (settings->envp[++i])
	{
		if (ft_strchr(line, '+'))
			res = ft_substr(line, 0, ft_strlen(line)
					- ft_strlen(ft_strchr(line, '+')));
		else if (ft_strchr(line, '='))
			res = ft_substr(line, 0, ft_strlen(line)
					- ft_strlen(ft_strchr(line, '=')));
		else
			res = ft_strdup(line);
		if ((res && !ft_strncmp(res, settings->envp[i], ft_strlen(res)))
			&& (settings->envp[i][ft_strlen(res)] == '\0'
			|| settings->envp[i][ft_strlen(res)] == '='))
		{
			if (!ft_strchr(line, '='))
				i = -2;
			return (free(res), i);
		}
		free(res);
	}
	return (-1);
}

char	**add_env(t_settings *settings, char *str)
{
	char	**new_matrice;
	int		i;

	new_matrice = malloc(sizeof(char *) * (matrice_len(settings->envp) + 2));
	i = -1;
	while (settings->envp[++i])
		new_matrice[i] = ft_strdup(settings->envp[i]);
	if (ft_strchr(str, '+'))
		new_matrice[i++] = plus_case(str);
	else
		new_matrice[i++] = ft_strdup(str);
	new_matrice[i] = NULL;
	return (new_matrice);
}

void	replace_env(t_settings *settings, char *str, int index)
{
	char	*tmp;

	if (strchr(str, '+') && *(strchr(str, '+') + 1) == '=')
	{
		if (!ft_strchr(settings->envp[index], '='))
		{
			tmp = settings->envp[index];
			settings->envp[index] = ft_strjoin(settings->envp[index], "=");
			free(tmp);
		}
		tmp = ft_strjoin(settings->envp[index], strchr(str, '=') + 1);
		free(settings->envp[index]);
		settings->envp[index] = tmp;
	}
	else
	{
		free(settings->envp[index]);
		settings->envp[index] = ft_strdup(str);
	}
}

void	print_envp_item_with_val(char *str, t_cmd *cmd)
{
	int	i;
	int	first_time;

	i = -1;
	first_time = 0;
	while (str[++i])
	{
		ft_putchar_fd(str[i], cmd->output);
		if (str[i] == '=' && first_time == 0)
		{
			first_time = 1;
			ft_putchar_fd('\"', cmd->output);
		}
	}
	ft_putstr_fd("\"\n", cmd->output);
}
