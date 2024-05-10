/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:40:27 by pfontenl          #+#    #+#             */
/*   Updated: 2024/04/27 17:18:23 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef unsigned long long int	t_millis;
typedef pthread_mutex_t			t_mutex;
typedef t_mutex					t_fork;

# define ERR_MSG_PHILO "Error: Invalid amount of philosophers (Maximum: 200)."
# define ERR_MSG_STARVE "Error: Invalid starve time (Minimum: 60)."
# define ERR_MSG_EAT "Error: Invalid eat time (Minimum: 60)."
# define ERR_MSG_SLEEP "Error: Invalid sleep time (Minimum: 60)."
# define ERR_MSG_MEAL "Error: Invalid meal goal."

# define MSLEEP_TIME 250
# define ALONE_PHILO_SLEEP 500
# define SIM_SLEEP 500

# define COLOR_NONE "\033[0;0m"
# define COLOR_RED "\033[1;31m"
# define COLOR_GREEN "\033[1;32m"
# define COLOR_YELLOW "\033[1;33m"
# define COLOR_PINK "\033[1;35m"
# define COLOR_CYAN "\033[1;36m"

enum							e_status
{
	Think,
	Eat,
	Sleep,
	Fork,
	Death
};

typedef struct s_philo
{
	pthread_t					thread;
	int							run_thread;
	int							thread_stopped;
	size_t						n;
	ssize_t						start_delay;
	int							extra_delay;
	t_fork						*forks[2];
	t_millis					last_meal;
	size_t						eaten_meals;
	t_millis					start_ms;
	t_millis					eat_time;
	t_millis					sleep_time;
	t_mutex						philo_lock;
	t_mutex						*print_lock;
	int							err_flag;
	t_mutex						*death_lock;
	int							*death_flag;
}								t_philo;

typedef struct s_data
{
	t_millis					start_ms;
	size_t						amount;
	t_fork						*forks;
	t_philo						*philo;
	pthread_t					sim_thread;
	t_millis					eat_time;
	t_millis					sleep_time;
	t_millis					starve_time;
	size_t						meal_goal;
	t_mutex						print_lock;
	int							err_flag;
	t_mutex						death_lock;
	int							death_flag;
}								t_data;

// time_utils.c
t_millis						calc_time(t_millis offset);
void							ft_msleep(t_millis time);

// fork_utils.c
int								create_forks(t_data *data);
int								grab_forks(t_philo *philo);
int								release_forks(t_philo *philo);
void							destroy_forks(t_data *data);

// mutex_utils.c
int								init_mutex(t_mutex *mutex, int *err);
int								lock_mutex(t_mutex *mutex, int *err);
int								unlock_mutex(t_mutex *mutex, int *err);
int								destroy_mutex(t_mutex *mutex, int *err);

// sim_init.c
int								init_simulation(t_data *data);

// philo_init.c
int								init_philos(t_data *data);

// philo_thread.c
void							*philo_main(void *ptr);
int								sim_running(t_philo *philo);

// status_log.c
int								print_status(t_philo *philo,
									enum e_status status);

// sim_utils.c
int								run_sim(t_data *data);

// parse_utils.c
int								parse_sim_data(int argn, char **args,
									t_data *data);

// sim_thread.c
void							*thread_main(void *raw_data);

#endif