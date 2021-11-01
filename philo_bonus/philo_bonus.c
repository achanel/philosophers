/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:21:33 by achanel           #+#    #+#             */
/*   Updated: 2021/11/01 17:16:00 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	base_init(t_base *base, int ac, char **av)
{
	base->ph_number = ft_atoi(av[1]);
	base->time_to_die = ft_atoi(av[2]);
	base->time_to_eat = ft_atoi(av[3]);
	base->time_to_sleep = ft_atoi(av[4]);
	base->meals = -1;
	if (ac == 6)
		base->meals = ft_atoi(av[5]);
	base->start_time = ft_start_time();
}

int	main(int ac, char **av)
{
	t_base	*base;

	if (ac < 5 || ac > 6 || check_arg(ac, av))
		ft_error("ARG ERROR\n");
	base = (t_base *)malloc(sizeof(t_base));
	if (!base)
		ft_error("MALLOC ERROR");
	base_init(base, ac, av);
	solve(base);
	free(base);
	return (0);
}
