/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:22:22 by pgrellie          #+#    #+#             */
/*   Updated: 2024/11/26 17:00:55 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/***********************/
/*  LIBRARIES IMPORTS  */
/***********************/

# include <pthread.h>
# include <string.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>

/************************/
/*       DEFINES        */
/************************/

# define NML "\033[0;39m"
# define GRAY "\033[0;90m"
# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[0;94m"
# define MAGENT "\033[0;95m"
# define CYAN "\033[0;96m"
# define WHITE "\033[0;97m"

/************************/
/*      STRUCTURES      */
/************************/

typedef struct s_philo	t_philo;
typedef struct s_diner	t_diner;

typedef struct s_philo
{
	size_t			id;
	size_t			position;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long		last_meal;
	size_t			meals_count;
	t_diner			*diner;
}			t_philo;

typedef struct s_diner
{
	t_philo			*philos;
	pthread_t		death_thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	l_dead;
	pthread_mutex_t	l_count_meal;
	pthread_mutex_t	l_print;
	pthread_mutex_t	l_last_meal;
	size_t			start_time;
	size_t			philo_nb;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			meal_nb;
	int				dead;
}			t_diner;

enum
{
	EAT = 1,
	SLEEP = 2,
	THINK = 3,
	DEAD = 4,
	FORK = 5
};

/************************/
/*	    PROTOTYPES	    */
/************************/

/**************  Utils  ****************/

void	ft_putstr_fd(char *s, int fd);
void	cleaner(t_diner *diner);
void	print_msg(t_philo *philo, int msg);

/*************  Program  ***************/

bool	pre_parser(int ac, char **av, t_diner *diner);
bool	init_diner(t_diner *diner);
bool	init_mutex(t_diner *diner);
size_t	get_time(void);
int		death(t_diner *diner);
void	set_death(t_diner *diner);
void	wait_all_philos(size_t time_start);
void	*eat_train_sleep(void *arg);
void	*death_monitor(void *arg);

#endif