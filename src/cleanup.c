/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:32:46 by jmeruma           #+#    #+#             */
/*   Updated: 2023/03/14 15:20:50 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_exit(char *message)
{
	printf("%s, Error\n", message);
	return (EXIT_FAILURE);
}

void	philo_cleaning(t_philo *philo, pthread_t *thread)
{
	free(philo->bin->fork);
	free(thread);
	free(philo);
}
