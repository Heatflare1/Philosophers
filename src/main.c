/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisse <jisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:04:11 by jisse             #+#    #+#             */
/*   Updated: 2023/03/03 15:04:52 by jisse            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waiting_all_threads(pthread_t monitor_thread, pthread_t *thread, t_bin *bin)
{
	int	i;
	
	i = 0;
	while (i < bin->number_of_philo)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
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
	return (EXIT_SUCCESS);
}

int	thread_creation(pthread_t *monitor_thread, t_philo *philo, pthread_t *thread, t_bin *bin)
{
	int	i;

	i = 0;
	while (i < bin->number_of_philo)
	{
		philo[i].bin = bin;
		philo[i].philo_tag = i + 1;
		fork_input(&philo[i], i);
		if(pthread_create(&thread[i], NULL, &test, &philo[i]))
		{
			printf("Pthread_Error\n");
			mutex_destroy(bin);
			return (EXIT_FAILURE);
		}
		i++;
	}
	if (pthread_create(monitor_thread, NULL, &monitoring, philo))
	{
		printf("Pthread_Error\n");
		mutex_destroy(bin);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_bin			bin;
	t_philo			*philo;
	pthread_t		*thread;
	pthread_t		monitor_thread;

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
	if(thread_creation(&monitor_thread, philo, thread, &bin))
		return (malloc_free(thread, philo, &bin));
	waiting_all_threads(monitor_thread, thread, &bin);
}