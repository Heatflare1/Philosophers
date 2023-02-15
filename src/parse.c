/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisse <jisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:34:42 by jisse             #+#    #+#             */
/*   Updated: 2023/02/14 16:01:27 by jisse            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int     ft_atoi_overflow(const char *str, int *numb)
{
	int     i;
	int     sign;

	i = 0;
	*numb = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
				i++;
	if (str[i] == '-')
			sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		*numb += str[i] - '0';
		if (*numb < 0 && (*numb != INT_MIN || sign == 1))
			return (1);
		if (str[i + 1] >= '0' && str[i + 1] <= '9')
			*numb *= 10;
		i++;
	}
	*numb *= sign;
	return (0);
}

int argument_conversion(t_philo *philo, int argc, char *argv[])
{
	int i;
	int numb[5];

	i = 0;
	philo->eat_till_full = false;
	philo->each_philo_must_eat = 0;
	if (argc == 6)
		philo->eat_till_full = true;
	while (i < argc - 1)
	{
		if (ft_atoi_overflow(argv[i + 1], &numb[i]))
			return (1);
		i++;
	}
	philo->number_of_philo = numb[0];
	philo->time_to_die = numb[1];
	philo->time_to_eat = numb[2];
	philo->time_to_sleep = numb[3];
	if (philo->eat_till_full)
		philo->each_philo_must_eat = numb[4];
	return (0);
}