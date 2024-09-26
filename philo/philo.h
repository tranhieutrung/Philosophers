/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:11:41 by hitran            #+#    #+#             */
/*   Updated: 2024/09/26 15:05:07 by hitran           ###   ########.fr       */
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

typedef struct s_thread
{
	pthread_t		thread;
	size_t			id;
	size_t			eaten_times;
	long			last_eaten_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_philo	*philo;
} t_thread;

typedef enum e_status
{
	RUNNING,
	FINISH
} t_status;

typedef struct s_philo
{
	size_t			num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			num_of_meals;
	size_t			num_of_full_philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	t_thread		*threads;
	t_status		status;
	long			start_time;
} t_philo;

//----------------------------||     PHILO      ||----------------------------//
bool	parse_input(t_philo *philo, int argc, char **argv);
bool	init_philo(t_philo *philo);
void	*philo_routine(void *arg);
bool	simulate_philo(t_philo *philo);

//----------------------------||  ROUTINE UTILS ||----------------------------//

t_status	check_status(t_philo *philo);
bool		waiting(long ms, t_philo *philo);
bool		print_action(t_thread *thread, char *message);

//----------------------------||     UTILS      ||----------------------------//

void	ft_putstr_fd(int fd, char *s);
long	get_millisecond(void);
bool	free_philo(t_philo *philo);
bool 	philo_error(t_philo *philo, char *message);

#endif
