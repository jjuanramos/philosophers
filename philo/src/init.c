/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:45:01 by juramos           #+#    #+#             */
/*   Updated: 2024/05/09 14:04:20 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_rules *rules)
{
	int	i;

	if (!rules->philos)
		return (1);
	i = 0;
	while (i < rules->nb_philo)
	{
		rules->philos[i]->nb = i + 1;
		rules->philos[i]->n_meals = 0;
		rules->philos[i]->last_meal = current_timestamp();
		printf("current timestamp is %d\n", rules->philos[i]->last_meal);
		i++;
	}
	return (0);
}

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
	rules->philos = ft_calloc(rules->nb_philo, sizeof(t_philo *));
	if (!rules->nb_philo || !rules->time_to_die
		|| !rules->time_to_eat || !rules->time_to_sleep
		|| init_philos(rules))
	{
		free(rules);
		return (1);
	}
	return (0);
}
