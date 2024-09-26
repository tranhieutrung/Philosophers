/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:32:34 by hitran            #+#    #+#             */
/*   Updated: 2024/09/26 23:35:54 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status	arg_error(char *argv, char *message)
{
	ft_putstr_fd(2, "Error: ");
	if (argv)
	{
		ft_putstr_fd(2, argv);
		ft_putstr_fd(2, ": ");
	}
	ft_putstr_fd(2, message);
	ft_putstr_fd(2, "\n");
	return (ERROR);
}

static long	ft_atopi(char *s)
{
	long	number;

	if (*s == '+')
		s++;
	number = 0;
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (-1);
		number = (number * 10) + (*s - '0');
		if (number > MAX_INT)
			return (-1);
		s++;
	}
	return (number);
}

t_status	is_valid_args(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (arg_error(NULL, "Invalid number of arguments"));
	while (++i < argc)
	{
		if (ft_atopi(argv[i]) <= 0)
			return (arg_error(argv[i], "Is invalid"));
	}
	return (SUCCESS);
}

t_status	parse_input(t_philo *philo, int argc, char **argv)
{
	memset(philo, 0, sizeof(t_philo));
	if (is_valid_args(argc, argv) == ERROR)
		return (ERROR);
	philo->num_of_philos = ft_atopi(argv[1]);
	philo->time_to_die = ft_atopi(argv[2]);
	philo->time_to_eat = ft_atopi(argv[3]);
	philo->time_to_sleep = ft_atopi(argv[4]);
	if (argv[5])
		philo->num_of_meals = ft_atopi(argv[5]);
	else
		philo->num_of_meals = -1;
	return (SUCCESS);
}
