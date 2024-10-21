/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_starvation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:17:24 by root              #+#    #+#             */
/*   Updated: 2024/03/25 10:30:34 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

t_bool	stop(t_dinner *dinner, struct timeval actual_time)
{
	size_t	timestamp;
	int		error;

	timestamp = get_time_diff(&dinner->start_time, &actual_time);
	error = false;
	if (sem_wait(dinner->print) == -1)
		return (false);
	if (is_end(dinner) == false)
	{
		end_simulation(dinner);
		sem_post(dinner->stop);
		error = printf("%ld %ld died\n", timestamp, dinner->index + 1);
		usleep(5000);
	}
	else
		sem_post(dinner->stop);
	sem_post(dinner->print);
	sem_post(dinner->last_meal_sem);
	if (error == EOF)
		return (false);
	return (true);
}

void	*check_starvation(void *arg)
{
	struct timeval	actual_time;
	t_dinner		*dinner;

	dinner = (t_dinner *)arg;
	while (true)
	{
		if (gettimeofday(&actual_time, NULL) == -1)
			return ((void *)false);
		sem_wait(dinner->last_meal_sem);
		if (get_time_diff(&dinner->last_meal,
				&actual_time) > (size_t)dinner->times[TO_DIE])
		{
			if (stop(dinner, actual_time) == false)
				return ((void *)false);
			break ;
		}
		sem_post(dinner->last_meal_sem);
		usleep(50);
	}
	return ((void *)true);
}
