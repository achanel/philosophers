/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:15:32 by achanel           #+#    #+#             */
/*   Updated: 2021/11/01 16:15:21 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_base
{
	pthread_t		*philosopher;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	int				ph_number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals;
	long			start_time;
	int				*life_time;
	int				i;
}	t_base;

// solve_utils.c
void	phil_life_helper(t_base *base, int eating_times, int number);
int		ft_death(t_base *base);
long	ft_start_time(void);
long	ft_time(t_base *base);
void	ft_delay(int ms);
// solve.c
void	eating(t_base *base, int number);
void	*waiter_life(void *base);
void	*phil_life(void *base);
void	solve(t_base *base);
// utils.c
void	ft_error(char *message);
void	ft_print(t_base *base, int phil_number, char *s);
int		ft_atoi(const char *str);
int		check_arg(int ac, char **av);
#endif