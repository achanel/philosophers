/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:37:09 by achanel           #+#    #+#             */
/*   Updated: 2021/11/01 17:51:32 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// int	ft_death(t_base *base)
// {
// 	long	time;
// 	int		i;

// 	time = ft_time(base) - 2;
// 	i = 0;
// 	while (i < base->ph_number)
// 	{
// 		if (base->life_time[i] != -1)
// 		{
// 			if (base->life_time[i] + base->time_to_die < time)
// 			{
// 				sem_wait(base->print);
// 				printf("%ld %d %s", ft_time(base), i + 1, "died\n");
// 				exit(1);
// 			}
// 		}
// 		i++;
// 	}
// 	return (1);
// }

long	ft_start_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	ft_time(t_base *base)
{
	struct timeval	current_tv;

	gettimeofday(&current_tv, NULL);
	return ((current_tv.tv_sec * 1000 + current_tv.tv_usec / 1000)
		- base->start_time);
}

void	ft_delay(int ms)
{
	long	time;

	time = ft_start_time();
	while (ft_start_time() - time < (long)ms)
		usleep(100);
}
