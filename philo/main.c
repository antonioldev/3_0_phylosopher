/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:08:02 by alimotta          #+#    #+#             */
/*   Updated: 2024/04/02 12:48:00 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
static long	ft_decide_thinking_time(t_arg *arg)
{
	long	time;

	if (arg->time_to_die >= 2 * (arg->time_to_eat + arg->time_to_sleep))
		time = arg->time_to_die - arg->time_to_eat - arg->time_to_sleep - 50;
	else
		time = arg->time_to_eat - arg->time_to_sleep;
	if (time < 0)
		time *= -1;
	return (time);
}

/*This function check if arguments pased are valid*/
static int	ft_check_args(int argc, char **argv, t_arg *arg)
{
	if (argc < 5 || argc > 6)
		return (printf("Wrong number of arguments\n"), 1);
	arg->num_philo = ft_atol(argv[1]);
	arg->time_to_die = ft_atol(argv[2]);
	arg->time_to_eat = ft_atol(argv[3]);
	arg->time_to_sleep = ft_atol(argv[4]);
	arg->time_to_think = ft_decide_thinking_time(arg);
	if (argc == 5)
		arg->times_dinner = -1;
	else
		arg->times_dinner = ft_atol(argv[5]);
	if (arg->num_philo <= 0 || arg->num_philo > 200
		|| arg->time_to_die <= 0 || arg->time_to_eat <= 0
		|| arg->time_to_sleep <= 0 || arg->times_dinner < -1)
		return (printf("Arguments are invalid!\n"), 2);
	if (arg->times_dinner == 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_arg	arg;

	if (ft_check_args(argc, argv, &arg) == 0)
	{
		if (ft_initiate(&arg) == 0)
		{
			ft_simulation(&arg);
			ft_clean(&arg);
		}
	}
	return (0);
}
