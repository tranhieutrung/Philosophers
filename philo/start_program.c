/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:38:43 by hitran            #+#    #+#             */
/*   Updated: 2024/09/22 13:07:36 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_watcher(void *watcher)
{
	
}

void	*routine(void *thread)
{

}

bool	start_program(t_philo *philo)
{
	int			i;
	pthread_t	*threads;
	pthread_t	watcher;

	threads = (pthread_t *)ft_calloc(philo->args.num_of_philos, sizeof(pthread_t));
	if (!threads)
		return (error_thread(philo)); //handle error
	if (pthread_create(&watcher, NULL, &death_watcher, (void *)philo))
		return (error_thread(philo)); //handle error
	if (pthread_detach(watcher))
		return (error_thread(philo)); //handle error
	i = 0;
	while (i < philo->args.num_of_philos)
	{
		if (pthread_create(&threads[i], NULL, &routine, (void *)philo))
			return (error_thread(philo)); //handle error
		philo = philo->next;
		if (pthread_join(threads[i], NULL))
			return (error_thread(philo)); //handle error
		i++;
	}
	free(threads);
	cleaner(philo);
	return (true);
}
