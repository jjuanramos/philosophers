/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:33:48 by juramos           #+#    #+#             */
/*   Updated: 2024/05/21 11:32:07 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Should philo_sleeps go before or after last_meal calculation?
*/
void	philo_eats(t_philo *phi, t_rules *rules)
{
	pthread_mutex_lock(&(rules->forks[phi->lf_id]));
	print_action(phi, "has taken a fork");
	pthread_mutex_lock(&(rules->forks[phi->rf_id]));
	print_action(phi, "has taken a fork");
	print_action(phi, "is eating");
	pthread_mutex_lock(&(rules->meal_check));
	phi->last_meal = current_timestamp();
	(phi->n_meals)++;
	philo_sleeps(rules->time_to_eat);
	pthread_mutex_unlock(&(rules->meal_check));
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

/*
	This loop is wrong as we are only checking whether the first
	philo is dead.
*/
void	check_if_dead(t_rules *rules)
{
	t_philo	*phi;
	int		i;

	i = 0;
	while (!(rules->all_ate))
	{
		phi = rules->philos[i];
		if (time_diff(phi->last_meal, current_timestamp()) > rules->time_to_die)
		{
			print_action(phi, "died");
			rules->dead = 1;
		}
		if (rules->dead)
			break ;
		if (rules->meals_needed != 1)
		{
			i = 0;
			while (i < rules->nb_philo
				&& rules->philos[i]->n_meals >= rules->meals_needed)
				i++;
			if (i == rules->nb_philo)
				rules->all_ate = 1;
		}
		else
			i++;
	}
}

int	join_and_exit(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i)
	{
		if (pthread_join(rules->philos[i]->thread_id, NULL))
			return (EXIT_FAILURE);
		if (pthread_mutex_destroy(&(rules->forks[i])))
			return (EXIT_FAILURE);
	}
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
	rules->starting_time = current_timestamp();
	while (++i < rules->nb_philo)
	{
		if (pthread_create(&(rules->philos[i]->thread_id),
				NULL, p_thread, rules->philos[i]))
			return (EXIT_FAILURE);
	}
	check_if_dead(rules);
	join_and_exit(rules);
	rules_cleaner(rules);
	return (EXIT_SUCCESS);
}
