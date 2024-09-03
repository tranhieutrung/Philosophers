/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:09:40 by hitran            #+#    #+#             */
/*   Updated: 2024/09/03 22:36:59 by hitran           ###   ########.fr       */
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
	int		sign;

	number = 0;
	sign = 1;
	while ((*s >= '\t' && *s <= '\r') || *s == ' ')
		s++;
	if (*s == '-')
		sign = -sign;
	if (*s == '-' || *s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * sign);
}
