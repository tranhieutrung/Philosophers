/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:38:43 by hitran            #+#    #+#             */
/*   Updated: 2024/09/03 22:39:28 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_input(t_philo *philo, char **argv)
{
	philo->number = ft_atol(argv[1]);
	philo->time_die = ft_atol(argv[2]);
	philo->time_eat = ft_atol(argv[3]);
	philo->time_sleep = ft_atol(argv[4]);
	if (argv[5])
		philo->meals = ft_atol(argv[5]);
	else
		philo->meals = -1;
}

bool	start_philo(t_philo *philo, char **argv)
{
	parse_input(philo, argv);
	return (true);
}