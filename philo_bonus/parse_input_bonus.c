/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:32:34 by hitran            #+#    #+#             */
/*   Updated: 2024/10/03 12:55:31 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		return (arg_error(NULL, "Invalid number of arguments"));
	while (++i < argc)
	{
		if (ft_atopi(argv[i]) <= 0)
			return (arg_error(argv[i], "Is invalid"));
		else if (ft_atopi(argv[1]) > 498)
			return (arg_error(NULL,
					"The program can only simulate up to 498 philosophers."));
		else if (i > 1 && i < 5 && ft_atopi(argv[i]) <= 10)
			return (arg_error(argv[i], "The time must be greater than 10ms"));
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
