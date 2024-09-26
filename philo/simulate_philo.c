/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:34:20 by hitran            #+#    #+#             */
/*   Updated: 2024/09/26 23:33:48 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_status	monitor_philo(t_philo *philo)
{
	size_t	index;

	index = 0;
	while (index < philo->num_of_philos)
	{
		pthread_mutex_lock(&philo->lock);
		if (((size_t)(get_millisecond()
				- philo->threads[index].last_eaten_time) >= philo->time_to_die)
				|| philo->num_of_full_philos == philo->num_of_philos)
		{
			philo->status = FINISH;
			if (philo->num_of_full_philos == philo->num_of_philos)
				printf("All philosophers ate %ld times\n", philo->num_of_meals);
			else
				printf("%lu %ld died\n", get_millisecond()
					- philo->start_time, index + 1);
			pthread_mutex_unlock(&philo->lock);
			return (FINISH);
		}
		index++;
		pthread_mutex_unlock(&philo->lock);
	}
	return (RUNNING);
}

t_status	wait_for_all_threads(t_philo *philo)
{
	size_t	index;

	index = 0;
	while (index < philo->num_of_philos)
	{
		if (pthread_join(philo->threads[index].thread, NULL))
			return (philo_error(philo, "Failed to join threads"));
		index++;
	}
	return (SUCCESS);
}

t_status	simulate_philo(t_philo *philo)
{
	while (1)
	{
		if (monitor_philo(philo) == FINISH)
			break ;
	}
	if (wait_for_all_threads(philo) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
