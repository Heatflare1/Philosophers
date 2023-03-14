/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:29:20 by jmeruma           #+#    #+#             */
/*   Updated: 2023/03/14 15:45:33 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosopher_died(t_philo *philo)
{
	pthread_mutex_lock(&(philo->bin->monitor));
	philo->bin->philo_starved = true;
	pthread_mutex_unlock(&(philo->bin->monitor));
}

void	one_philo_problem(t_philo *philo)
{
	sleeping(philo);
	printing(philo, THINKING);
	printing(philo, FORK);
	sleep_tight_philo(philo, philo->bin->time_to_die);
}

void	group_one(t_philo *philo)
{
	while (true)
	{
		if (sleeping(philo) == false)
			break ;
		if (printing(philo, THINKING) == false)
			break ;
		if (eating(philo) == false)
			break ;
	}
}

void	group_two(t_philo *philo)
{
	while (true)
	{
		if (printing(philo, THINKING) == false)
			break ;
		if (eating(philo) == false)
			break ;
		if (sleeping(philo) == false)
			break ;
	}
}

void	*philosophers(void *arg)
{
	t_philo	*philo;

	philo = arg;
	pthread_mutex_lock(&(philo->bin->monitor));
	pthread_mutex_unlock(&(philo->bin->monitor));
	if (philo->bin->number_of_threads_created != philo->bin->number_of_philo)
		return (NULL);
	pthread_mutex_lock(&(philo->eating_mutex));
	philo->time_alive = gimme_time_micro();
	pthread_mutex_unlock(&(philo->eating_mutex));
	if (philo->bin->number_of_philo == 1)
	{
		one_philo_problem(philo);
		return (NULL);
	}
	if (philo->philo_tag % 2)
		group_one(philo);
	else
		group_two(philo);
	return (NULL);
}
