/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:40:45 by hitran            #+#    #+#             */
/*   Updated: 2024/10/21 10:54:09 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_status	grab_chopsticks(t_philo *philo)
{
	if (check_status(philo) == FINISH)
		return (ERROR);
	sem_wait(philo->chopsticks);
	if (print_action(philo, "has taken the first chopstick") == ERROR)
		return (post_return(philo->chopsticks, 1));
	if (philo->num_of_philos == 1)
		return (post_return(philo->chopsticks, 1));
	sem_wait(philo->chopsticks);
	if (print_action(philo, "has taken the second chopstick") == ERROR)
		return (post_return(philo->chopsticks, 2));
	return (SUCCESS);
}

static t_status	eating(t_philo *philo)
{
	if (check_status(philo) == FINISH)
		return (ERROR);
	print_action(philo, "is eating Pho");
	if (waiting(philo->time_to_eat, philo) == ERROR)
		return (post_return(philo->chopsticks, 2));
	sem_wait(philo->lock);
	philo->eaten_times++;
	philo->last_eaten_time = get_millisecond();
	if (philo->eaten_times == philo->num_of_meals)
		philo->num_of_full_philos++;
	sem_post(philo->lock);
	sem_post(philo->chopsticks);
	sem_post(philo->chopsticks);
	return (SUCCESS);
}

static t_status	not_eating(t_philo *philo)
{
	if (check_status(philo) == FINISH)
		return (ERROR);
	if (print_action(philo, "is sleeping") == ERROR)
		return (ERROR);
	if (waiting(philo->time_to_sleep, philo) == ERROR)
		return (ERROR);
	if (print_action(philo, "is coding") == ERROR)
		return (ERROR);
	return (SUCCESS);
}

t_status	philo_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		waiting(philo->time_to_eat, philo);
	while (1)
	{
		if (grab_chopsticks(philo) == ERROR)
			break ;
		if (eating(philo) == ERROR)
			break ;
		if (not_eating(philo) == ERROR)
			break ;
	}
	return (SUCCESS);
}
