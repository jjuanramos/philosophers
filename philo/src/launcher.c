/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:33:48 by juramos           #+#    #+#             */
/*   Updated: 2024/05/23 12:17:51 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eats(t_philo *phi, t_rules *rules)
{
	if (phi->id % 2)
	{
		pthread_mutex_lock(&(rules->forks[phi->rf_id]));
		print_action(phi, "has taken a fork");
		pthread_mutex_lock(&(rules->forks[phi->lf_id]));
		print_action(phi, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&(rules->forks[phi->lf_id]));
		print_action(phi, "has taken a fork");
		pthread_mutex_lock(&(rules->forks[phi->rf_id]));
		print_action(phi, "has taken a fork");
	}
	pthread_mutex_lock(&(rules->meal_check));
	print_action(phi, "is eating");
	phi->last_meal = timestamp();
	(phi->n_meals)++;
	pthread_mutex_unlock(&(rules->meal_check));
	philo_sleeps(rules->time_to_eat);
	pthread_mutex_unlock(&(rules->forks[phi->lf_id]));
	pthread_mutex_unlock(&(rules->forks[phi->rf_id]));
}

void	*p_thread(void *philo)
{
	t_philo	*phi;
	t_rules	*rules;

	phi = (t_philo *)philo;
	rules = phi->rules;
	if (phi->id % 2)
		usleep(10000);
	while (!rules->dead)
	{
		philo_eats(phi, rules);
		pthread_mutex_lock(&(rules->all_ate_check));
		if (rules->all_ate)
		{
			pthread_mutex_unlock(&(rules->all_ate_check));
			break ;
		}
		else
			pthread_mutex_unlock(&(rules->all_ate_check));
		print_action(phi, "is sleeping");
		philo_sleeps(rules->time_to_sleep);
		print_action(phi, "is thinking");
	}
	return (NULL);
}

int	join_and_exit(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->nb_philo)
	{
		if (pthread_join(rules->philos[i]->thread_id, NULL))
			return (print_error(NULL, "Error: Failure joining threads.\n", 0));
	}
	i = -1;
	while (++i < rules->nb_philo)
	{
		if (pthread_mutex_destroy(&(rules->forks[i])))
			return (print_error(NULL, "Error: Failure destroying mutex.\n", 0));
	}
	if (pthread_mutex_destroy(&(rules->logger)))
		return (print_error(NULL, "Error: Failure destroying mutex.\n", 0));
	if (pthread_mutex_destroy(&(rules->meal_check)))
		return (print_error(NULL, "Error: Failure destroying mutex.\n", 0));
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
			return (print_error(NULL, "Error: Failure init. threads.\n", 0));
		pthread_mutex_lock(&(rules->meal_check));
		rules->philos[i]->last_meal = timestamp();
		pthread_mutex_unlock(&(rules->meal_check));
	}
	main_process_checker(rules, rules->philos);
	join_and_exit(rules);
	rules_cleaner(rules);
	return (EXIT_SUCCESS);
}
