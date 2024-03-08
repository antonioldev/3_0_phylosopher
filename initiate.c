/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:55:46 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/08 12:51:39 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(int num_philo, t_philo *philo, t_fork *forks, int i)
{
	if (philo->id % 2 == 1)
	{
		philo->first_fork = &forks[(i + 1) % num_philo];
		philo->second_fork = &forks[i];
	}
	else
	{
		philo->first_fork = &forks[i];
		philo->second_fork = &forks[(i + 1) % num_philo];
	}
}

/*Needs to handle errors for malloc or mutex init*/
void	ft_initiate(t_arg *arg)//Check comment
{
	int	i;

	i = 0;
	arg->end = false;
	arg->all_thread_ready = false;
	arg->forks = malloc(arg->num_philo * sizeof(t_fork));
	arg->philos = malloc(arg->num_philo * sizeof(t_philo));
	pthread_mutex_init(&arg->arg_mutex, NULL);
	while (i < arg->num_philo)
	{
		arg->forks[i].fork_id = i;
		pthread_mutex_init(&arg->forks[i].fork, NULL);
		arg->philos[i].id = i + 1;
		arg->philos[i].meal_consumed = 0;
		arg->philos[i].last_meal = ft_get_time(arg->philos[i].last_meal);
		arg->philos[i].is_full = false;
		arg->philos[i].arg = arg;
		pthread_mutex_init(&arg->philos[i].philo_mutex, NULL);
		assign_forks(arg->num_philo, &arg->philos[i], arg->forks, i);
		i++;
	}
}
