/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:29:20 by jmeruma           #+#    #+#             */
/*   Updated: 2023/03/09 14:39:12 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#define DEATH 1

int	sleeping(t_philo *philo)
{
	if (printing(philo, SLEEPING) == DEATH)
		return (true);
	sleep_tight_philo(philo, philo->bin->time_to_sleep);
	return (false);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (printing(philo, FORK) == DEATH)
		return (true);
	pthread_mutex_lock(philo->right_fork);
	if (printing(philo, FORK) == DEATH)
		return (true);
	pthread_mutex_lock(&(philo->eating_mutex));
	philo->time_alive = gimme_time_micro();
	pthread_mutex_unlock(&(philo->eating_mutex));
	if (printing(philo, EATING) == DEATH)
		return (true);
	sleep_tight_philo(philo, philo->bin->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (false);
}

void	group_one(t_philo *philo)
{
	while (true)
	{
		if (sleeping(philo) == DEATH)
			break;
		if (printing(philo, THINKING) == DEATH)
			break;
		if (eating(philo) == DEATH)
			break;
	}
}
void	group_two(t_philo *philo)
{
	while (true)
	{
		if (printing(philo, THINKING) == DEATH)
			break;
		if (eating(philo) == DEATH)
			break;
		if (sleeping(philo) == DEATH)
			break;
	}
}

void	*philosophers(void *arg)
{
	t_philo *philo;
	
	philo = arg;
	pthread_mutex_lock(&(philo->bin->monitor));
	pthread_mutex_unlock(&(philo->bin->monitor));
	pthread_mutex_lock(&(philo->eating_mutex));
	philo->time_alive = philo->bin->start_of_the_day;
	pthread_mutex_unlock(&(philo->eating_mutex));
	if (philo->philo_tag % 2)
		group_one(philo);
	else
		group_two(philo);
	return (NULL);
}