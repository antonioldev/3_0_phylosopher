/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 07:59:57 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/14 16:53:34 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_write_state(t_philo *philo, const char *str, long time)
{
	if (!(philo->arg->end))
	{
		pthread_mutex_lock(&philo->arg->write_mutex);
		pthread_mutex_lock(&philo->arg->arg_mutex);
		if (ft_strcmp(str, "died") == 0)
			philo->arg->end = true;
		pthread_mutex_unlock(&philo->arg->arg_mutex);
		printf("%li %i %s\n", time, philo->id, str);
		pthread_mutex_unlock(&philo->arg->write_mutex);
	}
}

void	ft_thread_suspension(t_philo *philo, long action)
{
	int		i;
	long	time_to_wait;

	i = 0;
	pthread_mutex_lock(&philo->arg->arg_mutex);
	time_to_wait = action * 1000;
	pthread_mutex_unlock(&philo->arg->arg_mutex);
	i = time_to_wait / 100000;
	while (i-- > 0)
		usleep(100000);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	ft_write_state(philo, "has taken a fork", ft_get_time());
	pthread_mutex_lock(&philo->second_fork->fork);
	ft_write_state(philo, "has taken a fork", ft_get_time());
	philo->meal_consumed++;
	philo->last_meal = ft_get_time();
	ft_write_state(philo, "is eating", philo->last_meal);
	ft_thread_suspension(philo, philo->arg->time_to_eat);
	if (philo->meal_consumed == philo->arg->times_dinner)
		philo->is_full = true;
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

void	ft_sleep(t_philo *philo)
{
	long	time;
	bool	end;

	end = end_dinner(philo);
	if (!end)
	{
		time = ft_get_time();
		ft_write_state(philo, "is sleeping", time);
		ft_thread_suspension(philo, philo->arg->time_to_sleep);
	}
}

void	ft_think(t_philo *philo)
{
	long	time;
	bool	end;

	end = end_dinner(philo);
	if (!end)
	{
		time = ft_get_time();
		ft_write_state(philo, "is thinking", time);
		ft_thread_suspension(philo, philo->arg->time_to_think);
	}
}
