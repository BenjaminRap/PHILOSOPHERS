/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_meal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:43:47 by root              #+#    #+#             */
/*   Updated: 2024/03/20 11:35:42 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	lock_meal(t_philo *philo)
{
	int	error;

	error = pthread_mutex_lock(&philo->last_meal.mutex);
	if (error != 0)
		return (error);
	return (true);
}

void	unlock_meal(t_philo *philo)
{
	pthread_mutex_unlock(&philo->last_meal.mutex);
}

t_bool	set_last_meal(t_philo *philo)
{
	struct timeval	actual_time;

	if (lock_meal(philo) == false)
		return (error);
	if (gettimeofday(&actual_time, NULL) == -1)
		return (unlock_meal(philo), error);
	philo->last_meal.value = actual_time;
	unlock_meal(philo);
	return (true);
}
