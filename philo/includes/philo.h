/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:15:32 by achanel           #+#    #+#             */
/*   Updated: 2021/11/15 16:06:23 by achanel          ###   ########.fr       */
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
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	lock;
	pthread_t		*philosopher;
	long			start_time;
	int				ph_number;
	int				meals;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				i;
	int				*life_time;
}	t_base;

// solve_utils.c
void	ft_error(char *message);
void	ft_print(t_base *base, int ph_index, char *s);
long	ft_cur_time(void);
long	ft_time(t_base *base);
void	ft_delay(int ms);
// solve.c
void	*waiter_life(void *void_phil);
void	*phil_life(void *void_phil);
// utils.c
int		ft_atoi(const char *str);
int		check_arg(int ac, char **av);
#endif