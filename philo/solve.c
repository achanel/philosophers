/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:06:03 by achanel           #+#    #+#             */
/*   Updated: 2021/11/20 14:06:39 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	phil_life_helper(t_base *base, int eating_times, int number)
{
	if (eating_times == 0)
	{
		base->i--;
		base->life_time[number - 1] = -1;
	}
}

static int	ft_stick(t_base *base)
{
	long	time;
	int		i;

	i = -1;
	time = ft_time(base) - 2;
	while (++i < base->ph_number)
	{
		if (base->life_time[i] != -1)
		{
			if ((base->life_time[i] + base->time_to_die) < time)
			{
				pthread_mutex_lock(&base->print);
				printf("%ld %d %s", ft_time(base), i + 1, "died\n");
				return (0);
			}
		}
	}
	return (1);
}

static void	eating(t_base *base, int number)
{
	int	l_fork;
	int	r_fork;

	l_fork = number - 1;
	if (number == 1)
		r_fork = base->ph_number - 1;
	else
		r_fork = number - 2;
	pthread_mutex_lock(&base->fork[r_fork]);
	ft_print(base, number, "has taken a fork");
	pthread_mutex_lock(&base->fork[l_fork]);
	ft_print(base, number, "has taken a fork");
	base->life_time[number - 1] = ft_time(base);
	ft_print(base, number, "is eating");
	ft_delay(base->time_to_eat);
	pthread_mutex_unlock(&base->fork[l_fork]);
	pthread_mutex_unlock(&base->fork[r_fork]);
}

void	*waiter_life(void *void_base)
{
	t_base	*base;
	int		not_dead;

	base = (t_base *)void_base;
	not_dead = 1;
	while (not_dead)
	{
		not_dead = ft_stick(base);
		if (base->i <= 0 && base->meals > 0 && not_dead)
			not_dead = 0;
	}
	ft_delay(4);
	return (NULL);
}

void	*phil_life(void *void_base)
{
	int		eating_times;
	int		number;
	t_base	*base;

	base = (t_base *)void_base;
	eating_times = -1;
	if (base->meals > 0)
		eating_times = base->meals;
	number = base->i + 1;
	pthread_mutex_unlock(&base->lock);
	base->life_time[number - 1] = ft_time(base);
	if (!number % 2)
		ft_delay(base->time_to_eat / 2);
	while (eating_times)
	{
		eating(base, number);
		ft_print(base, number, "is sleeping");
		ft_delay(base->time_to_sleep);
		ft_print(base, number, "is thinking");
		if (eating_times > 0)
			eating_times--;
	}
	phil_life_helper(base, eating_times, number);
	return (NULL);
}
