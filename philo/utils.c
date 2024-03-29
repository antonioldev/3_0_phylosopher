/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:25:25 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/16 11:13:00 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Compare if two strings are equal*/
size_t	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2 [i]);
		i++;
	}
	return (0);
}

/*This function get the time and convert into milliseconds*/
long	ft_get_time(void)
{
	long			time;
	struct timeval	current_time;

	time = 0;
	gettimeofday(&current_time, NULL);
	time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time);
}

/*This function destroys all mutex and free memory allocated by malloc*/
void	ft_clean(t_arg *arg)
{
	int	i;

	i = -1;
	while (++i < arg->num_philo)
	{
		pthread_mutex_destroy(&arg->philos[i].philo_mutex);
		pthread_mutex_destroy(&arg->forks[i].fork);
	}
	pthread_mutex_destroy(&arg->write_mutex);
	pthread_mutex_destroy(&arg->arg_mutex);
	free(arg->philos);
	free(arg->forks);
}
