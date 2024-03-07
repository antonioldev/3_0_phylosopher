/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:55:46 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/07 11:58:08 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks_to_philo(int num_philo, t_philo *philo, t_fork *forks, int i)
{
	if (philo->id % 2 == 1)
	{
		philo->first_fork = &forks[(i + 1) % num_philo];
		philo->second_fork = &forks[i];
		//printf("Philo %i, first %i, second %i\n", i, (i + 1) % num_philo, i);
	}
	else
	{
		philo->first_fork = &forks[i];
		philo->second_fork = &forks[(i + 1) % num_philo];
		//printf("Philo %i, first %i, second %i\n", i, i, (i + 1) % num_philo);
	}
}

void	ft_initiate(t_arg *arg)
{
	int	i;

	i = 0;
	arg->end = false;
	arg->all_thread_ready = false;
	arg->forks = malloc(arg->num_philo * sizeof(t_fork));
	arg->philos = malloc(arg->num_philo * sizeof(t_philo));
	// CHECK MALLOC FAIL
	while (i < arg->num_philo)
	{
		arg->forks[i].fork_id = i;
		pthread_mutex_init(&arg->forks[i].fork_mutex, NULL); //ERROR
		arg->philos[i].id = i + 1;
		arg->philos[i].meal_consumed = 0;
		arg->philos[i].is_full = false;
		pthread_mutex_init(&arg->philos[i].philo_mutex, NULL); //ERROR
		assign_forks_to_philo(arg->num_philo, &arg->philos[i], arg->forks, i);
		i++;
	}
}