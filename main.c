/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:08:02 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/07 16:01:43 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static int	ft_check_args(int argc, char **argv, t_arg *arg)
{
	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	arg->num_philo = ft_atol(argv[1]);
	arg->time_to_die = ft_atol(argv[2]);
	arg->time_to_eat = ft_atol(argv[3]);
	arg->time_to_sleep = ft_atol(argv[4]);
	if (argc == 5)
		arg->times_dinner = -1;
	else
		arg->times_dinner = ft_atol(argv[5]);
	if (arg->num_philo <= 0 || arg->num_philo > 200
		|| arg->time_to_die <= 0 || arg->time_to_eat <= 0
		|| arg->time_to_sleep <= 0 || arg->times_dinner < -1)
	{
		printf("Arguments are invalid!\n");
		return (2);
	}
	if (arg->times_dinner == 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_arg	arg;

	if (ft_check_args(argc, argv, &arg) == 0)
	{
		ft_initiate(&arg);
		ft_simulation(&arg);
		ft_clean(&arg);
	}
	return (0);
}
