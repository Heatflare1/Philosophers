/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:35:34 by jmeruma           #+#    #+#             */
/*   Updated: 2023/03/14 13:37:59 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_mutex_destroy(pthread_mutex_t *fork, int fork_index)
{
	while (fork_index >= 0)
	{
		pthread_mutex_destroy(&(fork[fork_index]));
		fork_index--;
	}
}

void	monitor_mutex_destroy(t_bin *bin)
{
	fork_mutex_destroy(bin->fork, bin->number_of_philo - 1);
	pthread_mutex_destroy(&(bin->monitor));
}

void	printing_mutex_destroy(t_bin *bin)
{
	monitor_mutex_destroy(bin);
	pthread_mutex_destroy(&(bin->printing));
}

void	philo_mutex_destroy(t_philo *philo, int philo_index)
{
	while (philo_index >= 0)
	{
		pthread_mutex_destroy(&(philo[philo_index].eating_mutex));
		philo_index--;
	}
}

void	all_mutex_destroy(t_philo *philo)
{
	philo_mutex_destroy(philo, philo->bin->number_of_philo - 1);
	printing_mutex_destroy(philo->bin);
}
