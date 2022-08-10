/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:41:00 by achedmi           #+#    #+#             */
/*   Updated: 2022/07/31 19:49:43 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	empty_export(char **matrice, t_cmd *commande)
{
	int	i;

	i = -1;
	while (matrice[++i])
	{
		ft_putstr_fd("declare -x ", commande->output);
		if (ft_strchr(matrice[i], '='))
			print_envp_item_with_val(matrice[i], commande);
		else
		{
			ft_putstr_fd(matrice[i], commande->output);
			ft_putchar_fd('\n', commande->output);
		}
	}
}

void	export(t_settings *settings, char **vars)
{
	char	**tmp_env;
	int		search_result;
	int		i;

	i = -1;
	while (vars[++i])
	{
		tmp_env = settings->envp;
		if (!str_validation(vars[i], "export"))
		{
			ft_putstr_fd("export: '", 2);
			ft_putstr_fd(vars[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_global.exit_value = 1;
			continue ;
		}
		search_result = search_env(settings, vars[i]);
		if (search_result >= 0)
			replace_env(settings, vars[i], search_result);
		else if (search_result == -1)
		{
			settings->envp = add_env(settings, vars[i]);
			free_matrice(tmp_env);
		}
	}
}

int	str_validation(char *str, char *type)
{
	int	i;

	i = 0;
	if (str)
	{
		if (!(ft_isalpha(str[0]) || str[0] == '_'))
			return (0);
		while (str[++i] && str[i] != '=' && str[i] != '+')
		{
			if (!ft_isalnum(str[i]) && str[i] != '_')
				return (0);
		}
		if (str[i] == '+' && !ft_strncmp(type, "export", 6))
			i++;
		else if (str[i] == '+' && !ft_strncmp(type, "unset", 6))
			return (0);
		if ((str[i] != '=' && !ft_strncmp(type, "export", 6))
			&& str[i - 1] == '+')
			return (0);
		if (str[i] == '=' && !ft_strncmp(type, "unset", 6))
			return (0);
	}
	return (1);
}

void	unset(t_settings *settings, char **vars)
{
	char	**tmp_env;
	int		i;

	i = -1;
	tmp_env = settings->envp;
	while (vars[++i])
	{
		if (!str_validation(vars[i], "unset"))
		{
			ft_putstr_fd("unset: '", 2);
			ft_putstr_fd(vars[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_global.exit_value = 1;
			continue ;
		}
		tmp_env = settings->envp;
		settings->envp = remove_env(settings, vars[i]);
		free_matrice(tmp_env);
	}
}

char	*plus_case(char *str)
{
	int		i;
	int		should_split;
	char	**key_val;
	char	*res;

	i = -1;
	should_split = 0;
	while (str[++i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
		{
			should_split = 1;
			break ;
		}
	}
	if (should_split)
	{
		key_val = ft_split(str, '+');
		res = key_val[0];
		res = ft_strjoin(res, &str[i + 1]);
		free_matrice(key_val);
		return (res);
	}
	return (NULL);
}
