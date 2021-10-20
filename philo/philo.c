/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:21:33 by achanel           #+#    #+#             */
/*   Updated: 2021/10/20 16:55:42 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	base_init(t_philo *base, int ac, char **av)
{
	base->philo = NULL;
	base->fork = NULL;
	base->life_time = NULL;
	base->ph_count = ft_atoi(av[1]);
	base->time_to_die = ft_atoi(av[2]);
	base->time_to_eat = ft_atoi(av[3]);
	base->time_to_sleep = ft_atoi(av[4]);
	base->eating_count = -1;
	if (ac == 6)
		base->eating_count = ft_atoi(av[5]);
	base->start_time = ft_start_time();
	base->philo = (pthread_t *)malloc(sizeof(pthread_t) * base->ph_count);
	base->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * base->ph_count);
	base->life_time = (int *)malloc(sizeof(int) * base->ph_count);
}

int	main(int ac, char **av)
{
	t_philo	*base;

	base = (t_philo *)malloc(sizeof(t_philo));
	if (!base)
		return (1);
	if (ac < 5 || ac > 6 || check_arg(ac, av))
	{
		printf("INVALID ARGUMENTS\n");
		return (1);
	}
	base_init(base, ac, av);
	if (base->philo && base->fork && base->life_time)
		solve(base);
	free_base(base);
	return (0);
}
