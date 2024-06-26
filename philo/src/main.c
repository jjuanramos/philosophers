/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:54:21 by juramos           #+#    #+#             */
/*   Updated: 2024/05/23 15:41:53 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc != 5 && argc != 6)
		return (print_error("Wrong number of arguments"));
	if (init_all(&rules, argv))
		return (EXIT_FAILURE);
	if (launch_threads(&rules))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
