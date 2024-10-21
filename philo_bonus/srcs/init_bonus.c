/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:19:32 by brappo            #+#    #+#             */
/*   Updated: 2024/03/25 11:16:17 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

t_bool	get_arguments(char **argv, t_dinner *dinner)
{
	size_t	index;

	index = 0;
	dinner->philo_count = ft_atoi_unsigned(argv[1]);
	if (dinner->philo_count == -1 || !dinner->philo_count)
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

t_bool	create_semaphores(t_dinner *dinner)
{
	dinner->last_meal_sem = sem_open("last_meal", O_CREAT, 0644, 1);
	dinner->print = sem_open("print", O_CREAT, 0644, 1);
	dinner->forks = sem_open("forks", O_CREAT, 0644, dinner->philo_count / 2);
	dinner->stop = sem_open("stop", O_CREAT, 0644, 0);
	dinner->set_end = sem_open("end", O_CREAT, 0644, 1);
	if (dinner->last_meal_sem == SEM_FAILED
		|| dinner->print == SEM_FAILED
		|| dinner->forks == SEM_FAILED
		|| dinner->stop == SEM_FAILED
		|| dinner->set_end == SEM_FAILED)
		return (close_semaphores(dinner), false);
	return (true);
}

t_bool	init(t_dinner *dinner, char **argv)
{
	if (get_arguments(argv, dinner) == false)
		return (printf("wrong arguments"), false);
	if (gettimeofday(&dinner->start_time, NULL) == -1)
		return (printf("main process error"), false);
	unlink_semaphores();
	if (create_semaphores(dinner) == false)
		return (printf("main process error"), false);
	dinner->last_meal = dinner->start_time;
	dinner->end = false;
	return (true);
}

t_bool	populate_philosophers(t_dinner *dinner)
{
	size_t	index;

	index = 0;
	dinner->philosophers = (pid_t *)ft_calloc(dinner->philo_count + 1,
			sizeof(pid_t));
	if (dinner->philosophers == NULL)
		return (error);
	while (index < (size_t)dinner->philo_count)
	{
		if (fork_philosopher(dinner, index) == error)
			return (error);
		index++;
	}
	return (true);
}
