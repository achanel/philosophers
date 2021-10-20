/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_utilc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:37:09 by achanel           #+#    #+#             */
/*   Updated: 2021/10/20 18:47:07 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_death(t_philo *base)
{
	long	time;
	int		i;

	time = ft_time(base) - 2;
	while (i < base->ph_count)
	{
		if (base->life_time[i] != -1)
		{
			if (base->life_time[i] + base->time_to_die < time)
			{
				pthread_mutex_lock(&base->print);
				printf("%ld %d %s", get_time(base), i + 1, "died\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

long	ft_start_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	ft_time(t_philo *base)
{
	struct timeval	current_tv;

	gettimeofday(&current_tv, NULL);
	return ((current_tv.tv_sec * 1000 + current_tv.tv_usec / 1000) - base->start_time);
}

void	ft_print(t_philo *base, char *s)
{
	pthread_mutex_lock(&base->print);
	printf("%ld %d %s", ft_time(base), base->philo_num, s);
	pthread_mutex_unlock(&base->print);
}

void	ft_delay(int ms)
{
	long	time;
	time = ft_start_time();
	while (ft_start_time() - time < (long)ms)
		usleep(100);
}
