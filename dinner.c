/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:28:52 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/09 12:51:51 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*dinner_alone(void *data)
{
	long		time;
	t_philo		*philo;

	time = 0;
	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->first_fork->fork);
	printf("%li %i has taken a fork\n", ft_get_time(time), philo->id);
	pthread_mutex_unlock(&philo->first_fork->fork);
	while (!end_dinner(philo->arg))
	{
		time = ft_get_time(time);
		if ((time - philo->last_meal) > philo->arg->time_to_die)
		{
			set_end_dinner(philo);// helgrind error
			ft_write_state(philo, "has died");
		}
		if (philo->is_full || philo->arg->end)
			break ;
	}
	return (NULL);
}

static void	*dinner(void *data)
{
	long		time;
	t_philo		*philo;

	time = 0;
	philo = (t_philo *)data;
	while (!wait_all_threads(philo->arg))
		;
	while (!end_dinner(philo->arg))
	{
		time = ft_get_time(time);
		if ((time - philo->last_meal) > philo->arg->time_to_die)
		{
			//set_end_dinner(philo);// helgrind error
			ft_write_state(philo, "has died");
			//printf("%li %i has died\n", time, philo->id);
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

	arg->start = ft_get_time(arg->start);
	i = -1;
	if (arg->num_philo == 1)
		pthread_create(&arg->philos[0].thread_id, NULL, dinner_alone,
			&arg->philos[0]);
	else
		while (++i < arg->num_philo)
			pthread_create(&arg->philos[i].thread_id, NULL, dinner,
				&arg->philos[i]);
	arg->all_thread_ready = true;
	i = -1;
	while (++i < arg->num_philo)
		pthread_join(arg->philos[i].thread_id, NULL);
}
