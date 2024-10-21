/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:47:06 by brappo            #+#    #+#             */
/*   Updated: 2024/03/25 11:25:04 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	philo_routine(t_philo *philo)
{
	t_bool	return_value;

	return_value = print_sync(philo, "is thinking", true);
	if (return_value != true)
		return (return_value);
	return_value = philo_eat(philo);
	if (return_value != true)
		return (return_value);
	return_value = philo_sleep(philo);
	if (return_value != true)
		return (return_value);
	if (philo->philo_count % 2 == 1
		&& philo->times[TO_EAT] > philo->times[TO_SLEEP] / 2)
		ft_sleep((philo->times[TO_EAT] * 2 - philo->times[TO_SLEEP]) * 1000);
	return (true);
}

t_bool	philo_alone(t_philo *philo)
{
	if (print_sync(philo, "is thinking", false) == error)
		return (error);
	ft_sleep(philo->times[TO_DIE] * 1000);
	return (true);
}

void	*philo_loop(void *arg)
{
	t_philo	*philo;
	int		meal_count;
	t_bool	return_value;

	meal_count = 0;
	philo = (t_philo *)arg;
	if (philo->philo_count == 1)
		return ((void *)philo_alone(philo));
	if (philo->index % 2 == 1)
		ft_sleep(philo->times[TO_EAT] * 500);
	while (meal_count != philo->eat_number)
	{
		return_value = philo_routine(philo);
		if (return_value == false || return_value == error)
			return ((void *)return_value);
		meal_count++;
	}
	if (set_end(philo) == error)
		return ((void *)error);
	return ((void *)true);
}
