/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:33:48 by juramos           #+#    #+#             */
/*   Updated: 2024/05/21 12:00:48 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eats(t_philo *phi, t_rules *rules)
{
	pthread_mutex_lock(&(rules->forks[phi->lf_id]));
	print_action(phi, "has taken a fork");
	pthread_mutex_lock(&(rules->forks[phi->rf_id]));
	print_action(phi, "has taken a fork");
	pthread_mutex_lock(&(rules->meal_check));
	print_action(phi, "is eating");
	phi->last_meal = timestamp();
	pthread_mutex_unlock(&(rules->meal_check));
	philo_sleeps(rules->time_to_eat);
	(phi->n_meals)++;
	pthread_mutex_unlock(&(rules->forks[phi->lf_id]));
	pthread_mutex_unlock(&(rules->forks[phi->rf_id]));
}

void	*p_thread(void *philo)
{
	t_philo	*phi;
	t_rules	*rules;

	phi = (t_philo *)philo;
	rules = phi->rules;
	while (!rules->dead)
	{
		philo_eats(phi, rules);
		if (rules->all_ate)
			break ;
		print_action(phi, "is sleeping");
		philo_sleeps(rules->time_to_sleep);
		print_action(phi, "is thinking");
	}
	return (NULL);
}

void	check_if_dead(t_rules *r, t_philo **p)
{
	int		i;

	while (!(r->all_ate))
	{
		i = -1;
		while (++i < r->nb_philo && !(r->dead))
		{
			pthread_mutex_lock(&(r->meal_check));
			if (time_diff(p[i]->last_meal, timestamp()) > r->time_to_die)
			{
				print_action(p[i], "died");
				r->dead = 1;
			}
			pthread_mutex_unlock(&(r->meal_check));
			usleep(100);
		}
		if (r->dead)
			break ;
		i = 0;
		while (r->meals_needed != -1
			&& i < r->nb_philo && p[i]->n_meals >= r->meals_needed)
			i++;
		if (i == r->nb_philo)
			r->all_ate = 1;
	}
}

int	join_and_exit(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i)
		if (pthread_join(rules->philos[i]->thread_id, NULL))
			return (EXIT_FAILURE);
	i = -1;
	while (++i)
		if (pthread_mutex_destroy(&(rules->forks[i])))
			return (EXIT_FAILURE);
	if (pthread_mutex_destroy(&(rules->logger)))
		return (EXIT_FAILURE);
	if (pthread_mutex_destroy(&(rules->meal_check)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	launch_threads(t_rules *rules)
{
	int	i;

	i = -1;
	rules->starting_time = timestamp();
	while (++i < rules->nb_philo)
	{
		if (pthread_create(&(rules->philos[i]->thread_id),
				NULL, p_thread, rules->philos[i]))
			return (EXIT_FAILURE);
	}
	check_if_dead(rules, rules->philos);
	join_and_exit(rules);
	// rules_cleaner(rules);
	return (EXIT_SUCCESS);
}
