/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:43:05 by hitran            #+#    #+#             */
/*   Updated: 2024/10/24 15:32:44 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status	grab_chopsticks(t_thread *thread)
{
	if (check_status(thread->philo) == FINISH)
		return (ERROR);
	pthread_mutex_lock(thread->left_chopstick);
	if (print_action(thread, "has taken the left chopstick") == ERROR
		|| thread->philo->total == 1
		|| check_status(thread->philo) == FINISH)
		return (unlock_return(thread->left_chopstick, NULL));
	pthread_mutex_lock(thread->right_chopstick);
	if (print_action(thread, "has taken the right chopstick") == ERROR)
		return (unlock_return(thread->left_chopstick, thread->right_chopstick));
	return (SUCCESS);
}

static t_status	eating(t_thread *thread)
{
	if (print_action(thread, "is eating Pho"))
		return (unlock_return(thread->left_chopstick, thread->right_chopstick));
	if (waiting(thread->philo->time_to_eat, thread->philo) == ERROR)
		return (unlock_return(thread->left_chopstick, thread->right_chopstick));
	pthread_mutex_lock(&thread->philo->lock);
	thread->eaten_times++;
	thread->last_eaten_time = get_millisecond();
	if (thread->eaten_times == thread->philo->meals)
		thread->philo->full_total++;
	pthread_mutex_unlock(&thread->philo->lock);
	pthread_mutex_unlock(thread->left_chopstick);
	pthread_mutex_unlock(thread->right_chopstick);
	return (SUCCESS);
}

static t_status	not_eating(t_thread *thread)
{
	if (check_status(thread->philo) == FINISH)
		return (ERROR);
	if (print_action(thread, "is sleeping") == ERROR)
		return (ERROR);
	if (waiting(thread->philo->time_to_sleep, thread->philo) == ERROR)
		return (ERROR);
	if (print_action(thread, "is coding") == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void	*routine(void *arg)
{
	t_thread	*thread;

	thread = arg;
	if (thread->id % 2 == 0)
		waiting(thread->philo->time_to_eat, thread->philo);
	while (1)
	{
		if (grab_chopsticks(thread) == ERROR)
			break ;
		if (eating(thread) == ERROR)
			break ;
		if (not_eating(thread) == ERROR)
			break ;
	}
	return (NULL);
}
