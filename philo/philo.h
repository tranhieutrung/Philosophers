/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:11:41 by hitran            #+#    #+#             */
/*   Updated: 2024/09/03 22:25:03 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>		// write, usleep
# include <stdlib.h>		// mallo, free, NULL
# include <pthread.h>		// thread
# include <stdio.h>			// printf
# include <sys/time.h>		// gettimeofday
# include <stdbool.h>		// bool

# define MAX_INT 2147483647

typedef struct s_philo
{
	int		number;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		meals;
} t_philo;

bool	is_valid_args(int argc, char **argv);
bool	start_philo(t_philo *philo, char **argv);

//----------| UTILS |----------//
size_t	ft_strlen(const char *s);
long	ft_atol(const char *s);

#endif
