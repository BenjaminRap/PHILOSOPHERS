/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:47:32 by brappo            #+#    #+#             */
/*   Updated: 2024/03/24 20:45:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_dinner	dinner;
	t_bool		return_main;
	t_bool		return_process;

	if (argc < 5 || argc > 6)
		return (printf("wrong arguments number"), 1);
	if (init(&dinner, argv) == false)
		return (false);
	return_main = populate_philosophers(&dinner);
	return_process = wait_philosophers(&dinner);
	close_semaphores(&dinner);
	unlink_semaphores();
	if (return_main == error)
		return (printf("main process error"), 1);
	if (return_process == error)
		return (printf("child process error"), 1);
	return (0);
}
