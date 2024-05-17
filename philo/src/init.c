/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:45:01 by juramos           #+#    #+#             */
/*   Updated: 2024/05/17 14:32:44 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_rules *rules)
{
	int	i;

	rules->philos = ft_calloc(rules->nb_philo + 1, sizeof(t_philo *));
	if (!rules->philos)
		return (EXIT_FAILURE);
	i = 0;
	while (i < rules->nb_philo)
	{
		rules->philos[i] = ft_calloc(2, sizeof(t_philo));
		if (!rules->philos[i])
			return (EXIT_FAILURE);
		rules->philos[i]->nb = i + 1;
		rules->philos[i]->n_meals = 0;
		rules->philos[i]->last_meal = current_timestamp();
		i++;
	}
	return (EXIT_SUCCESS);
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
	if (rules->nb_philo < 1 || rules->time_to_die < 0
		|| rules->time_to_eat < 0 || rules->time_to_sleep < 0)
		return (print_error(rules, "Init. error: philo's args\n"));
	if (init_philos(rules))
		return (print_error(rules, "Init. error: rules->philo's calloc\n"));
	return (EXIT_SUCCESS);
}
