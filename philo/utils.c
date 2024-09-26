/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:44:15 by hitran            #+#    #+#             */
/*   Updated: 2024/09/26 14:38:37 by hitran           ###   ########.fr       */
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

long	get_millisecond(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

bool	free_philo(t_philo *philo)
{
	size_t index;

	if (philo->threads)
		free (philo->threads);
	if (philo->forks)
	{
		index = 0;
		while (index < philo->num_of_philos)
			pthread_mutex_destroy(&philo->forks[index++]);
		free(philo->forks);
	}
	pthread_mutex_destroy(&philo->lock);
	return (false);
}

bool philo_error(t_philo *philo, char *message)
{
	ft_putstr_fd(2, "Error: ");
	ft_putstr_fd(2, message);
	ft_putstr_fd(2, "\n");
	free_philo(philo);
	return (false);
}