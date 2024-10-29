/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:43:05 by hitran            #+#    #+#             */
/*   Updated: 2024/10/29 22:16:38 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status	grab_forks(t_thread *thread)
{
	if (check_status(thread->philo) == FINISH)
		return (ERROR);
	pthread_mutex_lock(thread->left_fork);
	if (print_action(thread, "has taken a fork") == ERROR
		|| thread->philo->total == 1
		|| check_status(thread->philo) == FINISH)
		return (unlock_return(thread->left_fork, NULL));
	pthread_mutex_lock(thread->right_fork);
	if (print_action(thread, "has taken a fork") == ERROR)
		return (unlock_return(thread->left_fork, thread->right_fork));
	return (SUCCESS);
}

static t_status	eating(t_thread *thread)
{
	if (print_action(thread, "is eating") == ERROR)
		return (unlock_return(thread->left_fork, thread->right_fork));
	if (waiting(thread->philo->time_to_eat, thread->philo) == ERROR)
		return (unlock_return(thread->left_fork, thread->right_fork));
	pthread_mutex_lock(&thread->philo->lock);
	thread->eaten_times++;
	thread->last_eaten_time = get_millisecond();
	if (thread->eaten_times == thread->philo->meals)
		thread->philo->full_total++;
	pthread_mutex_unlock(&thread->philo->lock);
	pthread_mutex_unlock(thread->left_fork);
	pthread_mutex_unlock(thread->right_fork);
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
	if (print_action(thread, "is thinking") == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void	*routine(void *arg)
{
	t_thread	*thread;

	thread = arg;
	if (print_action(thread, "is thinking") == ERROR)
		return (NULL);
	if (thread->id % 2 == 0)
		waiting(thread->philo->time_to_eat, thread->philo);
	while (1)
	{
		if (grab_forks(thread) == ERROR)
			break ;
		if (eating(thread) == ERROR)
			break ;
		if (not_eating(thread) == ERROR)
			break ;
	}
	return (NULL);
}
