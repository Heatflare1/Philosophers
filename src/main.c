/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisse <jisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:04:11 by jisse             #+#    #+#             */
/*   Updated: 2023/02/14 16:20:21 by jisse            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

useconds_t microseconds(unsigned int milliseconds)
{
	return (milliseconds * 1000);
} 

int	error_exit(char *message)
{
	printf("%s: Error\n", message);
	return (EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	t_philo philo;
	struct timeval end;
	struct timeval start;

	if (argc != 5 && argc != 6)
		return (error_exit("Argument"));
	if (argument_conversion(&philo, argc, argv))
		return (error_exit("Parsing"));
	gettimeofday(&start, NULL);
	printf("philo = %d, time_die = %d, time_eat = %d, time_sleep = %d, philo_must_eat = %d\n", \
	philo.number_of_philo, philo.time_to_die, philo.time_to_eat, philo.time_to_sleep, philo.each_philo_must_eat);
	gettimeofday(&end, NULL);
	printf("milli-seconds = %ld\n", ((end.tv_sec * 1000) + (end.tv_usec / 1000)) - ((start.tv_sec * 1000) + (start.tv_usec / 1000)));
}