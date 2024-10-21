/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:18:37 by brappo            #+#    #+#             */
/*   Updated: 2024/03/20 15:39:50 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	get_arguments(char **argv, t_dinner *dinner)
{
	size_t	index;

	index = 0;
	dinner->philo_number = ft_atoi_unsigned(argv[1]);
	if (dinner->philo_number == -1 || !dinner->philo_number)
		return (false);
	while (index < 3)
	{
		dinner->times[index] = ft_atoi_unsigned(argv[index + 2]);
		if (dinner->times[index] == -1)
			return (false);
		index++;
	}
	if (argv[5] != NULL)
	{
		dinner->eat_number = ft_atoi_unsigned(argv[5]);
		if (dinner->eat_number == -1)
			return (false);
	}
	else
		dinner->eat_number = -1;
	return (true);
}

t_bool	populate_philosophers(t_dinner *dinner)
{
	size_t	index;

	index = 0;
	while (index < (size_t)dinner->philo_number)
	{
		dinner->philosophers[index] = create_philosopher(index, dinner);
		if (dinner->philosophers[index] == NULL)
			return (false);
		index++;
	}
	return (true);
}

t_bool	start_threads(t_dinner *dinner)
{
	size_t		index;

	index = 0;
	while (index < (size_t)dinner->philo_number)
	{
		if (pthread_create(&(dinner->philosophers[index]->thread), NULL,
				philo_loop, (void *)dinner->philosophers[index]) != 0)
		{
			stop_philosophers(dinner->philosophers);
			wait_thread(dinner, index);
			return (false);
		}
		index++;
	}
	return (true);
}

t_bool	start_dinner(t_dinner *dinner)
{
	dinner->philosophers = (t_philo **)ft_calloc(dinner->philo_number + 1,
			sizeof(t_philo *));
	if (dinner->philosophers == NULL)
		return (false);
	if (populate_philosophers(dinner) == false)
		return (false);
	if (start_threads(dinner) == false)
		return (false);
	if (pthread_create(&dinner->starvation_thrtead, NULL,
			check_starvation, (void *)dinner) != 0)
		return (stop_philosophers(dinner->philosophers), false);
	return (true);
}
