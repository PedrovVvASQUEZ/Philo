/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:47:15 by pgrellie          #+#    #+#             */
/*   Updated: 2024/11/29 13:52:30 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_philos(size_t time_start)
{
	while (get_time() < time_start)
	{
		continue ;
	}
}

bool	the_simulation(t_diner *diner)
{
	size_t	x;

	x = 0;
	diner->start_time = get_time() + (diner->philo_nb * 20);
	while (x < diner->philo_nb)
	{
		diner->philos[x].last_meal = diner->start_time;
		if (pthread_create(&diner->philos[x].thread, NULL,
				&eat_train_sleep, &diner->philos[x]) != 0)
			return (false);
		x++;
	}
	if (pthread_create(&diner->death_thread, NULL, &death_monitor, diner) != 0)
		return (false);
	x = 0;
	while (x < diner->philo_nb)
	{
		if (pthread_join(diner->philos[x].thread, NULL) != 0)
			return (false);
		x++;
	}
	if (pthread_join(diner->death_thread, NULL) != 0)
		return (false);
	return (true);
}

int	main(int ac, char **av)
{
	t_diner	diner;

	if (pre_parser(ac, av, &diner) == false)
		return (1);
	if (init_diner(&diner) == false)
		return (1);
	if (init_mutex(&diner) == false)
		return (1);
	if (the_simulation(&diner) == false)
		return (1);
	cleaner(&diner);
	return (0);
}
