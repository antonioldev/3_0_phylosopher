/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:28:52 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/08 17:02:15 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*dinner_alone(void *data)
{
	long		time;
	t_philo		*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->first_fork->fork);
	printf("%li %i has taken a fork\n", ft_get_time(time), philo->id);
	pthread_mutex_unlock(&philo->first_fork->fork);
	while(!end_dinner(philo->arg))
		usleep(200);
	return (NULL);
}

static void	*dinner(void *data)
{
	long		time;
	t_philo		*philo;

	philo = (t_philo *)data;
	while (!end_dinner(philo->arg))
	{
		time = ft_get_time(time);
		printf("             %li || %li\n",time - philo->last_meal, philo->arg->time_to_die);//
		if ((time - philo->last_meal) > philo->arg->time_to_die)
		{
			set_end_dinner(philo->arg);
			printf("%li %i has died\n", time, philo->id);
		}
		if (philo->is_full || philo->arg->end)
			break ;
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

static void	*monitor()
{
	return (NULL);
}

void	ft_simulation(t_arg *arg)
{
	int	i;

	arg->start = ft_get_time(arg->start);
	i = -1;
	if (arg->num_philo == 1)
		pthread_create(&arg->philos[0].thread_id, NULL, dinner_alone,
			&arg->philos[0]);
	else
		while (++i < arg->num_philo)
			pthread_create(&arg->philos[i].thread_id, NULL, dinner,
				&arg->philos[i]);
	pthread_create(&arg->monitor, NULL, monitor, NULL);
	arg->all_thread_ready = true;
	i = -1;
	while (++i < arg->num_philo)
		pthread_join(arg->philos[i].thread_id, NULL);
	arg->end = true;
	pthread_join(arg->monitor, NULL);
}
