/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 08:13:09 by brappo            #+#    #+#             */
/*   Updated: 2024/03/25 10:18:48 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	wait_thread(t_dinner *dinner, size_t thread_count)
{
	size_t	index;
	void	*return_result;

	index = 0;
	return_result = (void *)true;
	while (index < thread_count)
	{
		if (return_result == (void *)error)
			pthread_join(dinner->philosophers[index]->thread, NULL);
		else
			pthread_join(dinner->philosophers[index]->thread, &return_result);
		index++;
	}
	if (return_result == (void *)error)
		return (error);
	return (true);
}

void	free_dinner(t_dinner *dinner)
{
	size_t	index;
	t_philo	**philos;

	index = 0;
	philos = dinner->philosophers;
	while (philos[index] != NULL)
	{
		pthread_mutex_destroy(&philos[index]->fork.mutex);
		pthread_mutex_destroy(&philos[index]->last_meal.mutex);
		free(philos[index]);
		index++;
	}
	if (philos != NULL)
		free(philos);
	pthread_mutex_destroy(&dinner->print_mutex.mutex);
}

int	main(int argc, char **argv)
{
	t_dinner	dinner;
	t_bool		return_result;

	if (argc < 5 || argc > 6)
		return (printf("wrong arguments number"), 1);
	if (gettimeofday(&dinner.start_time, NULL) == -1)
		return (1);
	if (get_arguments(argv, &dinner) == false)
		return (printf("wrong arguments"), 1);
	if (pthread_mutex_init(&dinner.print_mutex.mutex, NULL))
		return (printf("internal error : main program"), 1);
	if (start_dinner(&dinner) == false)
	{
		printf("internal error : main program");
		return (free_dinner(&dinner), 1);
	}
	return_result = wait_thread(&dinner, dinner.philo_number);
	pthread_join(dinner.starvation_thrtead, NULL);
	free_dinner(&dinner);
	if (return_result == error)
		return (printf("internal error : thread"), 1);
	return (0);
}
