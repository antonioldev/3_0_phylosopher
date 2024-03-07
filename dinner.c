/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:28:52 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/07 16:43:03 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*dinner_alone()
{
	return (NULL);
}

static void	*dinner(void *data)
{
	t_philo		*philo;

	
	philo = (t_philo *)data;
	philo->last_meal = ft_get_time(philo->last_meal);
	//printf("%li\n", philo->last_meal);
	return (NULL);
}

static void	*monitor()
{
	return (NULL);
}

void	ft_simulation(t_arg *arg)
{
	int	i;

	i = -1;
	if (arg->num_philo == 1)
		pthread_create(&arg->philos[0].thread_id, NULL, dinner_alone, NULL);
	else
		while (++i < arg->num_philo)
			pthread_create(&arg->philos[i].thread_id, NULL, dinner, &arg->philos[i]);
	pthread_create(&arg->monitor, NULL, monitor, NULL);
	arg->start = ft_get_time(arg->start);
	//printf("%li\n", arg->start);
	arg->all_thread_ready = true;
	i = 0;
	while (i < arg->num_philo)
	{
		pthread_join(arg->philos[i].thread_id, NULL);
		i++;
	}
	arg->end = true;
	pthread_join(arg->monitor, NULL);
}
