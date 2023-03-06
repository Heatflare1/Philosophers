/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:04:11 by jisse             #+#    #+#             */
/*   Updated: 2023/03/06 16:52:20 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waiting_all_threads(pthread_t *thread, t_bin *bin)
{
	int	i;
	
	i = 0;
	while (i < bin->number_of_philo)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
}

int	fork_mutex_init(t_bin *bin)
{
	int	fork_index;

	fork_index = 0;
	while (fork_index < bin->number_of_philo)
	{
		if (pthread_mutex_init(&(bin->fork[fork_index]), NULL))
		{
			printf("Mutex_Error\n");
			mutex_destroy(bin);
			return (EXIT_FAILURE);
		}
		fork_index++;
	}
	if (pthread_mutex_init(&(bin->monitor), NULL))
	{
		printf("Mutex_Error\n");
		mutex_destroy(bin);
		return (EXIT_FAILURE);
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
			printf("Mutex_Error\n");
			mutex_destroy(philo->bin);
			return (EXIT_FAILURE);
		}
		philo_index++;
	}
	return (EXIT_SUCCESS);
}

int	thread_creation(t_philo *philo, pthread_t *thread, t_bin *bin)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(bin->monitor));
	while (i < bin->number_of_philo)
	{
		philo[i].bin = bin;
		philo[i].philo_tag = i + 1;
		philo[i].time_alive = gimme_time_micro();
		fork_input(&philo[i], i);
		if(pthread_create(&thread[i], NULL, &test, &philo[i]))
		{
			printf("Pthread_Error\n");
			mutex_destroy(bin);
			return (EXIT_FAILURE);
		}
		i++;
	}
	philo->bin->start_of_the_day = gimme_time_micro();
	pthread_mutex_unlock(&(philo->bin->monitor));
	monitoring(philo);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_bin			bin;
	t_philo			*philo;
	pthread_t		*thread;

	if (argc != 5 && argc != 6)
		return (error_exit("Argument"));
	if (argument_conversion(&bin, argc, argv))
		return (error_exit("Parsing"));
	thread = malloc(bin.number_of_philo * sizeof(pthread_t));
	bin.fork = malloc(bin.number_of_philo * sizeof(pthread_mutex_t));
	philo = malloc(bin.number_of_philo * sizeof(t_philo));
	if (!thread || !(bin.fork) || !philo)
		return (malloc_free(thread, philo, &bin));
	if(fork_mutex_init(&bin))
		return (malloc_free(thread, philo, &bin));
	if(philo_mutex_init(philo, &bin))
		return (malloc_free(thread, philo, &bin));
	if(thread_creation(philo, thread, &bin))
		return (malloc_free(thread, philo, &bin));
	waiting_all_threads(thread, &bin);
}