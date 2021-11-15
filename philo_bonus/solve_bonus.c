/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:06:03 by achanel           #+#    #+#             */
/*   Updated: 2021/11/15 17:45:58 by achanel          ###   ########.fr       */
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
	base->life_time[number - 1] = ft_time(base);
	ft_print(base, number, "is eating");
	ft_delay(base->time_to_eat);
	sem_post(base->fork);
	sem_post(base->fork);
}

void	*waiter_life(void *void_base)
{
	t_base	*base;
	long	time;

	base = (t_base *)void_base;
	time = ft_time(base) - 2;
	while (1)
	{
		if ((base->life_time[base->i] + base->time_to_die) < time)
		{
			sem_wait(base->print);
			printf("%ld %d %s", ft_time(base), base->i + 1, "died\n");
			exit (1);
		}
		if (base->i <= 0 && base->meals > 0)
			exit (0);
	}
	ft_delay(4);
	return (NULL);
}

static void	phil_life_helper(t_base *base, int eating_times, int number)
{
	while (eating_times)
	{
		eating(base, number);
		ft_print(base, number, "is sleeping");
		ft_delay(base->time_to_sleep);
		ft_print(base, number, "is thinking");
		if (eating_times > 0)
			eating_times--;
	}
	if (eating_times == 0)
	{
		base->i--;
		base->life_time[number - 1] = -1;
	}
}

void	phil_life(t_base *base)
{
	pthread_t	waiter;
	int			eating_times;
	int			number;

	pthread_create(&waiter, NULL, waiter_life, (void *)base);
	eating_times = -1;
	if (base->meals > 0)
		eating_times = base->meals;
	number = base->i + 1;
	base->life_time[number - 1] = ft_time(base);
	if (!number % 2)
		ft_delay(base->time_to_eat / 2);
	phil_life_helper(base, eating_times, number);
	pthread_join(waiter, NULL);
}
