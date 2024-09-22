/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:11:41 by hitran            #+#    #+#             */
/*   Updated: 2024/09/22 09:31:52 by hitran           ###   ########.fr       */
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

typedef struct s_arg
{
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_meals;
} t_arg;

typedef struct s_mutex
{
	int	stop;
	int	eaten;
	pthread_mutex_t	stop;
	pthread_mutex_t	eaten;
	pthread_mutex_t	print;
} t_mutex;

typedef struct s_status
{
	int	ate;
	int	died;
	int	finish;
} t_status;

typedef struct s_philo
{
	int				id;
	int				num_of_chopsticks;
	t_arg			args;
	t_mutex			*mutexes;
	t_status		status;
	pthread_mutex_t	chopstick;
	struct s_philo	*next;
} t_philo;

//----------------------------||     PHILO      ||----------------------------//

bool	init_philos(t_philo *philo, char **argv);
bool	start_program(t_philo *philo);

//----------------------------||     UTILS      ||----------------------------//

size_t	ft_strlen(const char *s);
long	ft_atol(const char *s);
void	*ft_calloc(size_t count, size_t size);

#endif
