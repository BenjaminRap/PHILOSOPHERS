/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:29:59 by brappo            #+#    #+#             */
/*   Updated: 2024/03/20 11:13:20 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_mutex_data	*get_left_fork(t_philo *philo)
{
	size_t	index;

	index = philo->index;
	if (index == 0)
		index = philo->philo_count - 1;
	else
		index -= 1;
	return (&philo->philosophers[index]->fork);
}

t_bool	take_fork(t_mutex_data *fork)
{
	int	error;

	error = pthread_mutex_lock(&fork->mutex);
	if (error != 0)
		return (error);
	return (true);
}

void	put_forks_down(t_mutex_data *first_fork, t_mutex_data *second_fork)
{
	pthread_mutex_unlock(&first_fork->mutex);
	pthread_mutex_unlock(&second_fork->mutex);
}

t_bool	is_end(t_philo *philo)
{
	t_bool	end;

	if (lock_meal(philo) == false)
		return (error);
	if (philo->last_meal.value.tv_usec == -1)
		end = true;
	else
		end = false;
	unlock_meal(philo);
	return (end);
}

t_bool	set_end(t_philo *philo)
{
	if (lock_meal(philo) == false)
		return (error);
	philo->last_meal.value.tv_usec = -1;
	unlock_meal(philo);
	return (true);
}
