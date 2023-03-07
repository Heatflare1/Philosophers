/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:53:35 by jmeruma           #+#    #+#             */
/*   Updated: 2023/03/07 13:51:37 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printing(t_philo *philo, char *color, char *message)
{
	unsigned long	time;

	time = gimme_time_micro() - philo->bin->start_of_the_day;
	time /= MICRO_SECONDS;
	printf("%stime-ms [%ld]%s Philo [%d] %s%s%s\n", C_GREEN, time, \
			C_RESET, philo->philo_tag, color, message, C_RESET);
}

void	*monitoring(t_philo *philo)
{
	int		i;

	i = 0;
	while(true)
	{
		pthread_mutex_lock(&(philo[i].eating_mutex));
		if (gimme_time_micro() - philo[i].time_alive >= philo->bin->time_to_die && philo[i].time_alive != 0)
		{
			pthread_mutex_unlock(&(philo[i].eating_mutex));
			printing(&philo[i], C_LRED, "died");
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