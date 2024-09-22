/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 21:23:12 by hitran            #+#    #+#             */
/*   Updated: 2024/09/22 09:20:40 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool arg_error(char *argv, char *message)
{
	printf("Error\n");
	if (argv)
		printf("%s: ", argv);
	printf("%s\n", message);
	return (false);
}

static bool	is_valid_int(char *s)
{
	if (*s == '+')
		s++;
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (false);
		s++;
	}
	if (ft_strlen(s) > 10 || ft_atol(s) > MAX_INT)
		return (false);
	return (true);
}

static bool	is_valid_args(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (arg_error(NULL, "Invalid number of arguments"));
	while (++i < argc)
	{
		if (!is_valid_int(argv[i]))
			return (arg_error(argv[i], "Is not an integer"));
	}
	if (!ft_atol(argv[1]))
		return (arg_error(NULL, "At least 1 philosopher"));
	if (argc == 6 && !ft_atol(argv[5]))
		return (arg_error(NULL, "At least 1 time to eat"));
	return (true);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;

	if (!is_valid_args(argc, argv))
		return (EXIT_FAILURE);
	memset(philo, 0, sizeof(t_philo));
	if (!init_philos(philo, argv))
		return(EXIT_FAILURE);
	if (!start_program(philo))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
