/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:16:30 by juramos           #+#    #+#             */
/*   Updated: 2024/05/23 12:31:31 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *str)
{
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
