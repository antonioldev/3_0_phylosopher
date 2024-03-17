/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:46:30 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/16 17:09:52 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*This function write each status and terminate the program if a philo dies*/
void	ft_write_state(t_philo *philo, const char *str, long time)
{
	bool	end;

	end = end_dinner(philo->arg);
	//pthread_mutex_lock(&philo->arg->write_mutex);
	if (!end)
	{
		pthread_mutex_lock(&philo->arg->write_mutex);
		//if (ft_strcmp(str, "died") == 0)
		//	set_end_dinner(philo->arg);
		printf("%li %3i %s\n", time, philo->id, str);
		pthread_mutex_unlock(&philo->arg->write_mutex);
	}
	//pthread_mutex_unlock(&philo->arg->write_mutex);
}

/*This function suspend the calling action*/
void	ft_thread_suspension(long action)
{
	int		i;
	long	time_to_wait;

	i = 0;
	time_to_wait = action * 1000;
	i = time_to_wait / 100000;
	while (i-- > 0)
		usleep(100000);
}

/*This function set the end of the dinner*/
void	set_end_dinner(t_arg *arg)
{
	pthread_mutex_lock(&arg->arg_mutex);
	arg->end = true;
	pthread_mutex_unlock(&arg->arg_mutex);
}

/*This function check the status of the dinner*/
bool	end_dinner(t_arg *arg)//t_philo *philo)
{
	bool	res;

	res = false;
	pthread_mutex_lock(&arg->arg_mutex);
	res = arg->end;
	pthread_mutex_unlock(&arg->arg_mutex);
	return (res);
}
