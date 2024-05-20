/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:45:01 by juramos           #+#    #+#             */
/*   Updated: 2024/05/20 10:19:45 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_rules *rules)
{
	int	i;

	rules->philos = malloc(rules->nb_philo * sizeof(t_philo *));
	if (!rules->philos)
		return (EXIT_FAILURE);
	i = 0;
	while (i < rules->nb_philo)
	{
		rules->philos[i] = malloc(2 * sizeof(t_philo));
		rules->philos[i]->id = i + 1;
		rules->philos[i]->n_meals = 0;
		rules->philos[i]->last_meal = 0;
		rules->philos[i]->rules = rules;
		if (!i)
		{
			rules->philos[i]->rf_id = rules->nb_philo - 1;
			rules->philos[i]->lf_id = 1;
		}
		else if (i == rules->nb_philo - 1)
		{
			rules->philos[i]->rf_id = rules->nb_philo - 2;
			rules->philos[i]->lf_id = 0;
		}
		else
		{
			rules->philos[i]->rf_id = i - 1;
			rules->philos[i]->lf_id = i + 1;
		}
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
	if (rules->nb_philo < 1 || rules->time_to_die < 0
		|| rules->time_to_eat < 0 || rules->time_to_sleep < 0)
		return (print_error(rules, "Init. error: philo's args\n", 0));
	if (argv[5])
	{
		rules->meals_needed = ft_atoi(argv[5]);
		if (rules->meals_needed < 0)
			return (print_error(rules, "Init. error: philo's args\n", 0));
	}
	else
		rules->meals_needed = -1;
	if (init_philos(rules))
		return (print_error(rules, "Init. error: rules->philo's alloc\n", 1));
	return (EXIT_SUCCESS);
}
