/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:31:46 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/27 16:58:28 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>

typedef struct s_philo
{
	int				id;
	int				*pid;
	long			num_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_think;
	long			times_dinner;
	long			start;
	long			meal_consumed;
	long			last_meal;
	bool			is_full;
	bool			stop;
	bool			died;
	sem_t			*print;
	sem_t			*fork;
	sem_t			*time;//
	pthread_t		waiter;
}				t_philo;

int		ft_initiate(t_philo *philo);
void	ft_simulation(t_philo *philo);
void	ft_clean(t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
void	ft_write_state(t_philo *philo, const char *str, long time);
void	ft_thread_suspension(t_philo *philo, long action);
//bool	end_dinner(t_philo *philo);
long	ft_get_time(void);
size_t	ft_strcmp(const char *s1, const char *s2);
#endif