/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:11:41 by hitran            #+#    #+#             */
/*   Updated: 2024/09/25 15:29:24 by hitran           ###   ########.fr       */
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
# include <string.h>		// memset

# define MAX_INT 2147483647

// typedef struct s_arg
// {
// 	int	num_of_philos;
// 	int	time_to_die;
// 	int	time_to_eat;
// 	int	time_to_sleep;
// 	int	num_of_meals;
// } t_arg;

// typedef struct s_mutex
// {
// 	int	stop;
// 	int	eaten;
// 	pthread_mutex_t	finish;
// 	pthread_mutex_t	eaten;
// 	pthread_mutex_t	print;
// } t_mutex;

typedef struct s_thread
{
	pthread_t		thread;
	size_t			id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
} t_thread;

typedef enum e_status
{
	ATE,
	DIED,
	FINISH
} t_status;

typedef struct s_philo
{
	size_t			num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			num_of_meals;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*lock;
	t_thread		*threads;
	t_status		status;
	long			millisecond;
} t_philo;

//----------------------------||     PHILO      ||----------------------------//
bool	parse_input(t_philo *philo, int argc, char **argv);
bool	init_philos(t_philo *philo);
bool	start_program(t_philo *philo);

//----------------------------||     UTILS      ||----------------------------//

// size_t	ft_strlen(const char *s);
// long	ft_atol(const char *s);
// void	*ft_calloc(size_t count, size_t size);
void	ft_putstr_fd(int fd, char *s);
long	get_time(void);
bool	free_philo(t_philo *philo);

#endif
