/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_philo_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:34:20 by hitran            #+#    #+#             */
/*   Updated: 2024/10/03 15:14:30 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_status	print_finish(t_philo *philo, int id)
{
	sem_wait(philo->lock);
	philo->status = FINISH;
	sem_post(philo->lock);
	if (id == 0)
		printf("All philos ate at least %d times\n", philo->num_of_meals);
	else
		printf("%-8lu %-6d died\n", get_millisecond() - philo->start_time, id);
	return (FINISH);
}

static t_status	monitor_philo(t_philo *philo)
{
	int	index;

	index = 0;
	while (index < philo->num_of_philos)
	{
		if (((get_millisecond() - philo->threads[index].last_eaten_time)
				>= (long)philo->time_to_die))
			return (print_finish(philo, index + 1));
		else if (philo->num_of_full_philos == philo->num_of_philos)
			return (print_finish(philo, 0));
		index++;
	}
	return (RUNNING);
}

static t_status	wait_for_all_threads(t_philo *philo)
{
	int	index;

	index = 0;
	while (index < philo->num_of_philos)
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
