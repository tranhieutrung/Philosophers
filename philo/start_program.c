/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:38:43 by hitran            #+#    #+#             */
/*   Updated: 2024/09/19 22:31:50 by hitran           ###   ########.fr       */
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
		return (error_thread(philo));
	pthread_create(&watcher, NULL, &death_watcher, (void *)philo);
	pthread_detach(watcher);
	i = -1;
	while (++i < philo->args.num_of_philos)
	{
		pthread_create(&threads[i], NULL, &routine, (void *)philo);
		philo = philo->next;
	}
	i = 0;
	while (i < philo->args.num_of_philos)
		pthread_join(threads[i++], NULL);
	free(threads);
	cleaner(philo);
	return (true);
}
