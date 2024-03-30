/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:55:46 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/30 11:21:22 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*This function calculate the thinking time, based on the arguments passed*/
static long long	ft_decide_thinking_time(t_philo *philo)
{
	long long	time;

	if (philo->time_to_die >= 2 * (philo->time_to_eat + philo->time_to_sleep))
		time = philo->time_to_die - philo->time_to_eat
			- philo->time_to_sleep - 50;
	else
		time = philo->time_to_eat - philo->time_to_sleep;
	if (time < 0)
		time *= -1;
	return (time);
}

/*This function initiate variables and allocate memory for philos and forks*/
static int	ft_initiate(t_philo *philo)
{
	int	i;

	i = -1;
	philo->is_full = false;
	philo->meal_consumed = 0;
	philo->pid = (int *)malloc(sizeof(int) * philo->num_philo);
	if (philo->pid == NULL)
		return (printf("Memory Allocation Failed\n"), 1);
	sem_unlink ("/sem_printf");
	sem_unlink ("/sem_fork");
	philo->print = sem_open ("/sem_printf", O_CREAT, 0644, 1);
	philo->fork = sem_open ("/sem_fork", O_CREAT, 0644, philo->num_philo);
	if (philo->print <= 0 || philo->fork <= 0)
		return (printf("Semaphore Creation Failed\n"), 1);
	return (0);
}

/*This function check if philouments pased are valid*/
int	ft_check_args(int argc, char **argv, t_philo *philo)
{
	philo->pid = NULL;
	if (argc < 5 || argc > 6)
		return (printf("Wrong number of arguments\n"), 1);
	philo->num_philo = ft_atol(argv[1]);
	philo->time_to_die = ft_atol(argv[2]);
	philo->time_to_eat = ft_atol(argv[3]);
	philo->time_to_sleep = ft_atol(argv[4]);
	philo->time_to_think = ft_decide_thinking_time(philo);
	if (argc == 5)
		philo->times_dinner = -1;
	else
		philo->times_dinner = ft_atol(argv[5]);
	if (philo->num_philo <= 0 || philo->num_philo > 200
		|| philo->time_to_die <= 0 || philo->time_to_eat <= 0
		|| philo->time_to_sleep <= 0 || philo->times_dinner < -1)
		return (printf("Arguments are invalid!\n"), 2);
	if (philo->times_dinner == 0)
		return (1);
	if (ft_initiate(philo) != 0)
		return (1);
	return (0);
}
