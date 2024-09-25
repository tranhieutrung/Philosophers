/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:44:15 by hitran            #+#    #+#             */
/*   Updated: 2024/09/25 15:28:55 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(int fd, char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len++;
	write(fd, s, len);
}

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

bool	free_philo(t_philo *philo)
{
	int index;

	if (philo->threads)
	{
		//free threads, mutexes
		free (philo->threads);
	}
	if (philo->forks)
	{
		index = 0;
		while (philo->forks[index])
			pthread_mutex_destroy(philo->forks[index++]);
		free(philo->forks);
	}
	if (philo->lock)
		pthread_mutex_destroy(philo->lock);
	return (false);
}
