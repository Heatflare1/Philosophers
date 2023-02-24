/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:32:46 by jmeruma           #+#    #+#             */
/*   Updated: 2023/02/23 12:24:33 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	malloc_free(pthread_t *thread, t_philo *philo, t_bin *bin)
{
	free(philo);
	free(thread);
	free(bin->fork);
	printf("%s: Error\n", "Allocation Failed");
	return (EXIT_FAILURE);
}

int	error_exit(char *message)
{
	printf("%s, Error\n", message);
	return (EXIT_FAILURE);
}

int	mutex_destroy(t_bin *bin)
{
	int	fork_index;

	fork_index = 0;
	while (fork_index < bin->number_of_philo)
	{
		pthread_mutex_destroy(&(bin->fork[fork_index]));
		fork_index++;
	}
	return (EXIT_SUCCESS);
}