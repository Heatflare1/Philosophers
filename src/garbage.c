/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:11:08 by jmeruma           #+#    #+#             */
/*   Updated: 2023/02/17 15:11:37 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void stuff(void)
{
	gettimeofday(&start, NULL);
	pthread_create(&thd, NULL, &test, NULL);
	pthread_create(&thd, NULL, &test, NULL);
	pthread_join(thd, NULL);
	printf("finished :D\n");
	gettimeofday(&end, NULL);
	printf("philo = %d, time_die = %d, time_eat = %d, time_sleep = %d, philo_must_eat = %d\n", \
	philo.number_of_philo, philo.time_to_die, philo.time_to_eat, philo.time_to_sleep, philo.each_philo_must_eat);
	printf("milli-seconds = %ld\n", ((end.tv_sec * 1000) + (end.tv_usec / 1000)) - ((start.tv_sec * 1000) + (start.tv_usec / 1000)));
	gettimeofday(&start, NULL);
	test(&philo);
	test(&philo);
	printf("cheese :D\n");
	gettimeofday(&end, NULL);
	printf("philo = %d, time_die = %d, time_eat = %d, time_sleep = %d, philo_must_eat = %d\n", \
	philo.number_of_philo, philo.time_to_die, philo.time_to_eat, philo.time_to_sleep, philo.each_philo_must_eat);
	printf("milli-seconds = %ld\n", ((end.tv_sec * 1000) + (end.tv_usec / 1000)) - ((start.tv_sec * 1000) + (start.tv_usec / 1000)));
}