/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:38:43 by hitran            #+#    #+#             */
/*   Updated: 2024/09/26 23:34:27 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status	init_error(t_philo *philo, char *message)
{
	ft_putstr_fd(2, "Error: ");
	ft_putstr_fd(2, message);
	ft_putstr_fd(2, "\n");
	free_philo(philo);
	return (ERROR);
}

t_status	init_mutexes(t_philo *philo)
{
	size_t	index;

	index = 0;
	while (index < philo->num_of_philos)
	{
		if (pthread_mutex_init(&philo->forks[index], NULL))
			return (ERROR);
		index++;
	}
	if (pthread_mutex_init(&philo->lock, NULL))
		return (ERROR);
	return (SUCCESS);
}

t_status	init_threads(t_philo *philo)
{
	size_t	index;

	index = 0;
	while (index < philo->num_of_philos)
	{
		philo->threads[index].id = index + 1;
		philo->threads[index].left_fork = &philo->forks[index];
		philo->threads[index].right_fork = &philo->forks[(index + 1)
			% philo->num_of_philos];
		philo->threads[index].philo = philo;
		philo->threads[index].last_eaten_time = philo->start_time;
		if (pthread_create(&(philo->threads[index].thread), NULL,
				&philo_routine, &philo->threads[index]))
			return (ERROR);
		index++;
	}
	return (SUCCESS);
}

t_status	init_philo(t_philo *philo)
{
	philo->threads = malloc(philo->num_of_philos * sizeof(t_thread));
	philo->forks = malloc(philo->num_of_philos * sizeof(pthread_mutex_t));
	if (!philo->threads || !philo->forks)
		return (init_error(philo, "Failed to allocate memories"));
	if (init_mutexes(philo) == ERROR)
		return (init_error(philo, "Failed to init mutexes"));
	philo->start_time = get_millisecond();
	if (philo->start_time == -1)
		return (init_error(philo, "Failed to get time"));
	if (init_threads(philo) == ERROR)
		return (init_error(philo, "Failed to init threads"));
	return (SUCCESS);
}
