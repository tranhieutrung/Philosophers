/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 21:23:12 by hitran            #+#    #+#             */
/*   Updated: 2024/09/26 23:36:41 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo		philo;

	if (parse_input(&philo, argc, argv) == ERROR)
		return (EXIT_FAILURE);
	if (init_philo(&philo) == ERROR)
		return (EXIT_FAILURE);
	if (simulate_philo(&philo) == ERROR)
		return (EXIT_FAILURE);
	free_philo(&philo);
	return (EXIT_SUCCESS);
}
