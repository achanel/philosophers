/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:21:33 by achanel           #+#    #+#             */
/*   Updated: 2021/11/15 16:19:45 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	mut_destroy(t_base *base)
{
	pthread_mutex_destroy(&base->lock);
	pthread_mutex_destroy(&base->print);
	base->i = -1;
	while (++base->i < base->ph_number)
		pthread_mutex_destroy(&base->fork[base->i]);
}

static void	solve(t_base *base)
{
	pthread_t	waiter;

	if (pthread_mutex_init(&base->lock, NULL) != 0 )
		ft_error("MUTEX_INIT ERROR");
	if (pthread_mutex_init(&base->print, NULL) != 0)
		ft_error("MUTEX_INIT ERROR");
	base->i = -1;
	while (++base->i < base->ph_number)
		if (pthread_mutex_init(&base->fork[base->i], NULL) != 0)
			ft_error("MUTEX_INIT ERROR");
	base->i = 0;
	while (base->i < base->ph_number)
	{
		pthread_mutex_lock(&base->lock);
		if (pthread_create(&base->philosopher[base->i],
				NULL, phil_life, (void *)base) != 0)
			ft_error("THREAD ERROR");
		pthread_detach(base->philosopher[base->i]);
		pthread_mutex_lock(&base->lock);
		base->i++;
		pthread_mutex_unlock(&base->lock);
	}
	pthread_create(&waiter, NULL, waiter_life, (void *)base);
	pthread_join(waiter, NULL);
	mut_destroy(base);
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
	base->start_time = ft_cur_time();
	base->philosopher = (pthread_t *)malloc(sizeof(pthread_t)
			* base->ph_number);
	base->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* base->ph_number);
	base->life_time = (int *)malloc(sizeof(int) * base->ph_number);
	if (!(base->fork) || !(base->philosopher) || !(base->life_time))
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
	if (base->philosopher)
		free(base->philosopher);
	if (base->fork)
		free(base->fork);
	if (base)
		free(base);
	return (0);
}
