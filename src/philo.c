/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisse <jisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:29:20 by jmeruma           #+#    #+#             */
/*   Updated: 2023/03/03 15:40:58 by jisse            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*test(void *arg)
{
	t_philo *philo;
	
	philo = arg;
	while (!philo->bin->program_start)
		;
	philo->time_alive = philo->bin->start_of_the_day;
	printf("philo [%d]\n", philo->philo_tag);
	sleep_tight_philo(philo->bin->time_to_sleep);
	philo->time_alive = 0;
	return (NULL);
}