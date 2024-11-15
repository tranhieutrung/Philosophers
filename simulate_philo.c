/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:34:20 by hitran            #+#    #+#             */
/*   Updated: 2024/10/24 15:27:16 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status	print_finish(t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->lock);
	philo->status = FINISH;
	pthread_mutex_unlock(&philo->lock);
	usleep(500);
	pthread_mutex_lock(&philo->lock);
	if (id == 0)
		printf("All philos ate at least %d times\n", philo->meals);
	else
		printf("%-8lu %-6d died\n", get_millisecond() - philo->start_time, id);
	pthread_mutex_unlock(&philo->lock);
	return (FINISH);
}

static t_status	monitor_philo(t_philo *philo)
{
	int	index;

	index = 0;
	while (index < philo->total)
	{
		if (((get_millisecond() - philo->threads[index].last_eaten_time)
				>= (long)philo->time_to_die))
			return (print_finish(philo, index + 1));
		else if (philo->full_total == philo->total)
			return (print_finish(philo, 0));
		index++;
	}
	return (RUNNING);
}

static t_status	wait_for_all_threads(t_philo *philo)
{
	int	index;

	index = 0;
	while (index < philo->total)
	{
		if (pthread_join(philo->threads[index].thread, NULL))
			return (philo_error(philo, "Error: Failed to join threads"));
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
	free_philo(philo);
	return (SUCCESS);
}
