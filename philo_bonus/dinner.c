/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:28:52 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/27 10:29:13 by alimotta         ###   ########.fr       */
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
	while (!philo->stop)
	{
		time = ft_get_time();
		time_elapsed = time - philo->last_meal;
		if (time_elapsed > philo->time_to_die)
		{
			philo->died = true;
			sem_wait(philo->print);
			printf("%li %3i %s\n", time, philo->id, "died");
			philo->stop = true;
			break ;
		}
		if (philo->is_full)
		{
			philo->stop = true;
			break ;
		}
	}
	if (philo->died)
		exit (1);
	else
		exit (0);
}

/*This function creates the threads and lunch the simulation*/
void	ft_simulation(t_philo *philo)
{
	// if (pthread_create(&philo->waiter, NULL, &check_dinner, philo))
	// {
	// 	printf("Thread Creation Error\n");
	// 	exit (EXIT_FAILURE);
	// }
	if (philo->id % 2 == 0)
		usleep(1000);
		//ft_thread_suspension(philo, 1000);
		//ft_thread_suspension(philo->time_to_think);
	// while (philo->end == false)
	while (1)
	{
		//if (philo->is_full)
		//	break ;
		ft_think(philo);
		ft_eat(philo);
		ft_sleep(philo);
		// ft_write_state(philo, "is thinking", ft_get_time());
		// sem_wait (philo->fork);
		// ft_write_state(philo, "has taken a fork", ft_get_time());
		// sem_wait (philo->fork);
		// ft_write_state(philo, "has taken a fork", ft_get_time());
		// philo->last_meal = ft_get_time();
		// philo->meal_consumed++;
		// ft_write_state(philo, "is eating", philo->last_meal);
		// ft_thread_suspension(philo, philo->time_to_eat);
		// sem_post (philo->fork);
		// sem_post (philo->fork);
		// if (philo->meal_consumed == philo->times_dinner)
		// 	philo->is_full = true;
		// ft_write_state(philo, "is sleeping", ft_get_time());
		// ft_thread_suspension(philo, philo->time_to_sleep);

	}
	//pthread_join(philo->waiter, NULL);
}
