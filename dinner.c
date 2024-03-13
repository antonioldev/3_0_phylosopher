/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:28:52 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/13 17:34:09 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_all_threads_ready(t_arg *arg)
{
	pthread_mutex_lock(&arg->arg_mutex);
	arg->all_thread_ready = true;
	pthread_mutex_unlock(&arg->arg_mutex);
}

static bool	all_threads_ready(t_arg *arg)
{
	bool	res;

	pthread_mutex_lock(&arg->arg_mutex);
	res = arg->all_thread_ready;
	pthread_mutex_unlock(&arg->arg_mutex);
	return (res);
}

static void	*dinner_alone(void *data)
{
	long		time;
	t_philo		*philo;

	//time = 0;
	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->first_fork->fork);
	printf("%li %i has taken a fork\n", ft_get_time(), philo->id);
	pthread_mutex_unlock(&philo->first_fork->fork);
	while (!end_dinner(philo))
	{
		time = ft_get_time();
		if ((time - philo->last_meal) > philo->arg->time_to_die)
		{
			ft_write_state(philo, "died", time);
			//set_end_dinner(philo);
		}
		if (philo->is_full || philo->arg->end)
			break ;
	}
	return (NULL);
}

static void	*dinner(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	while (!all_threads_ready(philo->arg))
		usleep(10);
	while (!end_dinner(philo))
	{
		long time = 0;
		time = ft_get_time();
		if ((time - philo->last_meal) > philo->arg->time_to_die)
		{
			ft_write_state(philo, "died", time);
			set_end_dinner(philo);		
		}
		if (philo->is_full || philo->arg->end)
			break ;
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

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
	// i = -1;
	// while (++i < arg->num_philo)
	// {
	// 	pthread_mutex_lock(&arg->philos[i].philo_mutex);
	// 	arg->philos[i].last_meal = arg->start;
	// 	pthread_mutex_unlock(&arg->philos[i].philo_mutex);
	// }
	set_all_threads_ready(arg);
	
	
	// i = -1;
	// while (++i < arg->num_philo)
	// {
	// 	printf("ID : %i  %li ------------------------\n",arg->philos[i].id, ft_get_time() - arg->philos[i].last_meal);
		
	// 	long time =0;
	// 	time =ft_get_time(); 
	// 	if ((time - arg->philos[i].last_meal) > arg->time_to_die)
	// 		return (ft_write_state(&arg->philos[i], "died"));
	// 	if (i == arg->num_philo - 1)
	// 		i = -1;
	// }
	i = -1;
	while (++i < arg->num_philo)
		pthread_join(arg->philos[i].thread_id, NULL);
	return ;
}
