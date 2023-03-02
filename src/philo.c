/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:29:20 by jmeruma           #+#    #+#             */
/*   Updated: 2023/03/02 13:14:50 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*test(void *arg)
{
	t_philo *philo;
	
	philo = arg;
	printf("philo [%d] - ", philo->philo_tag - 1);
	printf("die = %d\n", philo->bin->time_to_die);
	printf("left-fork = %p |", philo->left_fork);
	printf(" right-fork = %p\n", philo->right_fork);
	sleep_tight_philo(philo->bin->time_to_sleep);
	return (NULL);
}