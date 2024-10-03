/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:44:15 by hitran            #+#    #+#             */
/*   Updated: 2024/10/03 14:59:48 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	if (philo->threads)
		free (philo->threads);
	philo->threads = NULL;
	if (philo->chopsticks)
	{
		sem_close(philo->chopsticks);
    	sem_unlink("/chopstick_sem");
		philo->chopsticks = NULL;
	}
	if (philo->lock)
	{
		sem_close(philo->lock);
    	sem_unlink("/lock_sem");
		philo->lock = NULL;
	}
	return (ERROR);
}

t_status	philo_error(t_philo *philo, char *message)
{
	write(2, message, ft_strlen(message));
	free_philo(philo);
	return (ERROR);
}

t_status	post_return(sem_t *chopsticks, int num)
{
	while (num-- > 0)
		sem_post(chopsticks);
	return (ERROR);
}
