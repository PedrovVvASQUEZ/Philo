/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:50:35 by pgrellie          #+#    #+#             */
/*   Updated: 2024/11/29 13:45:17 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char x)
{
	if (x >= 48 && x <= 57)
		return (1);
	else
		return (0);
}

unsigned long	ft_atol(const char *str, bool *error)
{
	int				x;
	int				sign;
	unsigned long	res;

	x = 0;
	sign = 1;
	res = 0;
	if (str[x] == '-' || str[x] == '+')
	{
		if (str[x] == '-')
			sign = -1;
		x++;
	}
	while (str[x] >= '0' && str[x] <= '9')
	{
		res = (str[x] - '0') + res * 10;
		x++;
	}
	if (res > INT_MAX && sign == 1)
		*error = true;
	return (res * sign);
}

bool	args_check(char **av)
{
	int	x;
	int	y;
	int	len;

	y = 1;
	while (av[y] && y < 6)
	{
		x = 0;
		len = 0;
		if (av[y][x] == '+')
			x++;
		while (av[y][x])
		{
			if (!ft_isdigit(av[y][x]) || len > 10)
			{
				ft_putstr_fd(RED"\nError: wrong arguments\n\n"NML, 2);
				return (false);
			}
			x++;
			len++;
		}
		y++;
	}
	return (true);
}

bool	pre_parser(int ac, char **av, t_diner *diner)
{
	bool	error;

	error = false;
	if (ac < 5 || ac > 6)
		return (ft_putstr_fd(RED"\n/! Number of arguments\n\n"NML, 2), false);
	if (args_check(av) == false)
		return (false);
	diner->philo_nb = ft_atol(av[1], &error);
	if (diner->philo_nb > 200)
		return (ft_putstr_fd(RED "\n/! Too many philos\n\n"NML, 2), false);
	diner->time_to_die = ft_atol(av[2], &error);
	diner->time_to_eat = ft_atol(av[3], &error);
	diner->time_to_sleep = ft_atol(av[4], &error);
	diner->start_time = get_time() + diner->philo_nb * 10;
	if (ac == 6)
		diner->meal_nb = ft_atol(av[5], &error);
	else
		diner->meal_nb = 0;
	if (diner->philo_nb < 1 || diner->time_to_die < 60
		|| diner->time_to_eat < 60 || diner->time_to_sleep < 60
		|| (ac == 6 && diner->meal_nb < 1))
		return (ft_putstr_fd(RED"\nError: wrong arguments\n\n"NML, 2), false);
	return (true);
}
