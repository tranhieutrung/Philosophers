/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:32:34 by hitran            #+#    #+#             */
/*   Updated: 2024/10/24 13:26:46 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status	arg_error(char *argv, char *message)
{
	write(2, "Error: ", 7);
	if (argv)
	{
		write(2, argv, ft_strlen(argv));
		write(2, ": ", 2);
	}
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
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

static t_status	is_valid_args(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (arg_error(NULL, "Invalid number of arguments."));
	while (++i < argc)
	{
		if (ft_atopi(argv[i]) <= 0)
			return (arg_error(argv[i], "Is invalid."));
	}
	return (SUCCESS);
}

t_status	parse_input(t_philo *philo, int argc, char **argv)
{
	memset(philo, 0, sizeof(t_philo));
	if (is_valid_args(argc, argv) == ERROR)
		return (ERROR);
	philo->total = ft_atopi(argv[1]);
	philo->time_to_die = ft_atopi(argv[2]);
	philo->time_to_eat = ft_atopi(argv[3]);
	philo->time_to_sleep = ft_atopi(argv[4]);
	if (argv[5])
		philo->meals = ft_atopi(argv[5]);
	else
		philo->meals = -1;
	return (SUCCESS);
}
