/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisse <jisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:53:35 by jmeruma           #+#    #+#             */
/*   Updated: 2023/03/03 15:41:23 by jisse            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printing(t_philo *philo, char *message)
{
	unsigned long	time;

	time = gimme_time_micro() - philo->bin->start_of_the_day;
	time /= MICRO_SECONDS;
	printf("time-ms [%ld] Philo [%d] %s\n", time, philo->philo_tag, message);
}

void	*monitoring(void *arg)
{
	int		i;
	t_philo	*philo;
	
	i = 0;
	philo = arg;
	philo->bin->start_of_the_day = gimme_time_micro();
	philo->bin->program_start = true;
	while(true)
	{
		if (gimme_time_micro() - philo[i].time_alive >= philo->bin->time_to_die && philo[i].time_alive != 0)
		{
			printing(&philo[i], "died");
			exit(0);
			break;
		}
		i++;
		if (philo->bin->number_of_philo - 1 == i)
			i = 0;
	}
	return (NULL);
}