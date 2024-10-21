/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:23:25 by marvin            #+#    #+#             */
/*   Updated: 2024/03/24 19:23:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

t_bool	philo_talk(t_dinner *dinner, char *str)
{
	size_t	timestamp;
	t_bool	error;

	if (sem_wait(dinner->print) == -1)
		return (false);
	timestamp = get_timestamp(dinner);
	if (timestamp == 0)
		return (false);
	if (is_end(dinner) == true)
		return (sem_post(dinner->print), false);
	error = printf("%ld %ld %s\n", timestamp, dinner->index + 1, str);
	sem_post(dinner->print);
	if (error == EOF)
		return (false);
	return (true);
}

t_bool	philo_eat(t_dinner *dinner)
{
	if (sem_wait(dinner->forks) == -1)
		return (false);
	if (philo_talk(dinner, "is eating") == false)
		return (sem_post(dinner->forks), false);
	set_last_meal(dinner);
	ft_sleep(dinner->times[TO_EAT] * 1000);
	sem_post(dinner->forks);
	usleep(50);
	return (true);
}

t_bool	philo_sleep(t_dinner *dinner)
{
	if (philo_talk(dinner, "is sleeping") == false)
		return (false);
	ft_sleep(dinner->times[TO_SLEEP] * 1000);
	return (true);
}
