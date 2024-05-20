/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:55:36 by juramos           #+#    #+#             */
/*   Updated: 2024/05/20 19:58:38 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

struct	s_rules;

typedef struct s_philo
{
	int				id;
	int				lf_id;
	int				rf_id;
	long long		last_meal;
	int				n_meals;
	struct s_rules	*rules;
	pthread_t		thread_id;
}					t_philo;

typedef struct s_rules
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_needed;
	int				dead;
	int				all_ate;
	long long		starting_time;
	t_philo			**philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	logger;
	pthread_mutex_t	meal_check;
}					t_rules;

/*	init			*/
int					init_all(t_rules *rules, char **argv);
/*	time			*/
long long			current_timestamp(void);
/*	utils			*/
int					ft_atoi(const char *str);
void				rules_cleaner(t_rules *rules);
int					print_error(t_rules *rules, char *str, int to_free);

/*	launch_threads	*/
int					launch_threads(t_rules *rules);

#endif
