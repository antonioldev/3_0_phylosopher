/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:28:52 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/16 08:34:09 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_all_threads_ready(t_arg *arg)
{
	int	i;

	i = -1;
	while (++i < arg->num_philo)
		arg->philos[i].last_meal = arg->start;
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

	philo = (t_philo *)data;
	while (!all_threads_ready(philo->arg))
		usleep(100);
	pthread_mutex_lock(&philo->first_fork->fork);
	ft_write_state(philo, "has taken a fork", ft_get_time());
	pthread_mutex_unlock(&philo->first_fork->fork);
	while (!end_dinner(philo))
	{
		time = ft_get_time();
		if ((time - philo->last_meal) > philo->arg->time_to_die)
			ft_write_state(philo, "died", time);
	}
	return (NULL);
}

static void	*dinner(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	while (!all_threads_ready(philo->arg))
		usleep(1000);
	if (philo->id % 2 == 0)
		ft_thread_suspension(philo->arg->time_to_wait);
	while (!end_dinner(philo))
	{
		if (philo->is_full)
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
	if (arg->time_to_die < arg->time_to_eat)
		arg->time_to_wait = arg->time_to_die;
	else
		arg->time_to_wait = arg->time_to_eat;
	if (arg->num_philo == 1)
		pthread_create(&arg->philos[0].thread_id, NULL, dinner_alone,
			&arg->philos[0]);
	else
		while (++i < arg->num_philo)
			pthread_create(&arg->philos[i].thread_id, NULL, dinner,
				&arg->philos[i]);
	arg->start = ft_get_time();
	set_all_threads_ready(arg);
	i = -1;
	while (++i < arg->num_philo)
		pthread_join(arg->philos[i].thread_id, NULL);
	return ;
}
