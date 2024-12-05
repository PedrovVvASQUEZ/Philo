/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:57:51 by pgrellie          #+#    #+#             */
/*   Updated: 2024/11/29 15:38:13 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_mutex(t_diner *diner)
{
	if (pthread_mutex_init(&diner->l_dead, NULL))
		return (false);
	if (pthread_mutex_init(&diner->l_count_meal, NULL))
		return (false);
	if (pthread_mutex_init(&diner->l_print, NULL))
		return (false);
	if (pthread_mutex_init(&diner->l_last_meal, NULL))
		return (false);
	return (true);
}

void	philo_forks_init(t_philo *philo, size_t x)
{
	if (philo->position % 2 == 0)
	{
		philo->left_fork = &philo->diner->forks[x];
		philo->right_fork = &philo->diner->forks[(x + 1)
			% philo->diner->philo_nb];
	}
	else
	{
		philo->right_fork = &philo->diner->forks[x];
		philo->left_fork = &philo->diner->forks[(x + 1)
			% philo->diner->philo_nb];
	}
}

bool	init_philos(t_diner *diner)
{
	size_t	x;

	diner->philos = malloc(sizeof(t_philo) * diner->philo_nb);
	if (!diner->philos)
		return (false);
	x = 0;
	memset(diner->philos, 0, sizeof(t_philo) * diner->philo_nb);
	while (x < diner->philo_nb)
	{
		diner->philos[x].id = x + 1;
		diner->philos[x].position = x + 1;
		diner->philos[x].diner = diner;
		x++;
	}
	return (true);
}

bool	init_forks(t_diner *diner)
{
	size_t	x;

	diner->forks = malloc(sizeof(pthread_mutex_t) * diner->philo_nb);
	if (!diner->forks)
	{
		free(diner->philos);
		return (false);
	}
	x = 0;
	while (x < diner->philo_nb)
	{
		if (pthread_mutex_init(&diner->forks[x], NULL) != 0)
		{
			free(diner->philos);
			free(diner->forks);
			return (false);
		}
		philo_forks_init(&diner->philos[x], x);
		x++;
	}
	return (true);
}

bool	init_diner(t_diner *diner)
{
	if (init_philos(diner) == false
		|| init_forks(diner) == false)
		return (false);
	diner->dead = 0;
	return (true);
}
