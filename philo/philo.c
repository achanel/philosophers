/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:21:33 by achanel           #+#    #+#             */
/*   Updated: 2021/10/23 18:37:33 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
}

int	main(int ac, char **av)
{
	t_base	*base;

	if (ac < 5 || ac > 6 || check_arg(ac, av))
	{
		write(2, "ERROR\n", 6);
		return (1);
	}
	base = (t_base *)malloc(sizeof(t_base));
	if (!base)
		return (1);
	base_init(base, ac, av);
	if (base->philosopher && base->fork && base->life_time)
		solve(base);
	free_base(base);
	return (0);
}
