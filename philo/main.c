/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:54:21 by juramos           #+#    #+#             */
/*   Updated: 2024/05/09 13:33:31 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules	*rules;

	if (argc != 5 && argc != 6)
		return (print_error("Wrong number of arguments\n"));
	rules = ft_calloc(1, sizeof(t_rules));
	if (init_all(rules, argv))
		return (print_error("Error during initiation. Exiting\n"));
	free(rules);
}
