/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:49:42 by jmeruma           #+#    #+#             */
/*   Updated: 2023/02/24 12:24:00 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#define	SLEEP_BUFFER 100;

unsigned long	gimme_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * MICRO_SECONDS) + (time.tv_usec / MICRO_SECONDS));
}

void	sleep_loop(long	big_time, unsigned long end)
{
	if (big_time > 0)
		usleep(big_time);
	while(gimme_time() < end)
		usleep(10);
}

void	sleep_tight_philo(unsigned int time)
{
	long			big_time;
	unsigned long	end;
	unsigned long	start;

	start = gimme_time();
	end = start + time;
	big_time = time;
	big_time -= SLEEP_BUFFER;
	sleep_loop(big_time, end);
}
