/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:53:35 by jmeruma           #+#    #+#             */
/*   Updated: 2023/03/09 14:35:07 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

const char	*task_array(int action)
{
	const char	*tasks[] = \
	{
		[DIED] = "died",
		[FORK] = "has taken a fork",
		[EATING] = "is eating",
		[SLEEPING] = "is sleeping",
		[THINKING] = "is thinking"
	};

	return (tasks[action]);
}

int	printing(t_philo *philo, int action)
{
	bool			philo_died;
	unsigned long	time;
	
	pthread_mutex_lock(&(philo->bin->monitor));
	philo_died = philo->bin->philo_starved;
	pthread_mutex_unlock(&(philo->bin->monitor));
	if (philo->bin->philo_starved == true && action != DIED)
		return (true);
	pthread_mutex_lock(&(philo->bin->printing));
	time = gimme_time_micro() - philo->bin->start_of_the_day;
	time /= MICRO_SECONDS;
	printf("%ld %d %s\n", time, philo->philo_tag, task_array(action));
	pthread_mutex_unlock(&(philo->bin->printing));
	return (false);
}

void	*monitoring(t_philo *philo)
{
	int				i;
	unsigned long	philo_last_meal;
	i = 0;
	while(true)
	{
		pthread_mutex_lock(&(philo[i].eating_mutex));
		philo_last_meal = philo[i].time_alive;
		pthread_mutex_unlock(&(philo[i].eating_mutex));
		if (gimme_time_micro() - philo_last_meal > philo->bin->time_to_die && philo_last_meal != 0)
		{
			pthread_mutex_lock(&(philo->bin->monitor));
			philo->bin->philo_starved = true;
			pthread_mutex_unlock(&(philo->bin->monitor));
			printing(&philo[i], DIED);
			break;
		}
		i++;
		if (philo->bin->number_of_philo == i)
			i = 0;
	}
	return (NULL);
}