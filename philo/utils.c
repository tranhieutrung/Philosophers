/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:09:40 by hitran            #+#    #+#             */
/*   Updated: 2024/08/30 22:09:41 by hitran           ###   ########.fr       */
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
	long	nb;
	int		sign;

	nb = 0;
	sign = 1;
	while ((*s > 8 && *s < 14) || *s == ' ')
		s++;
	if (*s == '-')
		sign = -sign;
	if (*s == '-' || *s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		nb = (nb * 10) + (*s - '0');
		s++;
	}
	return (nb * sign);
}
