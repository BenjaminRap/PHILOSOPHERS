/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:46:06 by brappo            #+#    #+#             */
/*   Updated: 2024/03/25 10:51:32 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H
# include <semaphore.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <errno.h>
# define TO_DIE 0
# define TO_EAT 1
# define TO_SLEEP 2

typedef enum e_bool
{
	error = -1,
	false = 0,
	true = 1
}	t_bool;

typedef struct s_dinner
{
	int				philo_count;
	int				eat_number;
	int				times[3];
	pid_t			*philosophers;
	struct timeval	start_time;
	struct timeval	last_meal;
	sem_t			*forks;
	sem_t			*last_meal_sem;
	sem_t			*print;
	sem_t			*stop;
	sem_t			*set_end;
	size_t			index;
	t_bool			end;
}	t_dinner;

void	*check_stop(void *arg);
t_bool	set_last_meal(t_dinner *dinner);
t_bool	philo_routine(t_dinner *dinner);
t_bool	get_arguments(char **argv, t_dinner *dinner);
int		ft_atoi_unsigned(char *str);
void	*ft_calloc(size_t nmemb, size_t size);
t_bool	fork_philosopher(t_dinner *dinner, size_t index);
t_bool	populate_philosophers(t_dinner *dinner);
size_t	get_timestamp(t_dinner *dinner);
t_bool	init(t_dinner *dinner, char **argv);
void	*check_starvation(void *arg);
size_t	get_time_diff(struct timeval *first, struct timeval *second);
t_bool	philo_sleep(t_dinner *dinner);
t_bool	philo_talk(t_dinner *dinner, char *str);
t_bool	philo_eat(t_dinner *dinner);
t_bool	wait_philosophers(t_dinner *dinner);
void	unlink_semaphores(void);
void	close_semaphores(t_dinner *dinner);
t_bool	is_end(t_dinner *dinner);
t_bool	end_simulation(t_dinner *dinner);
void	ft_sleep(size_t	microseconds);
#endif // !PHILOSOPHERS_BONUS_H