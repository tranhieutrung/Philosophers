/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 21:23:12 by hitran            #+#    #+#             */
/*   Updated: 2024/09/03 22:19:56 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (!is_valid_args(argc, argv))
		return (EXIT_FAILURE);
	if (!start_philo(&philo, argv))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
