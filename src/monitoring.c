/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisse <jisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:53:35 by jmeruma           #+#    #+#             */
/*   Updated: 2023/03/12 16:52:02 by jisse            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int index_checker(t_bin *bin, int i)
{
	i++;
	if (bin->number_of_philo == i)
		i = 0;
	return (i);
}

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

int	philo_eating_counter(t_philo *philo)
{
	int philo_times_eated;

	if (philo->done_eating)
		return (true);
	if (philo->bin->eat_till_full)
	{
		pthread_mutex_lock(&(philo->eating_mutex));
		philo_times_eated = philo->number_times_eated;
		pthread_mutex_unlock(&(philo->eating_mutex));
		//printf("philo[%d], times eaten = [%d] done eating [%d]\n", philo->philo_tag, philo_times_eated, philo->done_eating);
		if (philo_times_eated >= philo->bin->each_philo_must_eat)
		{
			philo->bin->number_of_philo_full++;
			philo->done_eating = true;
			printf("AAAAA\n");
			return (true);
		}
		return (false);
	}
	return (false);	
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

void	monitoring(t_philo *philo)
{
	int				i;
	unsigned long	philo_last_meal;

	i = 0;
	while(true)
	{
		if (philo_eating_counter(&philo[i]))
		{
			i = index_checker(philo->bin, i);
			if (philo->bin->number_of_philo_full == philo->bin->number_of_philo)
				break;
			continue;
		}
		pthread_mutex_lock(&(philo[i].eating_mutex));
		philo_last_meal = philo[i].time_alive;
		pthread_mutex_unlock(&(philo[i].eating_mutex));
		if (gimme_time_micro() - philo_last_meal > philo->bin->time_to_die && philo_last_meal != 0)
		{
			printing(&philo[i], DIED);
			break;
		}
		i = index_checker(philo->bin, i);
	}
	pthread_mutex_lock(&(philo->bin->monitor));
	philo->bin->philo_starved = true;
	pthread_mutex_unlock(&(philo->bin->monitor));
}