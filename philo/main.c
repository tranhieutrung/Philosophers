/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 21:23:12 by hitran            #+#    #+#             */
/*   Updated: 2024/08/30 22:36:17 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int arg_error(char *argv, char *message)
{
	printf("Error\n");
	if (argv)
		printf("%s: ", argv);
	printf("%s\n", message);
	return (EXIT_FAILURE);
}

int	is_not_number(char *s)
{
	if (*s == '+')
		s++;
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (1);
		s++;
	}
	return (0);
}

int	is_invalid_arguments(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (arg_error(NULL, "Invalid number of arguments"));
	while (++i < argc)
	{
		if (is_not_number(argv[i]))
			return (arg_error(argv[i], "Is not a (unsigned) number"));
		if (ft_strlen(argv[i]) > 10 || ft_atol(argv[i]) > 2147483647)
			return (arg_error(argv[i], "Is not an integer number"));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (is_invalid_arguments(argc, argv))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
