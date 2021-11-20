/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:06:03 by achanel           #+#    #+#             */
/*   Updated: 2021/11/20 14:28:01 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	one_filo(t_base *base)
{
	ft_delay(base->time_to_die);
	ft_print(base, 1, "died");
	exit (0);
}

static void	eating(t_base *base, int number)
{
	sem_wait(base->fork);
	ft_print(base, number, "has taken a fork");
	if (base->ph_number == 1)
		one_filo(base);
	sem_wait(base->fork);
	ft_print(base, number, "has taken a fork");
	base->life_time = ft_time(base);
	ft_print(base, number, "is eating");
	ft_delay(base->time_to_eat);
	sem_post(base->fork);
	sem_post(base->fork);
}

void	*waiter_life(void *void_base)
{
	t_base	*base;

	base = (t_base *)void_base;
	while (1)
	{
		ft_delay(10);
		if ((base->life_time + base->time_to_die) <= ft_time(base) - 2)
		{
			sem_wait(base->print);
			printf("%ld %d %s", ft_time(base), base->i + 1, "died\n");
			exit (1);
		}
	}
	return (NULL);
}

void	phil_life(t_base *base)
{
	pthread_t	waiter;

	if (pthread_create(&waiter, NULL, waiter_life, (void *)base) != 0)
		ft_error("THREAD ERROR");
	pthread_detach(waiter);
	if (base->i % 2)
		ft_delay(base->time_to_eat / 2);
	while (1)
	{
		eating(base, base->i + 1);
		base->eating_times++;
		ft_print(base, base->i + 1, "is sleeping");
		ft_delay(base->time_to_sleep);
		if (base->eating_times == base->meals)
			exit (0);
		ft_print(base, base->i + 1, "is thinking");
	}
}
