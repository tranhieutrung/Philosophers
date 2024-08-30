/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:11:41 by hitran            #+#    #+#             */
/*   Updated: 2024/08/30 22:18:32 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>   // write, usleep
# include <stdlib.h>   // mallo, free, NULL
# include <pthread.h>  // thread
# include <stdio.h>    // printf
# include <sys/time.h> // gettimeofday

//----------| UTILS |----------//
size_t	ft_strlen(const char *s);
long	ft_atol(const char *s);

#endif
