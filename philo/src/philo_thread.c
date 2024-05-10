/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:52:22 by pfontenl          #+#    #+#             */
/*   Updated: 2024/02/26 12:28:55 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_loop(t_philo *philo);
static int	philo_alone(t_philo *philo);
static int	set_status(t_philo *philo, enum e_status status);

void	*philo_main(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->forks[0] == philo->forks[1])
		philo_alone(philo);
	else
		while (sim_running(philo) && !philo->err_flag)
			philo_loop(philo);
	if (lock_mutex(&philo->philo_lock, &philo->err_flag))
		return ((void *)1);
	philo->thread_stopped = 1;
	if (unlock_mutex(&philo->philo_lock, &philo->err_flag))
		return ((void *)1);
	if (philo->err_flag)
		return ((void *)1);
	return ((void *)0);
}

int	sim_running(t_philo *philo)
{
	int	out;

	if (lock_mutex(&philo->philo_lock, &philo->err_flag))
		return (0);
	out = philo->run_thread;
	if (unlock_mutex(&philo->philo_lock, &philo->err_flag))
		return (0);
	return (out);
}

static int	philo_loop(t_philo *philo)
{
	if (set_status(philo, Think))
		return (1);
	if (philo->start_delay)
		ft_msleep(philo->start_delay * philo->eat_time);
	philo->start_delay = philo->extra_delay;
	if (grab_forks(philo))
		return (1);
	if (set_status(philo, Eat))
		return (release_forks(philo), 1);
	if (lock_mutex(&philo->philo_lock, &philo->err_flag))
		return (release_forks(philo), 1);
	if (philo->run_thread)
	{
		philo->last_meal = calc_time(philo->start_ms);
		philo->eaten_meals++;
	}
	if (unlock_mutex(&philo->philo_lock, &philo->err_flag))
		return (release_forks(philo), 1);
	if (release_forks(philo))
		return (1);
	return (set_status(philo, Sleep));
}

static int	philo_alone(t_philo *philo)
{
	if (set_status(philo, Think))
		return (1);
	if (lock_mutex(philo->forks[0], &philo->err_flag))
		return (1);
	if (set_status(philo, Fork))
		return (1);
	while (sim_running(philo))
		usleep(ALONE_PHILO_SLEEP);
	return (unlock_mutex(philo->forks[0], &philo->err_flag));
}

static int	set_status(t_philo *philo, enum e_status status)
{
	if (!sim_running(philo))
		return (0);
	if (print_status(philo, status))
	{
		philo->err_flag = 1;
		return (1);
	}
	if (status == Eat)
		ft_msleep(philo->eat_time);
	else if (status == Sleep)
		ft_msleep(philo->sleep_time);
	return (0);
}
