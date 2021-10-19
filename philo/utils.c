/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:22:35 by achanel           #+#    #+#             */
/*   Updated: 2021/10/19 12:51:54 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *str)
{
	int		neg;
	long	res;

	neg = 1;
	res = 0;
	while (*str != '\0' && (*str == ' ' || *str == '\n' || *str == '\t'
			|| *str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
		neg = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str != '\0' && (*str >= '0' && *str <= '9'))
	{
		if ((((res * 10) + (*str - '0')) < res) && (neg == 1))
			return (-1);
		else if ((((res * 10) + (*str - '0')) < res) && (neg == -1))
			return (0);
		res = (res * 10) + *str - '0';
		++str;
	}
	res *= neg;
	return ((int)res);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	check_arg(int ac, char **av)
{
	int	i;

	i = 0;
	ac -= 1;
	while (ac)
	{
		while(av[ac][i])
		{
			i = 0;
			if (!ft_isdigit(av[ac][i]))
				return (1);
			i++;
		}
		if (ft_atoi(av[ac]) < 1)
			return (1);
	}
	return (0);
}
