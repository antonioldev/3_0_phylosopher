/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:25:25 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/30 11:21:09 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*This function convert the string into a long int*/
long	ft_atol(const char *nptr)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (nptr[i] != '\0')
	{
		if (nptr[i] >= '0' && nptr[i] <= '9')
		{
			result *= 10;
			result += (nptr[i] - '0');
		}
		else
			return (-2);
		i++;
	}
	if (result > INT_MAX)
		return (-2);
	return (result);
}

void	is_philo_dead(t_philo *philo)
{
	long long	time_elapsed;
	long long	time;

	time = ft_get_time();
	time_elapsed = time - philo->last_meal;
	if (time_elapsed >= philo->time_to_die)
	{
		sem_wait(philo->print);
		printf("%lli %3i %s\n", time, philo->id, "died");
		ft_clean(philo);
		exit (1);
	}
}

/*This function get the time and convert into milliseconds*/
long long	ft_get_time(void)
{
	long long		time;
	struct timeval	current_time;

	time = 0;
	gettimeofday(&current_time, NULL);
	time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time);
}

/*This function destroys all mutex and free memory allocated by malloc*/
void	ft_clean(t_philo *philo)
{
	int	i;
	int	status;

	while (waitpid(-1, &status, 0) > 0)
	{
		if (status != 0)
		{
			i = -1;
			while (++i < philo->num_philo)
				kill(philo->pid[i], SIGKILL);
			break ;
		}
	}
	sem_close(philo->print);
	sem_close(philo->fork);
	sem_unlink ("/sem_printf");
	sem_unlink ("/sem_fork");
	if (philo->pid)
		free(philo->pid);
	free(philo);
}
