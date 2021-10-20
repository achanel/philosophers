/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:06:03 by achanel           #+#    #+#             */
/*   Updated: 2021/10/20 18:40:44 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*waiter_life(void *base)
{
	int	flag;

	flag = 1;
	while (flag)
	{
		flag = ft_death((t_philo *)base);
		if (((t_philo *)base)->eating_count > 0 && flag)
			flag = 0;
	}
	ft_death(4);
	return (NULL);
}

void	*phil_life(void *base)
{
	
}

void	solve(t_philo *base)
{
	pthread_t	waiter;
	int			i;
	
	i = -1;
	pthread_mutex_init(&base->lock, NULL);
	pthread_mutex_init(&base->print, NULL);
	while (++i < base->philo_num)
		pthread_mutex_init(&base->fork[i], NULL);
	i = -1;
	while (++i < base->philo_num)
	{
		pthread_mutex_lock(&base->lock);
		pthread_create(&base->philo[i], NULL, phil_life, (void *)base);
		pthread_detach(&base->philo[i]);
		pthread_mutex_lock(&base->lock);
		i++;
		pthread_mutex_unlock(&base->lock);
	}
	pthread_mutex_destroy(&base->lock);
	pthread_create(&base->philo[i], NULL, waiter_life, (void *)base);
	pthread_join(&waiter, NULL);
	pthread_mutex_destroy(&base->print);
	i = -1;
	while (++i < base->philo_num)
		pthread_mutex_destroy(&base->fork[i]);
}
