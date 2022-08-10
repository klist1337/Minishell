/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:17:09 by achedmi           #+#    #+#             */
/*   Updated: 2022/07/31 18:48:43 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((str + i));
		i++;
	}
	if ((char)c == '\0' && !str[i])
	{
		return (&str[i]);
	}
	return (NULL);
}

char	*ft_strchr2(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((str + i));
		i++;
	}
	if ((char)c == '\0' && !str[i])
	{
		return (&str[i]);
	}
	return (NULL);
}
