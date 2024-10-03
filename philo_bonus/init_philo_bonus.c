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

static t_status	init_semaphore(t_philo *philo)
{
	philo->chopsticks = sem_open("/chopstick_sem", O_CREAT, 0644,
		philo->num_of_philos);
	if (philo->chopsticks == SEM_FAILED)
	{
		printf("Error: sem_open");// handle error later
		return (ERROR);
	}
	philo->lock = sem_open("/lock_sem", O_CREAT, 0644, 1);
	if (philo->lock == SEM_FAILED)
	{
		printf("Error: sem_open"); // handle error later
		return (ERROR);
	}
	return (SUCCESS);
}

static t_status	init_threads(t_philo *philo)
{
	int	index;

	index = 0;
	while (index < philo->num_of_philos)
	{
		philo->threads[index].id = index + 1;
		philo->threads[index].philo = philo;
		philo->threads[index].last_eaten_time = philo->start_time;
		if (pthread_create(&(philo->threads[index].thread), NULL,
				&philo_routine, &philo->threads[index]))
		{
			sem_close(philo->chopsticks);
			sem_unlink("/chopstick_sem");
			sem_close(philo->lock);
			sem_unlink("/lock_sem");
			philo->status = FINISH;
			usleep(1000);
			while (index--)
				pthread_join(philo->threads[index].thread, NULL);
			return (ERROR);
		}
		index++;
	}
	return (SUCCESS);
}

t_status	init_philo(t_philo *philo)
{
	philo->threads = malloc(philo->num_of_philos * sizeof(t_thread));
	philo->chopsticks = malloc(philo->num_of_philos * sizeof(sem_t));
	philo->lock = malloc(sizeof(sem_t));
	if (!philo->threads || !philo->chopsticks)
		return (init_error(philo, "Error: Failed to allocate memories\n"));
	memset(philo->threads, 0, philo->num_of_philos * sizeof(t_thread));
	memset(philo->chopsticks, 0, philo->num_of_philos * sizeof(sem_t));
	memset(philo->lock, 0, sizeof(sem_t));
	if (init_semaphores(philo) == ERROR)
		return (init_error(philo, "Error: Failed to init semaphores\n"));
	philo->start_time = get_millisecond();
	if (philo->start_time == -1)
		return (init_error(philo, "Error: Failed to get time\n"));
	if (init_threads(philo) == ERROR)
		return (init_error(philo, "Error: Failed to init threads\n"));
	return (SUCCESS);
}
