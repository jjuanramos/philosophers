/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:00:13 by juramos           #+#    #+#             */
/*   Updated: 2024/05/09 14:03:12 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	current_timestamp(void)
{
	struct timeval	current_time;
	long			ms;

	gettimeofday(&current_time, NULL);
	ms = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (ms);
}
