/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:04:11 by jisse             #+#    #+#             */
/*   Updated: 2023/03/14 14:25:51 by jmeruma          ###   ########.fr       */
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
		if (pthread_create(&thread[i], NULL, &philosophers, &philo[i]))
		{
			bin->number_of_threads_created = i;
			pthread_mutex_unlock(&(bin->monitor));
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
	if (monitor_print_mutex_init(&bin))
		return (malloc_error_free(thread, philo, &bin));
	if (philo_mutex_init(philo, &bin))
		return (malloc_error_free(thread, philo, &bin));
	if (thread_creation(philo, thread, &bin))
	{
		waiting_all_threads(thread, &bin);
		all_mutex_destroy(philo);
		return (malloc_error_free(thread, philo, &bin));
	}
	monitoring(philo);
	waiting_all_threads(thread, &bin);
	philo_cleaning(philo, thread);
}
