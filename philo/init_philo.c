/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:38:43 by hitran            #+#    #+#             */
/*   Updated: 2024/10/24 14:27:17 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status	init_mutexes(t_philo *philo)
{
	int	index;

	index = 0;
	while (index < philo->total)
	{
		if (pthread_mutex_init(&philo->chopsticks[index], NULL))
		{
			while (index--)
				pthread_mutex_destroy(&philo->chopsticks[index]);
			free(philo->chopsticks);
			philo->chopsticks = NULL;
			return (ERROR);
		}
		index++;
	}
	if (pthread_mutex_init(&philo->lock, NULL))
		return (ERROR);
	return (SUCCESS);
}

static t_status	init_threads(t_philo *philo)
{
	int	index;

	index = 0;
	while (index < philo->total)
	{
		philo->threads[index].id = index + 1;
		philo->threads[index].left_chopstick = &philo->chopsticks[index];
		philo->threads[index].right_chopstick = &philo->chopsticks[(index + 1)
			% philo->total];
		philo->threads[index].philo = philo;
		philo->threads[index].last_eaten_time = philo->start_time;
		if (pthread_create(&(philo->threads[index].thread), NULL,
				&routine, &philo->threads[index]))
		{
			pthread_mutex_lock(&philo->lock);
			philo->status = FINISH;
			usleep(500);
			pthread_mutex_unlock(&philo->lock);
			while (index--)
				pthread_join(philo->threads[index].thread, NULL);
			return (ERROR);
		}
		index++;
	}
	return (SUCCESS);
}

t_status	init_philo(t_philo *philo)
{
	philo->threads = malloc(philo->total * sizeof(t_thread));
	philo->chopsticks = malloc(philo->total * sizeof(pthread_mutex_t));
	if (!philo->threads || !philo->chopsticks)
		return (philo_error(philo, "Error: Failed to allocate memories\n"));
	memset(philo->threads, 0, philo->total * sizeof(t_thread));
	memset(philo->chopsticks, 0, philo->total * sizeof(pthread_mutex_t));
	if (init_mutexes(philo) == ERROR)
		return (philo_error(philo, "Error: Failed to init mutexes\n"));
	philo->start_time = get_millisecond();
	if (philo->start_time == -1)
		return (philo_error(philo, "Error: Failed to get time\n"));
	if (init_threads(philo) == ERROR)
		return (philo_error(philo, "Error: Failed to init threads\n"));
	return (SUCCESS);
}
