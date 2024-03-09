/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 07:59:57 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/09 17:43:26 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_write_state(t_philo *philo, const char *str)
{
	long	time;

	time = 0;
	if (!(philo->arg->end))
	{
		pthread_mutex_lock(&philo->arg->write_mutex);
		printf("%li %i %s\n", ft_get_time(time), philo->id, str);
		pthread_mutex_unlock(&philo->arg->write_mutex);
	}
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	ft_write_state(philo, "has taken a fork");
	pthread_mutex_lock(&philo->second_fork->fork);
	ft_write_state(philo, "has taken a fork");
	ft_write_state(philo, "is eating");
	philo->meal_consumed++;
	philo->last_meal = ft_get_time(philo->last_meal);
	//usleep(philo->arg->time_to_eat * 1000);
	if (philo->meal_consumed == philo->arg->times_dinner)
		philo->is_full = true;
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

void	ft_sleep(t_philo *philo)
{
	ft_write_state(philo, "is sleeping");
	//usleep(1000);//(philo->arg->time_to_sleep * 1000);
}

void	ft_think(t_philo *philo)
{
	if (philo->is_full)
		return ;
	return ;
}
