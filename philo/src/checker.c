/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:18:05 by juramos           #+#    #+#             */
/*   Updated: 2024/05/23 18:42:09 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_if_dead(t_rules *r, t_philo *p)
{
	int	i;

	i = -1;
	while (++i < r->nb_philo && !(r->dead))
	{
		pthread_mutex_lock(&(r->meal_check));
		if (time_diff(p[i].last_meal, timestamp()) > r->time_to_die)
		{
			print_action(&p[i], "died");
			r->dead = 1;
			pthread_mutex_unlock(&(r->meal_check));
			break ;
		}
		pthread_mutex_unlock(&(r->meal_check));
		usleep(50);
	}
}

static void	check_if_all_ate(t_rules *r, t_philo *p)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(r->meal_check));
	while (r->meals_needed != -1
		&& i < r->nb_philo && p[i].n_meals >= r->meals_needed)
		i++;
	pthread_mutex_unlock(&(r->meal_check));
	if (i == r->nb_philo)
	{
		pthread_mutex_lock(&(r->meal_check));
		r->all_ate = 1;
		pthread_mutex_unlock(&(r->meal_check));
	}
	usleep(50);
}

int	check_condition(int *val, pthread_mutex_t *mut)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(mut);
	if (*val)
		ret = 1;
	pthread_mutex_unlock(mut);
	return (ret);
}

void	main_process_checker(t_rules *r, t_philo *p)
{
	while (!(r->all_ate))
	{
		check_if_dead(r, p);
		if (r->dead)
			break ;
		check_if_all_ate(r, p);
	}
}
