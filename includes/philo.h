/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:04:07 by jisse             #+#    #+#             */
/*   Updated: 2023/03/02 16:36:03 by jmeruma          ###   ########.fr       */
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

# define MICRO_SECONDS 1000
typedef struct s_bin
{
	int				number_of_philo;
	int				each_philo_must_eat;
	bool			eat_till_full;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned long	start_of_the_day;
	pthread_mutex_t	*fork;
}	t_bin;

typedef struct s_philo
{
	
	int				philo_tag;
	t_bin 			*bin;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t *right_fork;
}	t_philo;

// parce
void	fork_input(t_philo *philo, int index);
int		argument_conversion(t_bin *bin, int argc, char *argv[]);

//philo
void	*test(void *arg);

//Cleanup
int	error_exit(char *message);
int	malloc_free(pthread_t *thread, t_philo *philo, t_bin *bin);
int	mutex_destroy(t_bin *bin);

//Time
unsigned long	gimme_time_micro(void);
unsigned long	gimme_time_milli(void);
void			sleep_tight_philo(unsigned int time);

#endif