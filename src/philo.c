/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:29:20 by jmeruma           #+#    #+#             */
/*   Updated: 2023/02/23 18:33:00 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*test(void *arg)
{
	t_philo *philo;
	
	philo = arg;
	printf("philo [%d] - ", philo->philo_tag);
	printf("die = %d\n", philo->bin->time_to_die);
	sleep_tight_philo(philo->bin->time_to_sleep);
	return (NULL);
}