/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:24:28 by pgrellie          #+#    #+#             */
/*   Updated: 2024/11/29 14:17:03 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_sleep(size_t time, t_diner *diner)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (death(diner))
			break ;
		usleep(500);
	}
}

void	eat_da_shee(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo, FORK);
	pthread_mutex_lock(philo->right_fork);
	print_msg(philo, FORK);
	if (death(philo->diner))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	print_msg(philo, EAT);
	pthread_mutex_lock(&philo->diner->l_last_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->diner->l_last_meal);
	go_sleep(philo->diner->time_to_eat, philo->diner);
	if (!death(philo->diner))
	{
		pthread_mutex_lock(&philo->diner->l_count_meal);
		philo->meals_count++;
		pthread_mutex_unlock(&philo->diner->l_count_meal);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_on_the_couch(t_philo *philo)
{
	if (death(philo->diner))
		return ;
	print_msg(philo, SLEEP);
	go_sleep(philo->diner->time_to_sleep, philo->diner);
}

void	think_think(t_philo *philo)
{
	size_t	time_to_think;

	if (death(philo->diner))
		return ;
	print_msg(philo, THINK);
	if (philo->diner->philo_nb % 2 == 0)
		return ;
	else if (philo->diner->time_to_sleep > philo->diner->time_to_eat)
		return ;
	else
		time_to_think = philo->diner->time_to_eat;
	go_sleep(time_to_think, philo->diner);
}

void	*eat_train_sleep(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->diner->l_last_meal);
	philo->last_meal = philo->diner->start_time;
	pthread_mutex_unlock(&philo->diner->l_last_meal);
	wait_all_philos(philo->diner->start_time);
	if (philo->diner->philo_nb == 1)
	{
		go_sleep(philo->diner->time_to_die, philo->diner);
		if (!death(philo->diner))
			print_msg(philo, DEAD);
		return (NULL);
	}
	if (philo->position % 2 != 0)
		go_sleep(philo->diner->time_to_eat, philo->diner);
	while (!death(philo->diner))
	{
		eat_da_shee(philo);
		sleep_on_the_couch(philo);
		think_think(philo);
	}
	return (NULL);
}
