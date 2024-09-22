/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:38:43 by hitran            #+#    #+#             */
/*   Updated: 2024/09/22 09:31:04 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_input(t_philo *philo, char **argv)
{
	philo->args.num_of_philos = ft_atol(argv[1]);
	philo->args.time_to_die = ft_atol(argv[2]);
	philo->args.time_to_eat = ft_atol(argv[3]);
	philo->args.time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		philo->args.num_of_meals = ft_atol(argv[5]);
	else
		philo->args.num_of_meals = -1;
}

int	init_mutexes(t_philo *philo)
{
	int	ret;
	
	philo->mutexes->eaten = philo->args.num_of_philos;
	ret = pthread_mutex_init(&philo->mutexes->stop, NULL);
	if (ret)
		return (ret);
	ret = pthread_mutex_init(&philo->mutexes->eaten, NULL);
	if (ret)
	{
		pthread_mutex_destroy(&philo->mutexes->stop);
		return (ret);
	}
	ret = pthread_mutex_init(&philo->mutexes->print, NULL);
	if (ret)
	{
		pthread_mutex_destroy(&philo->mutexes->stop);
		pthread_mutex_destroy(&philo->mutexes->eaten);
		return (ret);
	}
	return (ret);
}

t_philo	*new_philo(t_philo *philo, int id)
{
	t_philo *new;
	int		ret;

	new = (t_philo *)ft_calloc(1, sizeof(t_philo));
	if (!new)
		return (NULL);
	new->id = id;
	new->num_of_chopsticks = 1;
	new->args = philo->args;
	new->mutexes = philo->mutexes;
	if (pthread_mutex_init(&new->chopstick, NULL))
	{
		free(new);
		return (NULL); //handle error
	}
	return (new);
}

t_philo	*last_philo(t_philo *philo)
{
	while (philo && philo->next)
		philo = philo->next;
	return (philo);
}

bool	init_philos(t_philo *philo, char **argv)
{
	int			i;
	t_philo		*new;

	parse_input(philo, argv);
	if (init_mutexes(philo))
		return (false); //handle error
	i = 0;
	while (i < philo->args.num_of_philos)
	{
		new = new_philo(philo, ++i);
		if (!new)
			return (false); //handle error
		if (i == 1)
			philo = new;
		else
			last_philo(philo)->next = new;
	}
	last_philo(philo)->next = philo;;
	return (true);
}
