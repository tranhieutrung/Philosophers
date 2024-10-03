/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:11:20 by hitran            #+#    #+#             */
/*   Updated: 2024/10/03 15:09:56 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_status	check_status(t_philo *philo)
{
	t_status	status;

	pthread_mutex_lock(&philo->lock);
	status = philo->status;
	pthread_mutex_unlock(&philo->lock);
	return (status);
}

t_status	waiting(long ms, t_philo *philo)
{
	long	time_in_ms;

	time_in_ms = get_millisecond();
	while ((get_millisecond() - time_in_ms) < ms)
	{
		if (check_status(philo) == FINISH)
			return (ERROR);
		usleep(1000);
	}
	return (SUCCESS);
}

t_status	print_action(t_thread *thread, char *message)
{
	pthread_mutex_lock(&thread->philo->lock);
	if (thread->philo->status == FINISH)
		return (unlock_return(&thread->philo->lock, NULL));
	printf("%-8lu %-6d %s\n", get_millisecond() - thread->philo->start_time,
		thread->id, message);
	pthread_mutex_unlock(&thread->philo->lock);
	return (SUCCESS);
}
