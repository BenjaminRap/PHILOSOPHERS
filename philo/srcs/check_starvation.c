/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_starvation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:17:24 by root              #+#    #+#             */
/*   Updated: 2024/03/25 11:09:34 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	stop_philosophers(t_philo **philosophers)
{
	size_t	index;
	t_bool	result;

	index = 0;
	result = true;
	if (pthread_mutex_lock(&(*philosophers)->print_mutex->mutex) == -1)
		return (error);
	while (philosophers[index] != NULL)
	{
		if (lock_meal(philosophers[index]) == error)
		{
			result = error;
			index++;
			continue ;
		}
		philosophers[index]->last_meal.value.tv_usec = -1;
		unlock_meal(philosophers[index]);
		index++;
	}
	if (pthread_mutex_unlock(&(*philosophers)->print_mutex->mutex) == -1)
		return (false);
	return (result);
}

t_bool	has_finished(t_philo *philo, size_t *philo_finished)
{
	if (philo->last_meal.value.tv_usec == -1)
	{
		*philo_finished += 1;
		return (true);
	}
	return (false);
}

t_bool	has_eaten(t_philo *philo, t_dinner *dinner, struct timeval *actual_time)
{
	size_t	starving_time;

	starving_time = get_time_diff(&philo->last_meal.value, actual_time);
	if (starving_time >= (size_t)philo->times[TO_DIE])
	{
		unlock_meal(philo);
		if (stop_philosophers(dinner->philosophers) == error
			|| print_sync(philo, "died", false) == error)
			return (error);
		return (false);
	}
	return (true);
}

t_bool	check_philosophers(t_dinner *dinner, struct timeval *actual_time)
{
	size_t	index;
	t_philo	*philo;
	t_bool	alive;
	size_t	philo_finished;	

	index = 0;
	philo_finished = 0;
	while (dinner->philosophers[index] != NULL)
	{
		philo = dinner->philosophers[index];
		if (lock_meal(philo) == error)
			return (error);
		if (has_finished(philo, &philo_finished) == false)
		{
			alive = has_eaten(philo, dinner, actual_time);
			if (alive != true)
				return (alive);
		}
		unlock_meal(philo);
		index++;
	}
	if (philo_finished == (size_t)dinner->philo_number)
		return (false);
	return (true);
}

void	*check_starvation(void *arg)
{
	struct timeval	actual_time;
	t_dinner		*dinner;
	t_bool			result_value;

	dinner = (t_dinner *)arg;
	while (true)
	{
		if (gettimeofday(&actual_time, NULL) == -1)
			return ((void *)error);
		result_value = check_philosophers(dinner, &actual_time);
		if (result_value == error)
			return ((void *)error);
		else if (result_value == false)
			break ;
		usleep(500);
	}
	return ((void *)true);
}
