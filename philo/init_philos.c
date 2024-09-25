/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:38:43 by hitran            #+#    #+#             */
/*   Updated: 2024/09/25 15:28:43 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool init_error(t_philo *philo, char *message)
{
	ft_putstr_fd(2, "Error: ");
	ft_putstr_fd(2, message);
	ft_putstr_fd(2, "\n");
	free_philo(philo);
	return (false);
}

bool	init_mutexes(t_philo *philo)
{
	size_t	index;

	index = 0;
	while (index < philo->num_of_philos)
		if (pthread_mutex_init(philo->forks[index++], NULL))
			return (false);
	if (pthread_mutex_init(philo->lock, NULL))
		return (false);
	return (true);
}

bool	init_threads(t_philo *philo)
{
	size_t	index;

	index = 0;
	while (index < philo->num_of_philos)
	{
		philo->threads[index].id = index + 1;
		philo->threads[index].left_fork = philo->forks[index];
		philo->threads[index].right_fork = philo->forks[(index + 1) % philo->num_of_philos];
		if (pthread_join(philo->threads[index].thread, NULL) != 0)
			return (false);
	}
	return (true);
}

bool	init_philos(t_philo *philo)
{
	philo->millisecond = get_time();
	if (philo->millisecond == -1)
		return (init_error(philo, "Failed to get time"));
	philo->threads = (t_thread *)malloc(philo->num_of_philos * sizeof(t_thread));
	philo->forks = (pthread_mutex_t **)malloc(philo->num_of_philos * sizeof(pthread_mutex_t *));
	if (!philo->threads || !philo->forks)
		return (init_error(philo, "Failed to allocate memories"));
	if (!init_mutexes(philo))
		return (init_error(philo, "Failed to init mutexes"));
	if (!init_threads(philo))
		return (init_error(philo, "Failed to init threads"));
	return (true);
}
