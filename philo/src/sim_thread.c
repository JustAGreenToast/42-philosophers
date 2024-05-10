/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_thread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 19:12:44 by pfontenl          #+#    #+#             */
/*   Updated: 2024/02/24 18:15:21 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*stop_sim(t_data *data);

void	*thread_main(void *raw_data)
{
	t_data	*data;
	size_t	i;

	data = (t_data *)raw_data;
	data->start_ms = calc_time(0);
	i = 0;
	while (i < data->amount)
	{
		data->philo[i].start_ms = data->start_ms;
		if (pthread_create(&data->philo[i].thread, NULL, &philo_main,
				&data->philo[i]))
			return ((void *)1);
		i++;
	}
	while (run_sim(data))
		usleep(SIM_SLEEP);
	return (stop_sim(data));
}

static void	*stop_sim(t_data *data)
{
	size_t	i;
	void	*out;

	i = 0;
	while (i < data->amount)
	{
		if (lock_mutex(&data->philo[i].philo_lock, &data->err_flag))
			return ((void *)1);
		data->philo[i].run_thread = 0;
		if (unlock_mutex(&data->philo[i].philo_lock, &data->err_flag))
			return ((void *)1);
		i++;
	}
	i = 0;
	while (i < data->amount)
	{
		if (pthread_join(data->philo[i].thread, &out) || out)
			data->err_flag = 1;
		destroy_mutex(&data->philo[i++].philo_lock, &data->err_flag);
	}
	return ((void *)0);
}
