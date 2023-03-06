/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:29:20 by jmeruma           #+#    #+#             */
/*   Updated: 2023/03/06 16:42:05 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*test(void *arg)
{
	t_philo *philo;
	
	philo = arg;
	pthread_mutex_lock(&(philo->bin->monitor));
	pthread_mutex_unlock(&(philo->bin->monitor));
	pthread_mutex_lock(&(philo->eating_mutex));
	philo->time_alive = philo->bin->start_of_the_day;
	pthread_mutex_unlock(&(philo->eating_mutex));
	printf("philo [%d]\n", philo->philo_tag);
	sleep_tight_philo(philo->bin->time_to_sleep);
	pthread_mutex_lock(&(philo->eating_mutex));
	philo->time_alive = 0;
	pthread_mutex_unlock(&(philo->eating_mutex));
	return (NULL);
}