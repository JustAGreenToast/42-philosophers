/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:50:01 by pfontenl          #+#    #+#             */
/*   Updated: 2024/02/26 12:28:36 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philo(t_data *data, size_t i);
static int	destroy_philo(t_data *data, size_t i);

int	init_philos(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->amount)
	{
		if (init_philo(data, i))
		{
			while (i > 0)
				destroy_philo(data, --i);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_philo(t_data *data, size_t i)
{
	data->philo[i].run_thread = 1;
	data->philo[i].thread_stopped = 0;
	data->philo[i].n = i;
	if (data->amount % 2 && i == data->amount - 1)
		data->philo[i].start_delay = 2;
	else
		data->philo[i].start_delay = i % 2;
	data->philo[i].extra_delay = data->amount % 2;
	data->philo[i].last_meal = 0;
	data->philo[i].eaten_meals = 0;
	data->philo[i].forks[0] = &data->forks[i];
	data->philo[i].forks[1] = &data->forks[(i + 1) % data->amount];
	data->philo[i].eat_time = data->eat_time;
	data->philo[i].sleep_time = data->sleep_time;
	if (init_mutex(&data->philo[i].philo_lock, NULL))
		return (1);
	data->philo[i].print_lock = &data->print_lock;
	data->philo[i].death_flag = &data->death_flag;
	data->philo[i].death_lock = &data->death_lock;
	data->philo[i].err_flag = 0;
	return (0);
}

int	destroy_philo(t_data *data, size_t i)
{
	return (destroy_mutex(&data->philo[i].philo_lock, NULL));
}
