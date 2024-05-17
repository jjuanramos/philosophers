/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:41:32 by juramos           #+#    #+#             */
/*   Updated: 2024/05/17 11:45:55 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	rules_cleaner(t_rules *rules)
{
	int	i;

	if (rules)
	{
		if (rules->philos)
		{
			i = 0;
			while (i < rules->nb_philo)
				free(rules->philos[i++]);
		}
		free(rules->philos);
		free(rules);
	}
}

int	print_error(t_rules *rules, char *str)
{
	int	i;

	rules_cleaner(rules);
	i = 0;
	write(2, "philo: ", 7);
	while (str[i])
		write(2, &str[i++], 1);
	return (EXIT_FAILURE);
}
