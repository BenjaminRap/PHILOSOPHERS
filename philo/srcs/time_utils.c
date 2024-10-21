/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:45:27 by root              #+#    #+#             */
/*   Updated: 2024/03/25 11:18:26 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_time_diff(struct timeval *first, struct timeval *second)
{
	size_t			seconds;
	int				microseconds;
	size_t			timestamp;

	seconds = second->tv_sec - first->tv_sec;
	microseconds = second->tv_usec - first->tv_usec;
	timestamp = seconds * 1000 + microseconds / 1000;
	return (timestamp);
}

size_t	get_timestamp(t_philo *philo)
{
	size_t			seconds;
	int				microseconds;
	size_t			timestamp;
	struct timeval	actual_time;

	if (gettimeofday(&actual_time, NULL) == -1)
		return (0);
	seconds = actual_time.tv_sec - philo->start_time->tv_sec;
	microseconds = actual_time.tv_usec - philo->start_time->tv_usec;
	timestamp = seconds * 1000 + microseconds / 1000;
	if (timestamp == 0)
		return (1);
	return (timestamp);
}

void	ft_sleep(size_t	microseconds)
{
	size_t	index;

	index = 0;
	while (index < microseconds / 1000000)
	{
		usleep(1000000);
		index++;
	}
	usleep(microseconds % 1000000);
}
