/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:21:33 by achanel           #+#    #+#             */
/*   Updated: 2021/11/01 16:22:38 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_base(t_base *base)
{
	if (base->philosopher)
		free(base->philosopher);
	if (base->fork)
		free(base->fork);
	if (base->life_time)
		free(base->life_time);
	if (base)
		free(base);
}

static void	base_init(t_base *base, int ac, char **av)
{
	base->philosopher = NULL;
	base->fork = NULL;
	base->life_time = NULL;
	base->ph_number = ft_atoi(av[1]);
	base->time_to_die = ft_atoi(av[2]);
	base->time_to_eat = ft_atoi(av[3]);
	base->time_to_sleep = ft_atoi(av[4]);
	base->meals = -1;
	if (ac == 6)
		base->meals = ft_atoi(av[5]);
	base->start_time = ft_start_time();
	base->philosopher = (pthread_t *)malloc(sizeof(pthread_t)
			* base->ph_number);
	base->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* base->ph_number);
	base->life_time = (int *)malloc(sizeof(int) * base->ph_number);
	if (!(base->philosopher) && !(base->fork) && !(base->life_time))
		ft_error("MALLOC ERROR");
}

int	main(int ac, char **av)
{
	t_base	*base;

	if (ac < 5 || ac > 6 || check_arg(ac, av))
		ft_error("ARG ERROR");
	base = (t_base *)malloc(sizeof(t_base));
	if (!base)
		ft_error("MALLOC ERROR");
	base_init(base, ac, av);
	solve(base);
	free_base(base);
	return (0);
}
