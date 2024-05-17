/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:55:36 by juramos           #+#    #+#             */
/*   Updated: 2024/05/17 10:17:42 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int			nb;
	long long	last_meal;
	int			n_meals;
}				t_philo;

typedef struct s_rules
{
	int		nb_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meals_needed;
	t_philo	**philos;
}				t_rules;

/*	error	*/
int			print_error(char *str);
/*	init	*/
int			init_all(t_rules *rules, char **argv);
/*	time	*/
long long	current_timestamp(void);
/*	utils	*/
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);

#endif
