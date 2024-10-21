/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:18:57 by brappo            #+#    #+#             */
/*   Updated: 2024/03/25 11:20:26 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	print_sync(t_philo *philo, char *str, t_bool check_end)
{
	int		error;
	size_t	timestamp;

	error = pthread_mutex_lock(&philo->print_mutex->mutex);
	if (error != 0)
		return (error);
	timestamp = get_timestamp(philo);
	if (check_end == true && is_end(philo) == true)
		return (pthread_mutex_unlock(&philo->print_mutex->mutex), false);
	if (timestamp == 0)
		return (pthread_mutex_unlock(&philo->print_mutex->mutex), error);
	error = printf("%ld %ld %s\n", timestamp, philo->index + 1, str);
	pthread_mutex_unlock(&philo->print_mutex->mutex);
	if (error == EOF)
		return (error);
	return (true);
}

t_bool	philo_eat(t_philo *philo)
{
	t_mutex_data	*first_fork;
	t_mutex_data	*second_fork;
	t_bool			return_value;

	first_fork = &philo->fork;
	second_fork = get_left_fork(philo);
	if (philo->index % 2)
		swap_pointers((void ***)&first_fork, (void ***)&second_fork);
	if (take_fork(first_fork) == error)
		return (error);
	if (take_fork(second_fork) == error)
		return (pthread_mutex_unlock(&first_fork->mutex), error);
	return_value = print_sync(philo, "is eating", true);
	if (return_value == false || return_value == error)
		return (put_forks_down(first_fork, second_fork), return_value);
	if (set_last_meal(philo) == error)
		return (put_forks_down(first_fork, second_fork), error);
	usleep(philo->times[TO_EAT] * 1000);
	put_forks_down(first_fork, second_fork);
	return (true);
}

t_bool	philo_sleep(t_philo *philo)
{
	t_bool	return_result;

	return_result = print_sync(philo, "is sleeping", true);
	if (return_result == false || return_result == error)
		return (return_result);
	ft_sleep(philo->times[TO_SLEEP] * 1000);
	return (true);
}
