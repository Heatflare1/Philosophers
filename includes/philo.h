/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisse <jisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:04:07 by jisse             #+#    #+#             */
/*   Updated: 2023/02/14 15:53:28 by jisse            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_philo
{
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_philo;
	int		each_philo_must_eat;
	bool	eat_till_full;
	
} t_philo;
	
// parce
int	argument_conversion(t_philo *philo, int argc, char *argv[]);

#endif