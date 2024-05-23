/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:05:42 by juramos           #+#    #+#             */
/*   Updated: 2024/05/23 10:51:41 by juramos          ###   ########.fr       */
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
	if (phi && phi->id > 0 && phi->id <= phi->rules->nb_philo)
	{
		pthread_mutex_lock(&(phi->rules->logger));
		if (!ft_strncmp(action, "died", ft_strlen("died")))
			printf("\033[0;91m%lli %d %s\n", timestamp(), phi->id, action);
		else if (!ft_strncmp(action, "is thinking", ft_strlen("is thinking")))
			printf("\033[0;93m%lli %d %s\n", timestamp(), phi->id, action);
		else if (!ft_strncmp(action, "is eating", ft_strlen("is eating")))
			printf("\033[0;92m%lli %d %s\n", timestamp(), phi->id, action);
		else if (!ft_strncmp(action, "is sleeping", ft_strlen("is sleeping")))
			printf("\033[0;94m%lli %d %s\n", timestamp(), phi->id, action);
		else
			printf("\033[0;97m%lli %d %s\n", timestamp(), phi->id, action);
		pthread_mutex_unlock(&(phi->rules->logger));
	}
}
