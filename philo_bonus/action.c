/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 07:59:57 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/27 17:08:44 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*This function suspend the calling action*/
void	ft_thread_suspension(t_philo *philo, long action)
{
	int		i;
	long	time_to_wait;

	i = 0;
	time_to_wait = action * 1000;
	i = time_to_wait / 100000;
	while (i-- > 0 && !philo->died)
		usleep(100000);
}

/*This function write each status and terminate the program if a philo dies*/
void	ft_write_state(t_philo *philo, const char *str, long time)
{
	sem_wait(philo->print);
	//if (!philo->stop)
		printf("%li %3i %s\n", time, philo->id, str);
	sem_post(philo->print);
}

/*This function lock the forks for the philo before start eating.
Once the philo get access to the forks, it checks if time elapsed from 
last meal is greater than time to die*/
void	ft_eat(t_philo *philo)
{
	long	time;

	sem_wait(philo->fork);
	ft_write_state(philo, "has taken a fork", ft_get_time());
	sem_wait(philo->fork);
	ft_write_state(philo, "has taken a fork", ft_get_time());
	time = ft_get_time();
	sem_wait(philo->time);//
	philo->last_meal = time;
	sem_post(philo->time);//
	ft_write_state(philo, "is eating", time);
	ft_thread_suspension(philo, philo->time_to_eat);
	philo->meal_consumed++;
	sem_post(philo->fork);
	sem_post(philo->fork);
	// if (philo->meal_consumed == philo->times_dinner)
		//philo->is_full = true;
}

/*This function manage the sleeping time of each philo*/
void	ft_sleep(t_philo *philo)
{
	long	time;

	time = ft_get_time();
	ft_write_state(philo, "is sleeping", time);
	ft_thread_suspension(philo, philo->time_to_sleep);
}

/*This function manage the thinking time of each philo*/
void	ft_think(t_philo *philo)
{
	long	time;

	time = ft_get_time();
	ft_write_state(philo, "is thinking", time);
}
