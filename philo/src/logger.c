/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:05:42 by juramos           #+#    #+#             */
/*   Updated: 2024/05/28 15:21:56 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(const char *str)
{
	size_t	pos;

	pos = 0;
	while (str[pos] != '\0')
		pos++;
	return (pos);
}

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	pos;

	pos = 0;
	if (n == 0)
		return (0);
	while (pos < n && s1[pos] != '\0' && s2[pos] != '\0')
	{
		if (s1[pos] != s2[pos])
			return ((unsigned char)s1[pos] - (unsigned char)s2[pos]);
		pos++;
	}
	if (n == pos)
		pos--;
	return ((unsigned char)s1[pos] - (unsigned char)s2[pos]);
}

void	print_action(t_philo *phi, char *action)
{
	long long	t;
	long long	time_dif;

	if (phi && phi->id > 0 && phi->id <= phi->rules->nb_philo)
	{
		pthread_mutex_lock(&(phi->rules->logger));
		t = timestamp();
		time_dif = time_diff(phi->rules->last_time_eaten, t);
		if (!ft_strncmp(action, "died", ft_strlen("died")))
			printf("\033[1;31m%lli %d %s\n", time_dif, phi->id, action);
		else if (!ft_strncmp(action, "is thinking", ft_strlen("is thinking")))
			printf("\033[0;95m%lli %d %s\n", time_dif, phi->id, action);
		else if (!ft_strncmp(action, "is eating", ft_strlen("is eating")))
			printf("\033[0;92m%lli %d %s\n", time_dif, phi->id, action);
		else if (!ft_strncmp(action, "is sleeping", ft_strlen("is sleeping")))
			printf("\033[0;94m%lli %d %s\n", time_dif, phi->id, action);
		else
			printf("\033[0;97m%lli %d %s\n", time_dif, phi->id, action);
		phi->rules->last_time_eaten = t;
		pthread_mutex_unlock(&(phi->rules->logger));
	}
}
