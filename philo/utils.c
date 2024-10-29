/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:44:15 by hitran            #+#    #+#             */
/*   Updated: 2024/10/29 22:16:11 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s && s[len] != '\0')
		len++;
	return (len);
}

long	get_millisecond(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

t_status	free_philo(t_philo *philo)
{
	int	index;

	if (philo->threads)
		free (philo->threads);
	philo->threads = NULL;
	if (philo->forks)
	{
		index = 0;
		while (index < philo->total)
			pthread_mutex_destroy(&philo->forks[index++]);
		free(philo->forks);
		philo->forks = NULL;
	}
	pthread_mutex_destroy(&philo->lock);
	return (ERROR);
}

t_status	philo_error(t_philo *philo, char *message)
{
	write(2, message, ft_strlen(message));
	free_philo(philo);
	return (ERROR);
}
