/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 09:44:40 by brappo            #+#    #+#             */
/*   Updated: 2024/03/25 10:50:05 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

t_bool	end_simulation(t_dinner *dinner)
{
	if (sem_wait(dinner->set_end) == -1)
		return (false);
	dinner->end = true;
	sem_post(dinner->set_end);
	return (true);
}

t_bool	philo_routine_alone(t_dinner *dinner)
{
	if (philo_talk(dinner, "is thinking") == false)
		return (false);
	ft_sleep(dinner->times[TO_DIE] * 1000);
	return (true);
}

t_bool	is_end(t_dinner *dinner)
{
	t_bool	end;

	sem_wait(dinner->set_end);
	end = dinner->end;
	sem_post(dinner->set_end);
	return (end);
}

t_bool	philo_routine(t_dinner *dinner)
{
	size_t	meal_count;

	meal_count = 0;
	if (dinner->philo_count == 1)
		return (philo_routine_alone(dinner));
	if (dinner->index % 2 == 1)
		ft_sleep(dinner->times[TO_EAT] * 500);
	while (meal_count != (size_t)dinner->eat_number)
	{
		if (philo_talk(dinner, "is thinking") == false)
			return (false);
		if (philo_eat(dinner) == false)
			return (false);
		if (philo_sleep(dinner) == false)
			return (false);
		meal_count++;
	}
	if (end_simulation(dinner) == false)
		return (false);
	return (true);
}
