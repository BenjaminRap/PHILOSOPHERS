/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_stop_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:00:07 by root              #+#    #+#             */
/*   Updated: 2024/03/25 10:28:37 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*check_stop(void *arg)
{
	t_dinner	*dinner;

	dinner = (t_dinner *)arg;
	if (sem_wait(dinner->stop) == -1)
		return ((void *)false);
	if (end_simulation(dinner) == false)
		return (sem_post(dinner->stop), (void *)false);
	sem_post(dinner->stop);
	return ((void *)true);
}
