/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:49:42 by jmeruma           #+#    #+#             */
/*   Updated: 2023/03/09 15:02:10 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	gimme_time_micro(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000000) + time.tv_usec);
}

unsigned long	gimme_time_milli(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * MICRO_SECONDS) + (time.tv_usec / MICRO_SECONDS));
}

void	sleep_loop(t_philo *philo, long	big_time, unsigned long end)
{
	bool philo_died;

	pthread_mutex_lock(&(philo->bin->monitor));
	philo_died = philo->bin->philo_starved;
	pthread_mutex_unlock(&(philo->bin->monitor));
	if (big_time > 0 && philo_died == false)
		usleep(big_time);
	while(gimme_time_micro() <= end)
	{
		pthread_mutex_lock(&(philo->bin->monitor));
		philo_died = philo->bin->philo_starved;
		pthread_mutex_unlock(&(philo->bin->monitor));
		if (philo_died == true)
			break;
		usleep(5);
	}
}

void	sleep_tight_philo(t_philo *philo, unsigned int time)
{
	long			big_time;
	unsigned long	end;
	unsigned long	start;

	start = gimme_time_micro();
	end = start + time;
	big_time = time / 3;
	sleep_loop(philo, big_time, end);
}
