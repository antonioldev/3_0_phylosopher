/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:55:46 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/27 16:58:14 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*This function initiate variables and allocate memory for philos and forks*/
int	ft_initiate(t_philo *philo)
{
	int	i;

	i = -1;
	
	philo->died = false;
	philo->stop = false;
	philo->is_full = false;
	philo->meal_consumed = 0;
	philo->pid = (int *)malloc(sizeof(int) * philo->num_philo);
	if (philo->pid == NULL)
		return (printf("Memory Allocation Failed\n"), 1);
	sem_unlink ("/sem_printf");
	sem_unlink ("/sem_fork");
	sem_unlink ("/sem_time");
	philo->time = sem_open ("/sem_time", O_CREAT, 0644, 1);
	philo->print = sem_open ("/sem_printf", O_CREAT, 0644, 1);
	philo->fork = sem_open ("/sem_fork", O_CREAT, 0644, philo->num_philo);
	if (philo->print <= 0 || philo->fork <= 0)
		return (printf("Semaphore Creation Failed\n"), 1);
	return (0);
}
