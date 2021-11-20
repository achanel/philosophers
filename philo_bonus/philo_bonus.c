/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:21:33 by achanel           #+#    #+#             */
/*   Updated: 2021/11/20 15:20:03 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	solve(t_base *base)
{
	base->i = -1;
	while (++base->i < base->ph_number)
	{
		base->philosopher[base->i] = fork();
		if (base->philosopher[base->i] == -1)
			ft_error("PID ERROR\n");
		if (!base->philosopher[base->i])
			phil_life(base);
	}
	base->i = -1;
	while (++base->i < base->ph_number)
	{
		waitpid(-1, &(base->status), 0);
		if (base->status != 0)
		{
			base->j = -1;
			while (++base->j < base->ph_number)
				kill(base->philosopher[base->j], SIGKILL);
		}
		base->i++;
	}
}

static void	base_init(t_base *base, int ac, char **av)
{
	base->philosopher = NULL;
	base->eating_times = 0;
	base->ph_number = ft_atoi(av[1]);
	base->time_to_die = ft_atoi(av[2]);
	base->time_to_eat = ft_atoi(av[3]);
	base->time_to_sleep = ft_atoi(av[4]);
	base->meals = -1;
	if (ac == 6)
		base->meals = ft_atoi(av[5]);
	base->start_time = ft_cur_time();
	sem_unlink("fork");
	sem_unlink("print");
	base->fork = sem_open("fork", O_CREAT, S_IRWXG, base->ph_number);
	base->print = sem_open("print", O_CREAT, S_IRWXG, 1);
	if (base->fork == SEM_FAILED || base->print == SEM_FAILED)
		ft_error("SEM_FAILED ERROR\n");
	base->philosopher = (pid_t *)malloc(sizeof(pid_t) * base->ph_number);
	if (!(base->philosopher))
		ft_error("MALLOC ERROR\n");
}

int	main(int ac, char **av)
{
	t_base	*base;

	if (ac < 5 || ac > 6 || check_arg(ac, av))
		ft_error("ARG ERROR\n");
	base = (t_base *)malloc(sizeof(t_base));
	if (!base)
		ft_error("MALLOC ERROR\n");
	base_init(base, ac, av);
	solve(base);
	sem_unlink("fork");
	sem_unlink("print");
	sem_close(base->fork);
	sem_close(base->print);
	if (base->philosopher)
		free(base->philosopher);
	if (base)
		free(base);
	return (0);
}
