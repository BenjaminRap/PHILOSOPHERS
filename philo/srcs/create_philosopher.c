/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philosopher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:12:57 by brappo            #+#    #+#             */
/*   Updated: 2024/03/20 11:15:51 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	copy_dinner(t_philo *philo, t_dinner *dinner)
{
	philo->last_meal.value = dinner->start_time;
	philo->philosophers = dinner->philosophers;
	philo->times = dinner->times;
	philo->philo_count = dinner->philo_number;
	philo->print_mutex = &dinner->print_mutex;
	philo->eat_number = dinner->eat_number;
	philo->start_time = &dinner->start_time;
}

t_philo	*create_philosopher(size_t index, t_dinner *dinner)
{
	t_philo			*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	if (pthread_mutex_init(&philo->fork.mutex, NULL))
		return (free(philo), NULL);
	if (pthread_mutex_init(&philo->last_meal.mutex, NULL))
	{
		pthread_mutex_destroy(&philo->last_meal.mutex);
		return (free(philo), NULL);
	}
	copy_dinner(philo, dinner);
	philo->index = index;
	return (philo);
}
