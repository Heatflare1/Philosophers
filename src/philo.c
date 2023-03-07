/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:29:20 by jmeruma           #+#    #+#             */
/*   Updated: 2023/03/07 14:57:15 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleeping(t_philo *philo)
{
	printing(philo, C_BLUE, "is sleeping");
	sleep_tight_philo(philo->bin->time_to_sleep);
	return (0);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printing(philo, C_BROWN, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&(philo->eating_mutex));
	philo->time_alive = gimme_time_micro();
	pthread_mutex_unlock(&(philo->eating_mutex));
	printing(philo, C_YELLOW, "is eating");
	sleep_tight_philo(philo->bin->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	thinking(t_philo *philo)
{
	printing(philo, C_PURPLE, "is thinking");
	return (0);
}

void	*test(void *arg)
{
	t_philo *philo;
	
	philo = arg;
	pthread_mutex_lock(&(philo->bin->monitor));
	pthread_mutex_lock(&(philo->eating_mutex));
	philo->time_alive = philo->bin->start_of_the_day;
	pthread_mutex_unlock(&(philo->eating_mutex));
	pthread_mutex_unlock(&(philo->bin->monitor));
	if (philo->philo_tag % 2)
		usleep(250);
	while (true)
	{
		if (thinking(philo))
			return (false);
		if (eating(philo))
			return (false);
		if (sleeping(philo))
			return (false);
	}
	return (NULL);
}