/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:18:54 by hitran            #+#    #+#             */
/*   Updated: 2024/08/30 22:24:50 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>	// write, usleep, fork
# include <stdlib.h>	// mallo, free, NULL
# include <pthread.h>	// thread
# include <stdio.h>		// printf
# include <sys/time.h>	// gettimeofday
# include <sys/wait.h>	// waitpid
# include <semaphore.h> // sem
# include <signal.h>    // signal

//----------| UTILS |----------//
size_t	ft_strlen(const char *s);
long	ft_atol(const char *s);

#endif
