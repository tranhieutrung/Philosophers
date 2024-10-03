/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:40:45 by hitran            #+#    #+#             */
/*   Updated: 2024/09/26 10:48:45 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status	grab_forks(t_thread *thread)
{
	if (check_status(thread->philo) == FINISH)
		return (ERROR);
	pthread_mutex_lock(thread->left_fork);
	if (print_action(thread, "has taken the first chopstick") == ERROR)
		return (unlock_return(thread->left_fork, NULL));
	if (thread->philo->num_of_philos == 1)
		return (unlock_return (thread->left_fork, NULL));
	pthread_mutex_lock(thread->right_fork);
	if (print_action(thread, "has taken the second chopstick") == ERROR)
		return (unlock_return (thread->left_fork, thread->right_fork));
	return (SUCCESS);
}

static t_status	eating(t_thread *thread)
{
	if (check_status(thread->philo) == FINISH)
		return (ERROR);
	pthread_mutex_lock(&thread->philo->lock);
	thread->eaten_times++;
	pthread_mutex_unlock(&thread->philo->lock);
	print_action(thread, "is eating Pho");
	if (waiting(thread->philo->time_to_eat, thread->philo) == ERROR)
		return (unlock_return (thread->left_fork, thread->right_fork));
	pthread_mutex_lock(&thread->philo->lock);
	thread->last_eaten_time = get_millisecond();
	if (thread->eaten_times == thread->philo->num_of_meals)
		thread->philo->num_of_full_philos++;
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
	if (print_action(thread, "is coding") == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void	*philo_routine(void *arg)
{
	t_thread	*thread;

	thread = arg;
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
