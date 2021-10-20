/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:15:32 by achanel           #+#    #+#             */
/*   Updated: 2021/10/20 17:30:05 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct	s_philo
{
	pthread_t		*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	lock;
	int				ph_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eating_count;
	long			start_time;
	int				*life_time;
	int				philo_num;
	int				eats;
}	t_philo;

// philo.c

// solve_utils.c
int	ft_death(t_philo *base);
long	ft_start_time(void);
long	ft_time(t_philo *base);
void	ft_print(t_philo *base, char *s);
void	ft_delay(int ms);
// solve.c
void	*waiter_life(void *base);
void	*phil_life(void *base);
void	solve(t_philo *base);
// utils.c
void	free_base(t_philo *base);
int		ft_atoi(const char *str);
int		check_arg(int ac, char **av);
#endif