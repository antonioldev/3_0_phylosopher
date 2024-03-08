/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 07:59:57 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/08 14:14:30 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
	long	time;
	
	pthread_mutex_lock(&philo->first_fork->fork);
	printf("%li %i has taken a fork\n", ft_get_time(time), philo->id);
	pthread_mutex_lock(&philo->second_fork->fork);
	printf("%li %i has taken a fork\n", ft_get_time(time), philo->id);
	printf("%li %i is eating\n", ft_get_time(time), philo->id);
	philo->meal_consumed++;
	philo->last_meal = ft_get_time(philo->last_meal);
	usleep(philo->arg->time_to_eat * 1000);
	if (philo->meal_consumed == philo->arg->times_dinner)
		philo->is_full = true;
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

void	ft_sleep(t_philo *philo)
{
	long	time;

	printf("%li %i is sleeping\n", ft_get_time(time), philo->id);
	usleep(philo->arg->time_to_sleep * 1000);
}

void	ft_think(t_philo *philo)
{
	return ;
}
