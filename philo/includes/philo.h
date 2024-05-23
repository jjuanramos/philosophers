/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:55:36 by juramos           #+#    #+#             */
/*   Updated: 2024/05/23 12:35:48 by juramos          ###   ########.fr       */
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
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	logger;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	all_ate_check;
}					t_rules;

/*	init			*/
int					init_all(t_rules *rules, char **argv);
/*	time			*/
long long			timestamp(void);
long long			time_diff(long long time1, long long time2);
void				philo_sleeps(int naptime);
/*	utils			*/
int					ft_atoi(const char *str);
int					print_error(char *str);

/*	logger			*/
void				print_action(t_philo *phi, char *action);

/*	checker			*/
void				main_process_checker(t_rules *r, t_philo *p);

/*	launcher	*/
int					launch_threads(t_rules *rules);

#endif
