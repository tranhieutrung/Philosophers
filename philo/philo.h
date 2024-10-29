/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:11:41 by hitran            #+#    #+#             */
/*   Updated: 2024/10/29 22:16:11 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>		// write, usleep
# include <stdlib.h>		// mallo, free, NULL
# include <pthread.h>		// thread
# include <stdio.h>			// printf
# include <sys/time.h>		// gettimeofday
# include <string.h>		// memset

# define MAX_INT 2147483647

typedef struct s_thread
{
	pthread_t		thread;
	int				id;
	int				eaten_times;
	long			last_eaten_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
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
	int				total;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals;
	int				full_total;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	t_thread		*threads;
	t_status		status;
	long			start_time;
}	t_philo;

//----------------------------||     PHILO      ||----------------------------//
t_status	parse_input(t_philo *philo, int argc, char **argv);
t_status	init_philo(t_philo *philo);
void		*routine(void *arg);
t_status	simulate_philo(t_philo *philo);

//----------------------------||  ROUTINE UTILS ||----------------------------//

t_status	check_status(t_philo *philo);
t_status	waiting(long ms, t_philo *philo);
t_status	print_action(t_thread *thread, char *message);
t_status	unlock_return(pthread_mutex_t *mutex1, pthread_mutex_t *mutex2);
void		set_finish(t_philo *philo);

//----------------------------||     UTILS      ||----------------------------//

int			ft_strlen(char *s);
long		get_millisecond(void);
t_status	free_philo(t_philo *philo);
t_status	philo_error(t_philo *philo, char *message);

#endif
