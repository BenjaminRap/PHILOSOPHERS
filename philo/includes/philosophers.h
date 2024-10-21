/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 08:13:52 by brappo            #+#    #+#             */
/*   Updated: 2024/03/25 11:21:48 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <errno.h>
# include <sys/time.h>
# define TO_DIE 0
# define TO_EAT 1
# define TO_SLEEP 2

typedef enum e_bool
{
	error = -1,
	false = 0,
	true = 1
}	t_bool;

typedef struct s_mutex_data
{
	struct timeval	value;
	pthread_mutex_t	mutex;
}	t_mutex_data;

typedef struct s_philo
{
	t_mutex_data	fork;
	t_mutex_data	*print_mutex;
	t_mutex_data	last_meal;
	pthread_t		thread;
	size_t			index;
	int				*times;
	struct s_philo	**philosophers;
	size_t			philo_count;
	int				eat_number;
	struct timeval	*start_time;
}	t_philo;

typedef struct s_dinner
{
	int				times[3];
	int				philo_number;
	int				eat_number;
	t_philo			**philosophers;
	t_mutex_data	print_mutex;
	struct timeval	start_time;
	pthread_t		starvation_thrtead;
}	t_dinner;

int				ft_atoi_unsigned(char *str);
t_bool			get_arguments(char **argv, t_dinner *dinner);
void			*philo_loop(void *arg);
t_bool			start_dinner(t_dinner *dinner);
t_philo			*create_philosopher(size_t index, t_dinner *dinner);
void			free_array(void ***array);
void			*ft_calloc(size_t nmemb, size_t size);
t_mutex_data	*get_left_fork(t_philo *philo);
t_bool			take_fork(t_mutex_data *fork);
void			put_forks_down(t_mutex_data *first_fork,
					t_mutex_data *second_fork);
t_bool			print_sync(t_philo *philo, char *str, t_bool check_end);
void			swap_pointers(void ***a, void ***b);
size_t			get_timestamp(t_philo *philo);
t_bool			set_last_meal(t_philo *philo);
size_t			get_time_diff(struct timeval *first, struct timeval *second);
t_bool			check_philosophers(t_dinner *dinner,
					struct timeval *actual_time);
void			*check_starvation(void *arg);
void			unlock_meal(t_philo *philo);
t_bool			lock_meal(t_philo *philo);
t_bool			is_end(t_philo *philo);
t_bool			set_end(t_philo *philo);
t_bool			stop_philosophers(t_philo **philosophers);
t_bool			wait_thread(t_dinner *dinner, size_t thread_count);
void			ft_sleep(size_t	microseconds);
t_bool			philo_sleep(t_philo *philo);
t_bool			philo_eat(t_philo *philo);
#endif // !PHILOSOPHERS_H