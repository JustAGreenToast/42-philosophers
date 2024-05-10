/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:38:03 by pfontenl          #+#    #+#             */
/*   Updated: 2024/02/26 12:34:08 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_millis	calc_time(t_millis offset)
{
	struct timeval	current_time;
	t_millis		sec;
	t_millis		micro;

	gettimeofday(&current_time, NULL);
	sec = current_time.tv_sec;
	micro = current_time.tv_usec;
	return ((sec * 1000 + micro / 1000) - offset);
}

void	ft_msleep(t_millis time)
{
	t_millis	start;

	start = calc_time(0);
	while (calc_time(start) < time)
		usleep(MSLEEP_TIME);
}
