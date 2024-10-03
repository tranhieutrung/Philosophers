/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:40:45 by hitran            #+#    #+#             */
/*   Updated: 2024/10/03 23:04:21 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_status	grab_chopsticks(t_thread *thread)
{
	if (check_status(thread->philo) == FINISH)
		return (ERROR);
	sem_wait(thread->philo->chopsticks);
	if (print_action(thread, "has taken the first chopstick") == ERROR)
		return (post_return(thread->philo->chopsticks, 1));
	if (thread->philo->num_of_philos == 1)
		return (post_return(thread->philo->chopsticks, 1));
	sem_wait(thread->philo->chopsticks);
	if (print_action(thread, "has taken the second chopstick") == ERROR)
		return (post_return(thread->philo->chopsticks, 2));
	return (SUCCESS);
}

static t_status	eating(t_thread *thread)
{
	if (check_status(thread->philo) == FINISH)
		return (ERROR);
	print_action(thread, "is eating Pho");
	if (waiting(thread->philo->time_to_eat, thread->philo) == ERROR)
		return (post_return(thread->philo->chopsticks, 2));
	sem_wait(thread->philo->lock);
	thread->eaten_times++;
	thread->last_eaten_time = get_millisecond();
	if (thread->eaten_times == thread->philo->num_of_meals)
		thread->philo->num_of_full_philos++;
	sem_post(thread->philo->lock);
	sem_post(thread->philo->chopsticks);
	sem_post(thread->philo->chopsticks);
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
		if (grab_chopsticks(thread) == ERROR)
			break ;
		if (eating(thread) == ERROR)
			break ;
		if (not_eating(thread) == ERROR)
			break ;
	}
	return (NULL);
}
