/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 17:03:55 by achedmi           #+#    #+#             */
/*   Updated: 2022/07/19 11:21:36 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strdup(const char *s)
{
	char	*p;

	if (!s)
		return (NULL);
	p = malloc(ft_strlen((char *)s) + 1);
	if (p == NULL)
		return (NULL);
	ft_strlcpy(p, s, ft_strlen((char *)s) + 1);
	return (p);
}
