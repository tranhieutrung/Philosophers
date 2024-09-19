/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:38:43 by hitran            #+#    #+#             */
/*   Updated: 2024/09/19 22:05:08 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_input(t_arg *args, char **argv)
{
	args->num_of_philos = ft_atol(argv[1]);
	args->time_to_die = ft_atol(argv[2]);
	args->time_to_eat = ft_atol(argv[3]);
	args->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		args->num_of_meals = ft_atol(argv[5]);
	else
		args->num_of_meals = -1;
}

int	init_mutexes(int num_of_philos, t_mutex *mutexes)
{
	int	ret;
	
	mutexes->eaten = num_of_philos;
	ret = pthread_mutex_init(&mutexes->stop, NULL);
	if (ret)
		return (ret);
	ret = pthread_mutex_init(&mutexes->eaten, NULL);
	if (ret)
	{
		pthread_mutex_destroy(&mutexes->stop);
		return (ret);
	}
	ret = pthread_mutex_init(&mutexes->print, NULL);
	if (ret)
	{
		pthread_mutex_destroy(&mutexes->stop);
		pthread_mutex_destroy(&mutexes->eaten);
		return (ret);
	}
	return (ret);
}

t_philo	*new_philo(t_arg *args, t_mutex *mutexes, int id)
{
	t_philo *new;
	int		ret;

	new = (t_philo *)ft_calloc(1, sizeof(t_philo));
	if (!new)
		return (NULL);
	new->id = id;
	new->num_of_chopsticks = 1;
	new->args = *args;
	new->mutexes = mutexes;
	if (pthread_mutex_init(&new->chopstick, NULL))
	{
		free(new);
		return (NULL); //handle error
	}
	return (new);
}

t_philo	*last_philo(t_philo *philo)
{
	while (philo->next)
		philo = philo->next;
	return (philo);
}

bool	*init_philos(t_philo *philo, char **argv)
{
	t_arg 		args;
	t_mutex		*mutexes;
	int			i;
	t_philo		*new;

	parse_input(&args, argv);
	if (init_mutexes(args.num_of_philos, mutexes))
		return (false); //handle error
	philo = NULL;
	i = 0;
	while (i < args.num_of_philos)
	{
		new = new_philo(&args, mutexes, ++i);
		if (!new)
			return (false); //handle error
		new->next = philo;
		if (i == 1)
			philo = new;
		else
			last_philo(philo)->next = new;
	}
	return (true);
}
