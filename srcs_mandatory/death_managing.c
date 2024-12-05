/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_managing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:37:53 by pgrellie          #+#    #+#             */
/*   Updated: 2024/11/26 15:43:40 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death(t_diner *diner)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&diner->l_dead);
	if (diner->dead)
		ret = 1;
	pthread_mutex_unlock(&diner->l_dead);
	return (ret);
}

void	set_death(t_diner *diner)
{
	pthread_mutex_lock(&diner->l_dead);
	diner->dead = 1;
	pthread_mutex_unlock(&diner->l_dead);
}

int	check_death(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->diner->l_last_meal);
	time = get_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->diner->l_last_meal);
	if (time >= philo->diner->time_to_die)
	{
		set_death(philo->diner);
		usleep(1000);
		print_msg(philo, DEAD);
		return (1);
	}
	return (0);
}

int	handle_end(t_diner *diner)
{
	size_t	x;
	int		ret;

	ret = 1;
	x = 0;
	while (x < diner->philo_nb)
	{
		if (check_death(&diner->philos[x]))
			return (1);
		if (diner->meal_nb)
		{
			pthread_mutex_lock(&diner->l_count_meal);
			if (diner->philos[x].meals_count < diner->meal_nb)
				ret = 0;
			pthread_mutex_unlock(&diner->l_count_meal);
		}
		x++;
	}
	if (diner->meal_nb && ret)
	{
		set_death(diner);
		return (1);
	}
	else
		return (0);
}

void	*death_monitor(void *arg)
{
	t_diner	*diner;

	diner = (t_diner *)arg;
	wait_all_philos(diner->start_time);
	while (!death(diner))
	{
		if (handle_end(diner))
			break ;
		usleep(1000);
	}
	return (NULL);
}
