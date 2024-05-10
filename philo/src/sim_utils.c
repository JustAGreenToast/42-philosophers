/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:38:53 by pfontenl          #+#    #+#             */
/*   Updated: 2024/04/30 12:10:09 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int		meal_goal_check(t_data *data);
static int		starve_check(t_data *data);
static int		philo_check(t_data *data);

int	run_sim(t_data *data)
{
	if (starve_check(data) || data->err_flag)
		return (0);
	if (meal_goal_check(data) || data->err_flag)
		return (0);
	if (philo_check(data) || data->err_flag)
		return (0);
	return (1);
}

static int	starve_check(t_data *data)
{
	size_t		i;
	t_millis	current_time;
	ssize_t		starved_index;

	i = 0;
	current_time = calc_time(data->start_ms);
	starved_index = -1;
	while (i < data->amount && starved_index == -1)
	{
		if (lock_mutex(&data->philo[i].philo_lock, &data->err_flag))
			return (1);
		if (current_time > data->philo[i].last_meal && (current_time
				- data->philo[i].last_meal) > data->starve_time)
		{
			data->philo[i].run_thread = 0;
			starved_index = i;
			if (print_status(&data->philo[starved_index], Death))
				data->err_flag = 1;
		}
		if (unlock_mutex(&data->philo[i].philo_lock, &data->err_flag))
			return (1);
		i++;
	}
	return (starved_index != -1);
}

static int	meal_goal_check(t_data *data)
{
	size_t	i;
	size_t	eaten_meals;

	if (!data->meal_goal)
		return (0);
	i = 0;
	while (i < data->amount)
	{
		if (lock_mutex(&data->philo[i].philo_lock, &data->err_flag))
			return (1);
		eaten_meals = data->philo[i].eaten_meals;
		if (unlock_mutex(&data->philo[i].philo_lock, &data->err_flag))
			return (1);
		if (eaten_meals < data->meal_goal)
			return (0);
		i++;
	}
	return (1);
}

static int	philo_check(t_data *data)
{
	size_t	i;
	int		out;

	i = 0;
	while (i < data->amount)
	{
		if (lock_mutex(&data->philo[i].philo_lock, &data->err_flag))
			return (1);
		out = data->philo[i].thread_stopped;
		if (unlock_mutex(&data->philo[i].philo_lock, &data->err_flag))
			return (1);
		if (out)
			return (1);
		i++;
	}
	return (0);
}
