/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:25:25 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/08 15:52:24 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_end_dinner(t_arg *arg)
{
	pthread_mutex_lock(&arg->arg_mutex);
	arg->end = true;
	pthread_mutex_unlock(&arg->arg_mutex);
}

bool	end_dinner(t_arg *arg)
{
	bool	res;

	pthread_mutex_lock(&arg->arg_mutex);
	res = arg->end;
	pthread_mutex_unlock(&arg->arg_mutex);
	return (res);
}

long	ft_get_time(long time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	time = current_time.tv_sec * 1000LL + current_time.tv_usec / 1000;
	return (time);
}

void	ft_clean(t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->num_philo)
	{
		pthread_mutex_destroy(&arg->philos[i].philo_mutex);
		pthread_mutex_destroy(&arg->forks[i].fork);
		i++;
	}
	pthread_mutex_destroy(&arg->arg_mutex);
	free(arg->philos);
	free(arg->forks);
}
