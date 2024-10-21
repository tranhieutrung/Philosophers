/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:38:43 by hitran            #+#    #+#             */
/*   Updated: 2024/10/03 15:13:34 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_status	init_error(t_philo *philo, char *message)
{
	write(2, message, ft_strlen(message));
	free_philo(philo);
	return (ERROR);
}

static t_status	init_semaphores(t_philo *philo)
{
	sem_unlink("/chopstick_sem");
	philo->chopsticks = sem_open("/chopstick_sem", O_CREAT, 0644,
		philo->num_of_philos);
	if (philo->chopsticks == SEM_FAILED)
		return (ERROR);
	sem_unlink("/lock_sem");
	philo->lock = sem_open("/lock_sem", O_CREAT, 0644, 1);
	if (philo->lock == SEM_FAILED)
	{
		sem_close(philo->chopsticks);
		sem_unlink("/chopstick_sem");
		return (ERROR);
	}
	return (SUCCESS);
}

static t_status	init_processes(t_philo *philo)
{
	int		index;

	philo->pid = (pid_t *)malloc(philo->num_of_philos * sizeof(pid_t));
	if (!philo->pid)
		return (ERROR);
	index = 0;
	while (index < philo->num_of_philos)
	{
		philo->pid[index] = fork();
		if (philo->pid[index] == -1)
			return (ERROR);
		else if (philo->pid[index] == 0)
		{
			free (philo->pid);
			philo->id = index + 1;
			philo->last_eaten_time = philo->start_time;
			return (philo_routine(philo));
		}
		index++;
	}
	return (SUCCESS);
}

t_status	init_philo(t_philo *philo)
{
	if (init_semaphores(philo) == ERROR)
		return (init_error(philo, "Error: Failed to init semaphores\n"));
	philo->start_time = get_millisecond();
	if (philo->start_time == -1)
		return (init_error(philo, "Error: Failed to get time\n"));
	if (init_processes(philo) == ERROR)
		return (init_error(philo, "Error: Failed to init processes\n"));
	return (SUCCESS);
}
