/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:56:12 by pfontenl          #+#    #+#             */
/*   Updated: 2024/04/27 17:18:51 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static unsigned int	arg_count_check(int arg_count);
static unsigned int	parse_num(char *str, int *err);
static void			write_err(char *s);

int	parse_sim_data(int argn, char **args, t_data *data)
{
	int	err_flag;

	if (arg_count_check(argn))
		return (1);
	err_flag = 0;
	data->amount = parse_num(args[1], &err_flag);
	if (err_flag || data->amount == 0 || data->amount > 200)
		return (write_err(ERR_MSG_PHILO), 1);
	data->starve_time = parse_num(args[2], &err_flag);
	if (err_flag || data->starve_time < 60)
		return (write_err(ERR_MSG_STARVE), 1);
	data->eat_time = parse_num(args[3], &err_flag);
	if (err_flag || data->eat_time < 60)
		return (write_err(ERR_MSG_EAT), 1);
	data->sleep_time = parse_num(args[4], &err_flag);
	if (err_flag || data->sleep_time < 60)
		return (write_err(ERR_MSG_SLEEP), 1);
	data->meal_goal = 0;
	if (argn == 6)
	{
		data->meal_goal = parse_num(args[5], &err_flag);
		if (err_flag || !data->meal_goal)
			return (write_err(ERR_MSG_MEAL), 1);
	}
	return (0);
}

static unsigned int	arg_count_check(int arg_count)
{
	if (arg_count != 5 && arg_count != 6)
	{
		write_err("Usage: ./philo <n> <starve> <eat> <sleep> (<meal_goal>)");
		return (1);
	}
	return (0);
}

static unsigned int	parse_num(char *str, int *err)
{
	unsigned int	n;
	unsigned int	prev;

	n = 0;
	prev = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (*err = 1, 0);
		prev = n;
		n = n * 10 + *str - '0';
		if (prev > n)
			return (*err = 1, 0);
		str++;
	}
	return (n);
}

static void	write_err(char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	write(STDERR_FILENO, COLOR_RED, 7);
	write(STDERR_FILENO, s, len);
	write(STDERR_FILENO, COLOR_NONE, 7);
	write(STDERR_FILENO, "\n", 1);
}
