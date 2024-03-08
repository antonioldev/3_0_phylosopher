/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:31:46 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/08 12:51:26 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_arg	t_arg;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork;
}			t_fork;

typedef struct s_philo
{
	int				id;
	int				meal_consumed;
	bool			is_full;
	long			last_meal;
	t_fork			*first_fork;
	t_fork			*second_fork;
	t_arg			*arg;
	pthread_t		thread_id;
	pthread_mutex_t	philo_mutex;
}				t_philo;

typedef struct s_arg
{
	long			num_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			times_dinner;
	long			start;
	//long			threads_running_nbr;
	bool			end;
	bool			all_thread_ready;
	t_fork			*forks;
	t_philo			*philos;
	pthread_t		monitor;
	pthread_mutex_t	arg_mutex;
	//pthread_mutex_t		write_mutex;
}				t_arg;

void	ft_initiate(t_arg *arg);
void	ft_simulation(t_arg *arg);
void	ft_clean(t_arg *arg);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
long	ft_get_time(long time);
bool	end_dinner(t_arg *arg);
#endif