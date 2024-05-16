/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:16:30 by juramos           #+#    #+#             */
/*   Updated: 2024/05/09 13:33:02 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_bzero(void *s, size_t n)
{
	if (n != 0)
	{
		while (n--)
			*(char *)s++ = 0;
	}
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n'
		|| c == '\f' || c == '\r'
		|| c == '\t' || c == '\v')
		return (1);
	return (0);
}

static const char	*remove_whitespaces(const char *str)
{
	int	pos;

	pos = 0;
	while (ft_isspace(str[pos]))
		pos++;
	return (&str[pos]);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	ret = malloc(count * size);
	if (!ret)
		return (0);
	ft_bzero(ret, count * size);
	if (!ret)
		return (0);
	return (ret);
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
		if (ft_isdigit(str[pos]))
			num = num * 10 + str[pos] - 48;
		else
			return (num * sign);
		pos++;
	}
	return (num * sign);
}
