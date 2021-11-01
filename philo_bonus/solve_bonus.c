/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:06:03 by achanel           #+#    #+#             */
/*   Updated: 2021/11/01 17:56:25 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_base *base, t_phil *phil)
{
	sem_wait(base->fork);
	ft_print(base, phil, "has taken a fork");
	sem_wait(base->fork);
	ft_print(base, phil, "has taken a fork");
	phil->life_time = ft_time(base);
	ft_print(base, phil, "is eating");
	phil->phil_meals++;
	ft_delay(base->time_to_eat);
	sem_post(base->fork);
	sem_post(base->fork);
	if (phil->phil_meals == base->meals)
		exit (0);
}

void	*waiter_life(void *phil)
{
	long	time;

	time = ft_time(((t_phil *)phil)->base) - 2;
	while (1)
	{
		ft_delay(4);
		if (((t_phil *)phil)->base->time_to_die <= time - ((t_phil *)phil)->life_time)
		{
			sem_wait(((t_phil *)phil)->base->print);
			printf("%ld %d %s", ft_time(((t_phil *)phil)->base), ((t_phil *)phil)->index + 1, "died\n");
			((t_phil *)phil)->base->is_dead = 1;
			exit(1);
		}
	}
	return (NULL);
}

void	phil_life(t_base *base, t_phil *phil)
{
	if (pthread_create(&(phil->waiter), NULL, waiter_life, (void *)phil) != 0)
		ft_error("THREAD ERROR");
	pthread_detach(phil->waiter);
	if (!phil->index % 2)
		ft_delay(base->time_to_eat / 2);
	while (1)
	{
		eating(base, phil);
		ft_print(base, phil, "is sleeping");
		ft_delay(base->time_to_sleep);
		ft_print(base, phil, "is thinking");
	}
}

void	solve(t_base *base)
{
	t_phil phil[base->ph_number];
	
	sem_unlink("fork");
	sem_unlink("print");
	base->i = 0;
	while (base->i < base->ph_number)
	{
		base->fork = sem_open("fork", O_CREAT, S_IRWXG, base->ph_number);
		if (base->fork == SEM_FAILED)
			ft_error("SEM_OPEN ERROR");
		phil[base->i].index = base->i;
		phil[base->i].base = base;
		phil[base->i].life_time = base->start_time;
		phil[base->i].phil_meals = 0;
		base->i++;
	}
	base->is_dead = 0;
	base->print = sem_open("print", O_CREAT, S_IRWXG, 1);
	if (base->print == SEM_FAILED)
		ft_error("SEM_OPEN ERROR");
	base->i = 0;
	while (base->i < base->ph_number)
	{	
		phil[base->i].philosopher = fork();
		if (phil[base->i].philosopher == -1)
			ft_error("PROCESS ERROR");
		if (phil[base->i].philosopher == 0)
			phil_life(base, &(phil[base->i]));
		base->i++;
	}
	base->i = 0;
	base->j = 0;
	while (base->i < base->ph_number)
	{
		waitpid(-1, &(base->status), 0);
		if (base->status != 0)
		{
			base->j = 0;
			while (base->j < base->ph_number)
			{
				kill(phil[base->j].philosopher, SIGTERM);
				base->j++;
			}
		}
		base->i++;
	}
	sem_close(base->fork);
	sem_close(base->print);
	sem_unlink("fork");
	sem_unlink("print");
}
