/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:21:53 by achedmi           #+#    #+#             */
/*   Updated: 2022/07/30 10:14:38 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

long	ft_atoi2(int i, long res, char *str, int sign)
{
	while (str[i])
	{
		res = (res * 10) + (str[i] - '0');
		if ((res > 2147483647 && sign == 1)
			|| (res > 2147483648 && sign == -1) || ft_isdigit(str[i]) == 0)
		{
			if (ft_isdigit(str[i]))
				printf("exit: %li: numeric argument required\n", res);
			else
				printf("exit: %s: numeric argument required\n", str);
			exit(255);
		}
		i++;
	}
	return (res);
}

int	ft_atoi(const char *str)
{
	long	i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	res = ft_atoi2(i, res, (char *)str, sign);
	return (res * sign);
}
