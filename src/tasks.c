/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:43:42 by jmeruma           #+#    #+#             */
/*   Updated: 2023/03/14 15:16:12 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleeping(t_philo *philo)
{
	if (printing(philo, SLEEPING) == false)
		return (false);
	sleep_tight_philo(philo, philo->bin->time_to_sleep);
	return (true);
}

bool	grab_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (printing(philo, FORK) == false)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (false);
	}
	pthread_mutex_lock(philo->right_fork);
	if (printing(philo, FORK) == false)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (false);
	}
	return (true);
}

int	eating(t_philo *philo)
{
	if (grab_forks(philo) == false)
		return (false);
	pthread_mutex_lock(&(philo->eating_mutex));
	philo->time_alive = gimme_time_micro();
	pthread_mutex_unlock(&(philo->eating_mutex));
	if (printing(philo, EATING) == false)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (false);
	}
	if (philo->bin->eat_till_full)
	{
		pthread_mutex_lock(&(philo->eating_mutex));
		philo->number_times_eated++;
		pthread_mutex_unlock(&(philo->eating_mutex));
	}
	sleep_tight_philo(philo, philo->bin->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (true);
}
