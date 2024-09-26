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

bool	grab_forks(t_thread *thread)
{
	if (check_status(thread->philo))
		return (false);
	pthread_mutex_lock(thread->left_fork);
	if (!print_action(thread, "has taken a fork"))
	{
		pthread_mutex_unlock(thread->left_fork);
		return (false);
	}
	if (check_status(thread->philo) || thread->philo->num_of_philos == 1)
	{
		pthread_mutex_unlock(thread->left_fork);
		return (false);
	}
	pthread_mutex_lock(thread->right_fork);
	if (!print_action(thread, "has taken a fork"))
	{
		pthread_mutex_unlock(thread->left_fork);
		pthread_mutex_unlock(thread->right_fork);
		return (false);
	}
	return (true);
}

bool	eating(t_thread *thread)
{
	pthread_mutex_lock(&thread->philo->lock);
	thread->eaten_times++;
	thread->last_eaten_time = get_millisecond();
	pthread_mutex_unlock(&thread->philo->lock);
	print_action(thread, "is eating");
	if (!waiting(thread->philo->time_to_eat, thread->philo))
		return (false);
	printf("here");
	pthread_mutex_lock(&thread->philo->lock);
	if (thread->eaten_times == thread->philo->num_of_meals)
		thread->philo->num_of_full_philos++;
	pthread_mutex_unlock(&thread->philo->lock);
	pthread_mutex_unlock(thread->left_fork);
	pthread_mutex_unlock(thread->right_fork);
	return (true);
}

bool	not_eating(t_thread *thread)
{
	if (!print_action(thread, "is sleeping"))
		return (false);
	if (!waiting(thread->philo->time_to_sleep, thread->philo))
		return (false);
	if (!print_action(thread, "is thinking"))
		return (false);
	return (true);
}

void	*philo_routine(void *arg)
{
	t_thread	*thread;

	thread = arg;
	if (thread->id % 2 == 0 &&
		!waiting(thread->philo->time_to_eat, thread->philo))
		return (NULL);
	while (1)
	{
		if (!grab_forks(thread))
			break ;
		if (!eating(thread))
			break ;
		if (!not_eating(thread))
			break ;
	}
	return (NULL);
}
