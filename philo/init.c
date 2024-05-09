/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:45:01 by juramos           #+#    #+#             */
/*   Updated: 2024/05/09 13:34:27 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_all(t_rules *rules, char **argv)
{
	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		rules->meals_needed = ft_atoi(argv[5]);
	else
		rules->meals_needed = -1;
	if (!rules->nb_philo || !rules->time_to_die
		|| !rules->time_to_eat || !rules->time_to_sleep)
	{
		free(rules);
		return (1);
	}
	return (0);
}
