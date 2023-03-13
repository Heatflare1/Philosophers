/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisse <jisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:04:11 by jisse             #+#    #+#             */
/*   Updated: 2023/03/13 16:08:25 by jisse            ###   ########.fr       */
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
			fork_mutex_destroy(bin->fork, fork_index - 1);
			return (error("Fork_Mutex"));
		}
		fork_index++;
	}
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

int	thread_creation(t_philo *philo, pthread_t *thread, t_bin *bin)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(bin->monitor));
	while (i < bin->number_of_philo)
	{
		philo[i].bin = bin;
		philo[i].philo_tag = i + 1;
		philo[i].done_eating = false;
		philo[i].number_times_eated = 0;
		fork_input(&philo[i], i);
		if(pthread_create(&thread[i], NULL, &philosophers, &philo[i]))
		{
			bin->number_of_threads_created = i;
			pthread_mutex_unlock(&(bin->monitor));
			all_mutex_destroy(philo);
			return (error("Pthread"));
		}
		i++;
	}
	bin->philo_starved = false;
	bin->number_of_threads_created = i;
	bin->start_of_the_day = gimme_time_micro();
	pthread_mutex_unlock(&(bin->monitor));
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_bin			bin;
	t_philo			*philo;
	pthread_t		*thread;

	if (argc != 5 && argc != 6)
		return (error("Argument"));
	if (argument_conversion(&bin, argc, argv))
		return (error("Parsing"));
	thread = malloc(bin.number_of_philo * sizeof(pthread_t));
	bin.fork = malloc(bin.number_of_philo * sizeof(pthread_mutex_t));
	philo = malloc(bin.number_of_philo * sizeof(t_philo));
	if (!thread || !(bin.fork) || !philo)
		return (malloc_error_free(thread, philo, &bin));
	if (fork_mutex_init(&bin))
		return (malloc_error_free(thread, philo, &bin));
	if (philo_mutex_init(philo, &bin))
		return (malloc_error_free(thread, philo, &bin));
	if (thread_creation(philo, thread, &bin))
		return (malloc_error_free(thread, philo, &bin));
	monitoring(philo);
	waiting_all_threads(thread, &bin);
	philo_cleaning(philo, thread);
}