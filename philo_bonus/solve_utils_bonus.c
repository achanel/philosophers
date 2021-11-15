/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:37:09 by achanel           #+#    #+#             */
/*   Updated: 2021/11/15 17:29:53 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_error(char *message)
{
	int	i;

	i = 0;
	while (message[i] != '\0')
		i++;
	write(2, message, i);
	exit (1);
}

void	ft_print(t_base *base, int ph_index, char *s)
{
	sem_wait(base->print);
	printf("%ld %d %s\n", ft_time(base), ph_index, s);
	sem_post(base->print);
}

long	ft_cur_time(void)
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

	time = ft_cur_time();
	while (ft_cur_time() - time < (long)ms)
		usleep(100);
}
