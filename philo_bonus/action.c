/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 07:59:57 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/27 10:04:17 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*This function write each status and terminate the program if a philo dies*/
void	ft_write_state(t_philo *philo, const char *str, long time)
{
	//bool	end;

	//end = philo->end;
	//if (!end)
	//{
	sem_wait(philo->print);
	if (!philo->stop)
		printf("%li %3i %s\n", time, philo->id, str);
	sem_post(philo->print);
	//}
}

/*This function lock the forks for the philo before start eating.
Once the philo get access to the forks, it checks if time elapsed from 
last meal is greater than time to die*/
void	ft_eat(t_philo *philo)
{
	long	time;
	// bool	end;

	// end = philo->end;
	// if (!end)
	// {
		sem_wait (philo->fork);
		ft_write_state(philo, "has taken a fork", ft_get_time());
		sem_wait (philo->fork);
		ft_write_state(philo, "has taken a fork", ft_get_time());
		time = ft_get_time();
		philo->last_meal = time;
		philo->meal_consumed++;
		ft_write_state(philo, "is eating", philo->last_meal);
		ft_thread_suspension(philo, philo->time_to_eat);
		sem_post (philo->fork);
		sem_post (philo->fork);
		if (philo->meal_consumed == philo->times_dinner)
			philo->is_full = true;

	//}
}

/*This function manage the sleeping time of each philo*/
void	ft_sleep(t_philo *philo)
{
	long	time;
	// bool	end;

	// end = philo->end;
	// if (!end)
	// {
		time = ft_get_time();
		ft_write_state(philo, "is sleeping", time);
		ft_thread_suspension(philo, philo->time_to_sleep);
	//}
}

/*This function manage the thinking time of each philo*/
void	ft_think(t_philo *philo)
{
	long	time;
	// bool	end;

	// end = philo->end;
	// if (!end)
	// {
		time = ft_get_time();
		ft_write_state(philo, "is thinking", time);
	//}
}
