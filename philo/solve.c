/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:06:03 by achanel           #+#    #+#             */
/*   Updated: 2021/11/01 16:33:36 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_base *base, int number)
{
	int	l_fork;
	int	r_fork;

	l_fork = number - 1;
	if (number == 1)
		r_fork = base->ph_number - 1;
	else
		r_fork = number - 2;
	pthread_mutex_lock(&base->fork[r_fork]);
	ft_prsint(base, number, "has taken a fork");
	pthread_mutex_lock(&base->fork[l_fork]);
	ft_print(base, number, "has taken a fork");
	base->life_time[number - 1] = ft_time(base);
	ft_print(base, number, "is eating");
	ft_delay(base->time_to_eat);
	pthread_mutex_unlock(&base->fork[l_fork]);
	pthread_mutex_unlock(&base->fork[r_fork]);
}

void	*waiter_life(void *base)
{
	int	flag;

	flag = 1;
	while (flag)
	{
		flag = ft_death((t_base *)base);
		if (((t_base *)base)->i <= 0 && ((t_base *)base)->meals > 0 && flag)
			flag = 0;
	}
	ft_delay(4);
	return (NULL);
}

void	*phil_life(void *base)
{
	int	eating_times;
	int	number;

	eating_times = -1;
	if (((t_base *)base)->meals > 0)
		eating_times = ((t_base *)base)->meals;
	number = ((t_base *)base)->i + 1;
	((t_base *)base)->life_time[number - 1] = ft_time(base);
	if (!number % 2)
		ft_delay(((t_base *)base)->time_to_eat / 2);
	while (eating_times)
	{
		eating(base, number);
		ft_print(base, number, "is sleeping");
		ft_delay(((t_base *)base)->time_to_sleep);
		ft_print(base, number, "is thinking");
		if (eating_times > 0)
			eating_times--;
	}
	phil_life_helper(((t_base *)base), eating_times, number);
	return (NULL);
}

static void	waiter_init(t_base *base)
{
	pthread_t	waiter;

	waiter = (pthread_t)malloc(sizeof(pthread_t));
	if (!waiter)
		ft_error("MALLOC ERROR");
	pthread_create(&waiter, NULL, waiter_life, (void *)base);
	pthread_join(waiter, NULL);
	pthread_mutex_destroy(&base->print);
	base->i = 0;
	while (base->i < base->ph_number)
	{
		pthread_mutex_destroy(&base->fork[base->i]);
		base->i++;
	}
}

void	solve(t_base *base)
{
	base->i = 0;
	if (pthread_mutex_init(&base->print, NULL) != 0);
		ft_error("MUTEX_INIT ERROR");
	while (base->i < base->ph_number)
	{
		if (pthread_mutex_init(&base->fork[base->i], NULL) != 0);
			ft_error("MUTEX_INIT ERROR");
		base->i++;
	}
	base->i = 0;
	while (base->i < base->ph_number)
	{
		if (pthread_create(&base->philosopher[base->i], NULL,
			phil_life, (void *)base) != 0);
			ft_error("THREAD ERROR");
		pthread_detach(base->philosopher[base->i]);
		base->i++;
	}
	waiter_init(base);
}
