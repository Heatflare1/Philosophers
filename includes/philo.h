/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisse <jisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:04:07 by jisse             #+#    #+#             */
/*   Updated: 2023/03/12 16:26:19 by jisse            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <string.h>
# include "h_colors.h"

# define MICRO_SECONDS 1000
# define DIED		0
# define EATING		1
# define SLEEPING	2
# define THINKING	3
# define FORK		4


typedef struct s_bin
{
	int				number_of_philo;
	int				each_philo_must_eat;
	int				number_of_philo_full;
	bool			eat_till_full;
	bool			philo_starved;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned long	start_of_the_day;
	pthread_mutex_t	*fork;
	pthread_mutex_t monitor;
	pthread_mutex_t printing;
}	t_bin;

typedef struct s_philo
{
	
	int				philo_tag;
	int				number_times_eated;
	bool			done_eating;
	t_bin 			*bin;
	unsigned long	time_alive;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t	eating_mutex;
}	t_philo;

// parce
void	fork_input(t_philo *philo, int index);
int		argument_conversion(t_bin *bin, int argc, char *argv[]);

//philo
void	*philosophers(void *arg);

//Cleanup
int	error_exit(char *message);
int	malloc_free(pthread_t *thread, t_philo *philo, t_bin *bin);
int	mutex_destroy(t_bin *bin);

//Time
unsigned long	gimme_time_micro(void);
unsigned long	gimme_time_milli(void);
void			sleep_tight_philo(t_philo *philo, unsigned int time);

//Monitoring
void		monitoring(t_philo *philo);
int			printing(t_philo *philo, int action);

#endif