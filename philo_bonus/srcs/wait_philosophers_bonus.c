/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_philosophers_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:00:29 by marvin            #+#    #+#             */
/*   Updated: 2024/03/24 20:00:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

t_bool	wait_philosophers(t_dinner *dinner)
{
	size_t	index;
	int		status;

	index = 0;
	status = 0;
	while (dinner->philosophers[index] != 0)
	{
		if (status == 0)
			waitpid(dinner->philosophers[index], &status, 0);
		else
			waitpid(dinner->philosophers[index], NULL, 0);
		index++;
	}
	if (dinner->philosophers != NULL)
		free(dinner->philosophers);
	if (status == 1)
		return (false);
	return (true);
}

void	unlink_semaphores(void)
{
	sem_unlink("stop");
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("last_meal");
	sem_unlink("end");
}

void	close_semaphores(t_dinner *dinner)
{
	if (dinner->print != SEM_FAILED)
		sem_close(dinner->print);
	if (dinner->forks != SEM_FAILED)
		sem_close(dinner->forks);
	if (dinner->last_meal_sem != SEM_FAILED)
		sem_close(dinner->last_meal_sem);
	if (dinner->stop != SEM_FAILED)
		sem_close(dinner->stop);
	if (dinner->set_end != SEM_FAILED)
		sem_close(dinner->set_end);
}
