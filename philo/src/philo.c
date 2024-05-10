/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:52:51 by pfontenl          #+#    #+#             */
/*   Updated: 2024/02/24 18:50:17 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argn, char **args)
{
	t_data	data;

	if (parse_sim_data(argn, args, &data))
		return (1);
	if (init_simulation(&data))
	{
		free(data.forks);
		free(data.philo);
		return (1);
	}
	if (pthread_create(&data.sim_thread, NULL, &thread_main, &data))
		return (1);
	if (pthread_join(data.sim_thread, NULL))
		data.err_flag = 1;
	destroy_mutex(&data.print_lock, &data.err_flag);
	destroy_mutex(&data.death_lock, &data.err_flag);
	free(data.philo);
	destroy_forks(&data);
	free(data.forks);
	return (data.err_flag);
}
