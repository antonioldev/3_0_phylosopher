/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:28:52 by alimotta          #+#    #+#             */
/*   Updated: 2024/04/02 14:54:23 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*This function is used when only one philo is at the table*/
static void	*dinner_alone(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	while (!all_threads_ready(philo->arg))
		usleep(100);
	pthread_mutex_lock(&philo->first_fork->fork);
	ft_write_state(philo, "has taken a fork", ft_get_time());
	pthread_mutex_unlock(&philo->first_fork->fork);
	while (!end_dinner(philo->arg))
		;
	return (NULL);
}

/*This function waits for all threads to be ready and it loops 
through the dinner cycle till the end of the simulation*/
static void	*dinner(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	while (!all_threads_ready(philo->arg))
		usleep(500);
	ft_write_state(philo, "is thinking", ft_get_time());
	if (philo->id % 2 == 0)
		usleep(500);
	// 	ft_thread_suspension(philo->arg->time_to_think);
	while (!end_dinner(philo->arg))
	{
		if (philo->is_full)
			break ;
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

/*This function check if any of the philo died of starvation*/
static void	*check_dinner(void *data)
{
	int		i;
	long	time;
	long	time_elapsed;
	t_arg	*arg;
	t_philo	*philo;

	arg = (t_arg *)data;
	while (!end_dinner(arg))
	{
		i = -1;
		while (++i < arg->num_philo)
		{
			philo = arg->philos + i;
			time = ft_get_time();
			pthread_mutex_lock(&philo->philo_mutex);
			time_elapsed = time - philo->last_meal;
			pthread_mutex_unlock(&philo->philo_mutex);
			if (time_elapsed > arg->time_to_die && !philo->is_full)
			{
				ft_write_state(philo, "died", time);
				set_end_dinner(arg);
			}
		}
	}
	return (NULL);
}

/*This function creates the threads and lunch the simulation*/
void	ft_simulation(t_arg *arg)
{
	int	i;

	i = -1;
	if (arg->num_philo == 1)
		pthread_create(&arg->philos[0].thread_id, NULL, dinner_alone,
			&arg->philos[0]);
	else
		while (++i < arg->num_philo)
			pthread_create(&arg->philos[i].thread_id, NULL, dinner,
				&arg->philos[i]);
	arg->start = ft_get_time();
	set_all_threads_ready(arg);
	pthread_create(&arg->waiter, NULL, check_dinner, arg);
	i = -1;
	while (++i < arg->num_philo)
		pthread_join(arg->philos[i].thread_id, NULL);
	set_end_dinner(arg);
	pthread_join(arg->waiter, NULL);
}
