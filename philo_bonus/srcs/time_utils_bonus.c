/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:45:27 by root              #+#    #+#             */
/*   Updated: 2024/03/25 11:22:46 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

size_t	get_time_diff(struct timeval *first, struct timeval *second)
{
	size_t			seconds;
	int				microseconds;
	size_t			diff;

	seconds = second->tv_sec - first->tv_sec;
	if (seconds == 0 && first->tv_usec > second->tv_usec)
		return (0);
	microseconds = second->tv_usec - first->tv_usec;
	diff = seconds * 1000 + microseconds / 1000;
	return (diff);
}

size_t	get_timestamp(t_dinner *dinner)
{
	size_t			seconds;
	int				microseconds;
	size_t			timestamp;
	struct timeval	actual_time;

	if (gettimeofday(&actual_time, NULL) == -1)
		return (0);
	seconds = actual_time.tv_sec - dinner->start_time.tv_sec;
	microseconds = actual_time.tv_usec - dinner->start_time.tv_usec;
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
