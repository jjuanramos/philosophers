/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:00:13 by juramos           #+#    #+#             */
/*   Updated: 2024/05/21 11:17:00 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_timestamp(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

long long	time_diff(long long time1, long long time2)
{
	return (time2 - time1);
}

void	philo_sleeps(int naptime)
{
	long long	starting_time;

	starting_time = current_timestamp();
	while (time_diff(starting_time, current_timestamp()) < naptime)
		usleep(50);
}
