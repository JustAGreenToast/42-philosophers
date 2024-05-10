/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:39:49 by pfontenl          #+#    #+#             */
/*   Updated: 2024/04/30 12:49:57 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_simulation(t_data *data)
{
	data->start_ms = calc_time(0);
	if (create_forks(data))
		return (data->philo = NULL, 1);
	data->philo = malloc(data->amount * sizeof(t_philo));
	if (!data->philo)
		return (destroy_forks(data), 1);
	if (init_philos(data))
		return (destroy_forks(data), 1);
	if (init_mutex(&data->print_lock, NULL))
		return (destroy_forks(data), 1);
	data->death_flag = 0;
	if (init_mutex(&data->death_lock, NULL))
		return (destroy_forks(data), destroy_mutex(&data->print_lock, NULL), 1);
	data->err_flag = 0;
	return (0);
}
