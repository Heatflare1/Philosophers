/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:26:38 by jisse             #+#    #+#             */
/*   Updated: 2023/03/14 10:38:31 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *message)
{
	int	i;

	i = 0;
	while (message[i])
		i++;
	write(STDERR_FILENO, message, i);
	write(STDERR_FILENO, ", Error\n", 8);
	return (EXIT_FAILURE);
}

int	malloc_error_free(pthread_t *thread, t_philo *philo, t_bin *bin)
{
	free(philo);
	free(thread);
	free(bin->fork);
	return (error("Malloc Allocation"));
}
