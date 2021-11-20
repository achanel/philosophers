/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:15:32 by achanel           #+#    #+#             */
/*   Updated: 2021/11/20 13:12:24 by achanel          ###   ########.fr       */
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
	pid_t		*philosopher;
	long		start_time;
	int			ph_number;
	int			meals;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			i;
	int			j;
	int			status;
	long		life_time;
	int			eating_times;
}	t_base;

// solve_utils_bonus.c
void	ft_error(char *message);
void	ft_print(t_base *base, int ph_index, char *s);
// int		ft_death(t_base *base);
long	ft_cur_time(void);
long	ft_time(t_base *base);
void	ft_delay(int ms);
// solve_bonus.c
void	*waiter_life(void *base);
void	phil_life(t_base *base);
void	solve(t_base *base);
// utils_bonus.c
int		ft_atoi(const char *str);
int		check_arg(int ac, char **av);
#endif