/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:25:25 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/27 09:22:47 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
void	ft_clean(t_philo *philo)
{
	int	i;
	int	status;

	i = 0;
	while (i < philo->num_philo)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < philo->num_philo)
				kill(philo->pid[i], SIGKILL);
			break ;
		}
		i++;
	}
	sem_close(philo->print);
	sem_close(philo->fork);
	sem_unlink ("/sem_printf");
	sem_unlink ("/sem_fork");
	free(philo->pid);
	free(philo);
}
