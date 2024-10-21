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

	sem_wait(philo->lock);
	status = philo->status;
	sem_post(philo->lock);
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

t_status	print_action(t_philo *philo, char *message)
{
	sem_wait(philo->lock);
	if (philo->status == FINISH)
		return (post_return(philo->lock, 1));
	printf("%-8lu %-6d %s\n", get_millisecond() - philo->start_time,
		philo->id, message);
	sem_post(philo->lock);
	return (SUCCESS);
}
