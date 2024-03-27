/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:08:02 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/27 09:18:14 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*This function convert the string into a long int*/
static long	ft_atol(const char *nptr)
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

/*This function calculate the thinking time, based on the arguments passed*/
static long	ft_decide_thinking_time(t_philo *philo)
{
	long	time;

	if (philo->time_to_die >= 2 * (philo->time_to_eat + philo->time_to_sleep)
		|| philo->time_to_eat == philo->time_to_sleep)
		time = philo->time_to_die - philo->time_to_eat - philo->time_to_sleep - 50;
	else
		time = philo->time_to_eat - philo->time_to_sleep;
	if (time < 0)
		time *= -1;
	return (time);
}

/*This function check if arguments pased are valid*/
static int	ft_check_args(int argc, char **argv, t_philo *philo)
{
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
				philo->last_meal = ft_get_time();
				ft_simulation(philo);
			}
		}
		// 	ft_simulation(&arg);
		// 	ft_clean(&arg);
	}
	ft_clean(philo);
	return (0);
}
