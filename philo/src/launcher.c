/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:33:48 by juramos           #+#    #+#             */
/*   Updated: 2024/05/28 18:28:59 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eats(t_philo *phi, t_rules *rules)
{
	if (phi->id % 2)
	{
		pthread_mutex_lock(&(rules->forks[phi->lf_id]));
		print_action(phi, "has taken a fork");
		pthread_mutex_lock(&(rules->forks[phi->rf_id]));
		print_action(phi, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&(rules->forks[phi->rf_id]));
		print_action(phi, "has taken a fork");
		pthread_mutex_lock(&(rules->forks[phi->lf_id]));
		print_action(phi, "has taken a fork");
	}
	print_action(phi, "is eating");
	pthread_mutex_lock(&(rules->meal_check));
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
	while (1)
	{
		if (check_condition(&(rules->dead), &(rules->meal_check)))
			break ;
		philo_eats(phi, rules);
		if (check_condition(&(rules->all_ate), &(rules->meal_check))
			|| check_condition(&(rules->dead), &(rules->meal_check)))
			break ;
		print_action(phi, "is sleeping");
		philo_sleeps(rules->time_to_sleep);
		print_action(phi, "is thinking");
		usleep(50);
	}
	return (NULL);
}

int	join_and_exit(t_rules *rules)
{
	int	i;

	i = -1;
	if (rules->nb_philo == 1)
	{
		if (pthread_detach(rules->philos[0].thread_id))
			return (print_error("Error: Failure detaching thread."));
	}
	else
	{
		while (++i < rules->nb_philo)
		{
			if (pthread_join(rules->philos[i].thread_id, NULL))
				return (print_error("Error: Failure joining threads."));
		}
		i = -1;
		while (++i < rules->nb_philo)
		{
			if (pthread_mutex_destroy(&(rules->forks[i])))
				return (print_error("Error: Failure destroying mutex."));
		}
		if (rules->philos)
			free(rules->philos);
	}
	return (EXIT_SUCCESS);
}

int	launch_threads(t_rules *rules)
{
	int	i;

	i = -1;
	rules->starting_time = timestamp();
	while (++i < rules->nb_philo)
	{
		if (pthread_create(&(rules->philos[i].thread_id),
				NULL, p_thread, &(rules->philos[i])))
			return (print_error("Error: Failure init. threads."));
		pthread_mutex_lock(&(rules->meal_check));
		rules->philos[i].last_meal = timestamp();
		pthread_mutex_unlock(&(rules->meal_check));
	}
	main_process_checker(rules, rules->philos);
	join_and_exit(rules);
	if (pthread_mutex_destroy(&(rules->logger)))
		return (print_error("Error: Failure destroying mutex."));
	if (pthread_mutex_destroy(&(rules->meal_check)))
		return (print_error("Error: Failure destroying mutex."));
	free(rules->forks);
	return (EXIT_SUCCESS);
}
