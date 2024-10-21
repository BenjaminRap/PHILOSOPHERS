/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_meal_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:43:47 by root              #+#    #+#             */
/*   Updated: 2024/03/22 15:32:09 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

t_bool	set_last_meal(t_dinner *dinner)
{
	struct timeval	actual_time;

	sem_wait(dinner->last_meal_sem);
	if (gettimeofday(&actual_time, NULL) == -1)
		return (sem_post(dinner->last_meal_sem), error);
	dinner->last_meal = actual_time;
	sem_post(dinner->last_meal_sem);
	return (true);
}
