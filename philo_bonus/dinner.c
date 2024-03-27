/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:28:52 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/27 17:17:47 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*This function is used when only one philo is at the table*/
// static void	*dinner_alone(void *data)
// {
// 	t_philo		*philo;

// 	philo = (t_philo *)data;
// 	while (!all_threads_ready(philo->arg))
// 		usleep(100);
// 	pthread_mutex_lock(&philo->first_fork->fork);
// 	ft_write_state(philo, "has taken a fork", ft_get_time());
// 	pthread_mutex_unlock(&philo->first_fork->fork);
// 	while (!end_dinner(philo->arg))
// 		;
// 	return (NULL);
// }

/*This function waits for all threads to be ready and it loops 
through the dinner cycle till the end of the simulation*/
// static void	*dinner(void *data)
// {
// 	t_philo		*philo;

// 	philo = (t_philo *)data;
// 	while (!all_threads_ready(philo->arg))
// 		usleep(1000);
	
// }

/*This function check if any of the philo died of starvation*/
static void	*check_dinner(void *data)
{
	long	time_elapsed;
	long	time;
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		usleep(100);
		time = ft_get_time();
		sem_wait(philo->time);
		time_elapsed = time - philo->last_meal;
		sem_post(philo->time);
		if (time_elapsed > philo->time_to_die)
		{
			philo->died = true;
			sem_wait(philo->print);
			printf("%li %3i %s\n", time, philo->id, "died");
			philo->stop = true;
			break ;
		}
		// if (philo->meal_consumed >= philo->times_dinner)
		// {
		// 	philo->stop = true;
		// 	break ;
		// }
	}
	if (philo->died)
		exit (1);
	else
		exit (0);
}

/*This function creates the threads and lunch the simulation*/
void	ft_simulation(t_philo *philo)
{
	// pthread_create(&philo->waiter, NULL, &check_dinner, philo);
	if (philo->id % 2 == 0)
		usleep(1000);
	pthread_create(&philo->waiter, NULL, &check_dinner, philo);
	while (1)
	{
		// ft_think(philo);
		// ft_eat(philo);
		// ft_sleep(philo);


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
		time = ft_get_time();
		ft_write_state(philo, "is sleeping", time);
		ft_thread_suspension(philo, philo->time_to_sleep);
		time = ft_get_time();
		ft_write_state(philo, "is thinking", time);
	}
	pthread_join(philo->waiter, NULL);
}
