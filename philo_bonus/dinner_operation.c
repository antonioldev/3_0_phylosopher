/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:46:30 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/27 09:52:43 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*This function is called after all threads have been created
It sets the starting time of the simulation*/
// void	set_all_threads_ready(t_arg *arg)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < arg->num_philo)
// 		arg->philos[i].last_meal = arg->start;
// 	pthread_mutex_lock(&arg->arg_mutex);
// 	arg->all_thread_ready = true;
// 	pthread_mutex_unlock(&arg->arg_mutex);
// }

/*This function check if all threads are ready*/
// bool	all_threads_ready(t_arg *arg)
// {
// 	bool	res;

// 	pthread_mutex_lock(&arg->arg_mutex);
// 	res = arg->all_thread_ready;
// 	pthread_mutex_unlock(&arg->arg_mutex);
// 	return (res);
// }

/*This function suspend the calling action*/
void	ft_thread_suspension(t_philo *philo, long action)
{
	int		i;
	long	time_to_wait;

	i = 0;
	time_to_wait = action * 1000;
	i = time_to_wait / 100000;
	while (i-- > 0 && !philo->stop)
		usleep(100000);
}

/*This function set the end of the dinner*/
// void	set_end_dinner(t_philo *philo)
// {
// 	pthread_mutex_lock(&arg->arg_mutex);
// 	arg->end = true;
// 	pthread_mutex_unlock(&arg->arg_mutex);
// }

/*This function check the status of the dinner*/
// bool	end_dinner(t_philo *philo)
// {
// 	bool	res;

// 	res = false;
// 	//pthread_mutex_lock(&arg->arg_mutex);
// 	res = arg->end;
// 	//pthread_mutex_unlock(&arg->arg_mutex);
// 	return (res);
// }
