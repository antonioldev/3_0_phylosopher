/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:55:46 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/16 13:13:52 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*This function assigne the forks to each philo*/
static void	assign_forks(int num_philo, t_philo *philo, t_fork *forks, int i)
{
	int	next;

	next = (i + 1) % num_philo;
	if (philo->id % 2 == 1)
	{
		philo->first_fork = &forks[i];
		philo->second_fork = &forks[next];
	}
	else
	{
		philo->first_fork = &forks[next];
		philo->second_fork = &forks[i];
	}
}

static int	ft_allocate_memory(t_fork **fork, t_philo **philo, int n)
{
	*fork = malloc(n * sizeof(t_fork));
	if (*fork == NULL)
		return (-1);
	*philo = malloc(n * sizeof(t_philo));
	if (*philo == NULL)
		return (free(*fork), -1);
	return (0);
}

static int	ft_init_mutex(t_arg *arg)
{
	int	i;
	
	if (pthread_mutex_init(&arg->arg_mutex, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&arg->write_mutex, NULL) != 0)
		return (-1);
	i = -1;
	while (++i < arg->num_philo)
		if (pthread_mutex_init(&arg->forks[i].fork, NULL) != 0)
			return (-1);
	return (0);
}

/*This function initiate variables and allocate memory for philos and forks*/
int	ft_initiate(t_arg *arg)
{
	int	i;//

	i = -1;
	if (ft_allocate_memory(&arg->forks, &arg->philos, arg->num_philo) != 0
		|| ft_init_mutex(arg) != 0)
		return (printf("Memory Error\n"), -1);
	arg->end = false;
	arg->all_thread_ready = false;
	while (++i < arg->num_philo)
	{
		arg->forks[i].fork_id = i;
		arg->philos[i].id = i + 1;
		arg->philos[i].meal_consumed = 0;
		arg->philos[i].is_full = false;
		arg->philos[i].arg = arg;
	}
	i = -1;
	while (++i < arg->num_philo)
		assign_forks(arg->num_philo, &arg->philos[i], arg->forks, i);
	return (0);
}
