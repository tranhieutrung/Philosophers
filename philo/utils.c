/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:09:40 by hitran            #+#    #+#             */
/*   Updated: 2024/09/19 13:06:08 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

long	ft_atol(const char *s)
{
	long	number;

	number = 0;
	while (*s >= '0' && *s <= '9')
	{
		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;
	size_t	total;

	total = count * size;
	if (count > 0 && size > 0 && count != (total / size))
		return (NULL);
	res = malloc(total);
	if (!res)
		return (0);
	while (total-- > 0)
		((unsigned char *)res)[total] = 0;
	return (res);
}
