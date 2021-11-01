/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:15:32 by achanel           #+#    #+#             */
/*   Updated: 2021/11/01 17:53:49 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_base
{
	sem_t		*fork;
	sem_t		*print;
	int			ph_number;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			meals;
	long		start_time;
	int			status;
	int			is_dead;
	int			i;
	int			j;
}	t_base;

typedef struct	s_phil
{
	int			index;
	pid_t		philosopher;
	pthread_t	waiter;
	t_base		*base;
	int			phil_meals;
	int			life_time;
}				t_phil;

// solve_utils_bonus.c
void	phil_life_helper(t_base *base, int eating_times, int number);
int		ft_death(t_base *base);
long	ft_start_time(void);
long	ft_time(t_base *base);
void	ft_delay(int ms);
// solve_bonus.c
void	eating(t_base *base, t_phil *phil);
void	*waiter_life(void *base);
void	phil_life(t_base *base, t_phil *phil);
void	solve(t_base *base);
// utils_bonus.c
void	ft_error(char *message);
void	ft_print(t_base *base, t_phil *phil, char *s);
int		ft_atoi(const char *str);
int		check_arg(int ac, char **av);
#endif