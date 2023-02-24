/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:04:07 by jisse             #+#    #+#             */
/*   Updated: 2023/02/23 18:31:59 by jmeruma          ###   ########.fr       */
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
pthread_mutex_t lock;
typedef struct s_bin
{
	int				number_of_philo;
	int				each_philo_must_eat;
	bool			eat_till_full;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	pthread_mutex_t	*fork;
}	t_bin;

typedef struct s_philo
{
		
	t_bin 			*bin;
	int				philo_tag;
}	t_philo;

// parce
int	argument_conversion(t_bin *bin, int argc, char *argv[]);

//philo
void	*test(void *arg);

//Cleanup
int	error_exit(char *message);
int	malloc_free(pthread_t *thread, t_philo *philo, t_bin *bin);
int	mutex_destroy(t_bin *bin);

//Time
void	sleep_tight_philo(unsigned int time);

#endif