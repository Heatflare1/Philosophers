/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:53:35 by jmeruma           #+#    #+#             */
/*   Updated: 2023/03/07 16:44:46 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printing(t_philo *philo, int action)
{
	unsigned long	time;

	time = gimme_time_micro() - philo->bin->start_of_the_day;
	time /= MICRO_SECONDS;
	if (action == DIED)
		printf("%ld %d died\n", time, philo->philo_tag);
	else if (action == THINKING)
			printf("%ld %d is thinking\n", time, philo->philo_tag);
	else if (action == FORK)
			printf("%ld %d has taken a fork\n", time, philo->philo_tag);
	else if (action == SLEEPING)
			printf("%ld %d is sleeping\n", time, philo->philo_tag);
	else if (action == EATING)
			printf("%ld %d is eating\n", time, philo->philo_tag);
}

void	*monitoring(t_philo *philo)
{
	int		i;

	i = 0;
	while(true)
	{
		pthread_mutex_lock(&(philo[i].eating_mutex));
		if (gimme_time_micro() - philo[i].time_alive > philo->bin->time_to_die && philo[i].time_alive != 0)
		{
			pthread_mutex_unlock(&(philo[i].eating_mutex));
			printing(&philo[i], DIED);
			exit(0);
			break;
		}
		pthread_mutex_unlock(&(philo[i].eating_mutex));
		i++;
		if (philo->bin->number_of_philo == i)
			i = 0;
	}
	return (NULL);
}