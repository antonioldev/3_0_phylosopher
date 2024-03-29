/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:08:02 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/29 13:48:29 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (philo == NULL)
		return (printf("Memory Allocation Failed\n"), -1);
	if (ft_check_args(argc, argv, philo) == 0)
	{
		i = -1;
		philo->start = ft_get_time();
		while (++i < philo->num_philo)
		{
			philo->pid[i] = fork();
			if (philo->pid[i] == -1)
				return (printf("Fork Error\n"), 1);
			if (philo->pid[i] == 0)
			{
				philo->id = i + 1;
				ft_simulation(philo);
				ft_clean(philo);
				exit (0);
			}
		}
	}
	return (ft_clean(philo), 0);
}
