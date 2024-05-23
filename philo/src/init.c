/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:45:01 by juramos           #+#    #+#             */
/*   Updated: 2024/05/23 18:44:06 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philos(t_rules *rules)
{
	int	i;

	i = 0;
	rules->philos = malloc(sizeof(t_philo) * rules->nb_philo);
	if (!rules->philos)
		return (EXIT_FAILURE);
	while (i < rules->nb_philo)
	{
		rules->philos[i].id = i + 1;
		rules->philos[i].n_meals = 0;
		rules->philos[i].last_meal = 0;
		rules->philos[i].rules = rules;
		if (i == 0)
			rules->philos[i].rf_id = rules->nb_philo;
		else
			rules->philos[i].rf_id = i;
		if (i + 1 == rules->nb_philo)
			rules->philos[i].lf_id = rules->nb_philo;
		else
			rules->philos[i].lf_id = (i + 1) % rules->nb_philo;
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	init_mutex(t_rules *rules)
{
	int	i;

	i = -1;
	rules->forks = malloc(sizeof(pthread_mutex_t) * (rules->nb_philo));
	if (!rules->forks)
		return (EXIT_FAILURE);
	while (++i < rules->nb_philo)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
			return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&(rules->logger), NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&(rules->meal_check), NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_all(t_rules *rules, char **argv)
{
	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->dead = 0;
	rules->all_ate = 0;
	if (rules->nb_philo < 1 || rules->time_to_die < 0
		|| rules->time_to_eat < 0 || rules->time_to_sleep < 0)
		return (print_error("Init. error: philo's args"));
	if (argv[5])
	{
		rules->meals_needed = ft_atoi(argv[5]);
		if (rules->meals_needed <= 0)
			return (print_error("Init. error: philo's args"));
	}
	else
		rules->meals_needed = -1;
	if (init_philos(rules))
		return (print_error("Init. error: rules->philo's alloc"));
	if (init_mutex(rules))
	{
		free(rules->philos);
		return (print_error("Init. error: mutex"));
	}
	return (EXIT_SUCCESS);
}
