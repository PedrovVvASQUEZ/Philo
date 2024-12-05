/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:42:51 by pgrellie          #+#    #+#             */
/*   Updated: 2024/11/29 13:45:12 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	unsigned int	x;

	x = 0;
	if (!s)
		return ;
	while (s[x])
	{
		write(fd, &s[x], 1);
		x++;
	}
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	cleaner(t_diner *diner)
{
	size_t	i;

	i = 0;
	while (i < diner->philo_nb)
	{
		pthread_mutex_destroy(&diner->forks[i]);
		i++;
	}
	free(diner->forks);
	free(diner->philos);
	pthread_mutex_destroy(&diner->l_dead);
	pthread_mutex_destroy(&diner->l_count_meal);
	pthread_mutex_destroy(&diner->l_print);
	pthread_mutex_destroy(&diner->l_last_meal);
}

void	print_msg(t_philo *philo, int msg)
{
	pthread_mutex_lock(&philo->diner->l_print);
	if (death(philo->diner) && msg != DEAD)
	{
		pthread_mutex_unlock(&philo->diner->l_print);
		return ;
	}
	if (msg == DEAD)
	{
		printf("%s%09zu %zu died%s\n", RED,
			get_time() - philo->diner->start_time, philo->id, NML);
		set_death(philo->diner);
	}
	else if (msg == EAT)
		printf("%s%09zu %zu is eating%s\n", GREEN,
			get_time() - philo->diner->start_time, philo->id, NML);
	else if (msg == SLEEP)
		printf("%s%09zu %zu is sleeping%s\n", WHITE,
			get_time() - philo->diner->start_time, philo->id, NML);
	else if (msg == THINK)
		printf("%s%09zu %zu is thinking%s\n", CYAN,
			get_time() - philo->diner->start_time, philo->id, NML);
	else if (msg == FORK)
		printf("%s%09zu %zu has taken a fork%s\n", YELLOW,
			get_time() - philo->diner->start_time, philo->id, NML);
	pthread_mutex_unlock(&philo->diner->l_print);
}
