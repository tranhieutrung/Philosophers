/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:11:41 by hitran            #+#    #+#             */
/*   Updated: 2024/10/03 15:46:29 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>		// write, usleep
# include <stdlib.h>		// mallo, free, NULL
# include <pthread.h>		// thread
# include <stdio.h>			// printf
# include <sys/time.h>		// gettimeofday
# include <string.h>		// memset, strerror
# include <semaphore.h>		// semaphore
# include <fcntl.h>			// O_CREAT, O_EXCL
#include <errno.h>    		// errno

# define MAX_INT 2147483647

typedef struct s_thread
{
	pthread_t		thread;
	int				id;
	int				eaten_times;
	long			last_eaten_time;
	struct s_philo	*philo;
}	t_thread;

typedef enum e_status
{
	RUNNING,
	FINISH,
	SUCCESS,
	ERROR
}	t_status;

typedef struct s_philo
{
	int			num_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_of_meals;
	int			num_of_full_philos;
	sem_t		*chopsticks;
	sem_t		*lock;
	t_thread	*threads;
	t_status	status;
	long		start_time;
}	t_philo;

//----------------------------||     PHILO      ||----------------------------//
t_status	parse_input(t_philo *philo, int argc, char **argv);
t_status	init_philo(t_philo *philo);
void		*philo_routine(void *arg);
t_status	simulate_philo(t_philo *philo);

//----------------------------||  ROUTINE UTILS ||----------------------------//

t_status	check_status(t_philo *philo);
t_status	waiting(long ms, t_philo *philo);
t_status	print_action(t_thread *thread, char *message);
t_status	unlock_return(pthread_mutex_t *mutex1, pthread_mutex_t *mutex2);

//----------------------------||     UTILS      ||----------------------------//

int			ft_strlen(char *s);
long		get_millisecond(void);
t_status	free_philo(t_philo *philo);
t_status	philo_error(t_philo *philo, char *message);

#endif
