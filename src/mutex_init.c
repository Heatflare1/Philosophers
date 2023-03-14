/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:43:14 by jmeruma           #+#    #+#             */
/*   Updated: 2023/03/14 14:24:56 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fork_mutex_init(t_bin *bin)
{
	int	fork_index;

	fork_index = 0;
	while (fork_index < bin->number_of_philo)
	{
		if (pthread_mutex_init(&(bin->fork[fork_index]), NULL))
		{
			fork_mutex_destroy(bin->fork, fork_index - 1);
			return (error("Fork_Mutex"));
		}
		fork_index++;
	}
	return (EXIT_SUCCESS);
}

int	monitor_print_mutex_init(t_bin *bin)
{
	if (pthread_mutex_init(&(bin->monitor), NULL))
	{
		fork_mutex_destroy(bin->fork, bin->number_of_philo - 1);
		return (error("Monitor_Mutex"));
	}
	if (pthread_mutex_init(&(bin->printing), NULL))
	{
		monitor_mutex_destroy(bin);
		return (error("Printing_Mutex"));
	}
	return (EXIT_SUCCESS);
}

int	philo_mutex_init(t_philo *philo, t_bin *bin)
{
	int	philo_index;

	philo_index = 0;
	while (philo_index < bin->number_of_philo)
	{
		if (pthread_mutex_init(&(philo[philo_index].eating_mutex), NULL))
		{
			philo_mutex_destroy(philo, philo_index - 1);
			return (error("Philo_Mutex"));
		}
		philo_index++;
	}
	return (EXIT_SUCCESS);
}
