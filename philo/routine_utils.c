/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:11:20 by hitran            #+#    #+#             */
/*   Updated: 2024/09/26 23:25:23 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (check_status(thread->philo) == FINISH)
		return (ERROR);
	printf("%lu %ld %s\n", get_millisecond() - thread->philo->start_time,
		thread->id, message);
	return (SUCCESS);
}
