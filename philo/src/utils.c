/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:16:30 by juramos           #+#    #+#             */
/*   Updated: 2024/05/22 13:35:56 by juramos          ###   ########.fr       */
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
			{
				if (rules->philos[i])
					free(rules->philos[i]);
				i++;
			}
			free(rules->philos);
			free(rules->forks);
		}
	}
}

int	print_error(t_rules *rules, char *str, int to_free)
{
	if (to_free)
		rules_cleaner(rules);
	printf("\033[0;97mphilo: %s\n", str);
	return (EXIT_FAILURE);
}

static const char	*remove_whitespaces(const char *str)
{
	int	pos;

	pos = 0;
	while (str[pos] == ' ' || str[pos] == '\n'
		|| str[pos] == '\f' || str[pos] == '\r'
		|| str[pos] == '\t' || str[pos] == '\v')
		pos++;
	return (&str[pos]);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	num;
	int	pos;

	str = remove_whitespaces(str);
	pos = 0;
	num = 0;
	sign = 1;
	if (str[0] == '+')
		pos++;
	else if (str[0] == '-')
	{
		sign *= -1;
		pos++;
	}
	while (str[pos] != '\0')
	{
		if (str[pos] >= '0' && str[pos] <= '9')
			num = num * 10 + str[pos] - 48;
		else
			return (num * sign);
		pos++;
	}
	return (num * sign);
}
