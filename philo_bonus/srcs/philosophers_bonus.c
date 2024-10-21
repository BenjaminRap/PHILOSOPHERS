/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:29:10 by brappo            #+#    #+#             */
/*   Updated: 2024/03/24 22:25:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	close_process(t_dinner *dinner)
{
	close_semaphores(dinner);
	free(dinner->philosophers);
}

t_bool	start_threads(t_dinner *dinner, pthread_t *check_starve,
		pthread_t *check_end)
{
	if (pthread_create(check_end, NULL, check_stop, dinner) != 0)
	{
		sem_post(dinner->stop);
		close_process(dinner);
		return (false);
	}
	if (pthread_create(check_starve, NULL, check_starvation, dinner) != 0)
	{
		sem_post(dinner->stop);
		pthread_join(*check_end, NULL);
		close_process(dinner);
		return (false);
	}
	return (true);
}

t_bool	wait_threads(pthread_t check_end, pthread_t check_starve)
{
	void	*result_check_starve;
	void	*result_check_end;

	pthread_join(check_starve, &result_check_starve);
	pthread_join(check_end, &result_check_end);
	if (result_check_end == (void *)false)
		return (false);
	if (result_check_starve == (void *)false)
		return (false);
	return (true);
}

void	start_philosopher(t_dinner *dinner)
{
	t_bool		result_routine;
	t_bool		result_threads;
	pthread_t	check_starve;
	pthread_t	check_end;

	if (start_threads(dinner, &check_starve, &check_end) == false)
		exit(1);
	result_routine = philo_routine(dinner);
	result_threads = wait_threads(check_end, check_starve);
	close_process(dinner);
	if (result_routine == false || result_threads == false)
		exit(1);
	exit(0);
}

t_bool	fork_philosopher(t_dinner *dinner, size_t index)
{
	pid_t		pid;

	pid = fork();
	if (pid == -1)
		return (error);
	if (pid == 0)
	{
		dinner->index = index;
		start_philosopher(dinner);
	}
	else
		dinner->philosophers[index] = pid;
	return (true);
}
