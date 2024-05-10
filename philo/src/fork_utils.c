/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 19:22:53 by pfontenl          #+#    #+#             */
/*   Updated: 2024/02/24 12:28:17 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_forks(t_data *data)
{
	size_t	i;

	data->forks = malloc(data->amount * sizeof(t_fork));
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->amount)
	{
		if (init_mutex(&data->forks[i], &data->err_flag))
		{
			while (i > 0)
				destroy_mutex(&data->forks[--i], &data->err_flag);
			return (1);
		}
		i++;
	}
	return (0);
}

int	grab_forks(t_philo *philo)
{
	if (!sim_running(philo))
		return (1);
	if (lock_mutex(philo->forks[0], &philo->err_flag))
		return (1);
	if (sim_running(philo))
	{
		if (print_status(philo, Fork))
		{
			unlock_mutex(philo->forks[0], NULL);
			philo->err_flag = 1;
			return (1);
		}
	}
	if (lock_mutex(philo->forks[1], &philo->err_flag))
		return (unlock_mutex(philo->forks[0], &philo->err_flag), 1);
	if (sim_running(philo))
	{
		if (print_status(philo, Fork))
		{
			release_forks(philo);
			philo->err_flag = 1;
			return (1);
		}
	}
	return (0);
}

int	release_forks(t_philo *philo)
{
	int	err;

	err = 0;
	unlock_mutex(philo->forks[0], &err);
	unlock_mutex(philo->forks[1], &err);
	if (err)
		philo->err_flag = 1;
	return (err);
}

void	destroy_forks(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->amount)
		destroy_mutex(&data->forks[i++], &data->err_flag);
}
