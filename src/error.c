/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisse <jisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:26:38 by jisse             #+#    #+#             */
/*   Updated: 2023/03/13 15:36:48 by jisse            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *message)
{
	int i;

	i = 0;
	while (message[i])
		i++;
	write(STDERR_FILENO, message, i);
	write(STDERR_FILENO, ", Error\n", 8);
	return (EXIT_FAILURE);
}

int	malloc_error_free(pthread_t *thread, t_philo *philo, t_bin *bin)
{
	free(philo);
	free(thread);
	free(bin->fork);
	return (error("Malloc Allocation"));
}

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
	fork_mutex_destroy(bin->fork, bin->number_of_philo - 1);
	pthread_mutex_destroy(&(bin->monitor));
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