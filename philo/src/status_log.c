/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_log.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:38:36 by pfontenl          #+#    #+#             */
/*   Updated: 2024/04/30 12:28:31 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	death_check(t_philo *philo, int set_flag);
static int	set_color(enum e_status *status);
static int	print_time(t_millis log_ms);
static int	print_action(size_t n, enum e_status status);

int	print_status(t_philo *philo, enum e_status status)
{
	int			death_flag;
	t_millis	log_ms;

	if (lock_mutex(philo->print_lock, NULL))
		return (1);
	death_flag = death_check(philo, status == Death);
	if (death_flag)
	{
		if (unlock_mutex(philo->print_lock, NULL))
			return (1);
		return (death_flag < 0);
	}
	log_ms = calc_time(philo->start_ms);
	if (set_color(&status) || print_time(log_ms) || print_action(philo->n + 1,
			status) || set_color(NULL))
		return (unlock_mutex(philo->print_lock, NULL), 1);
	return (unlock_mutex(philo->print_lock, NULL));
}

static int	set_color(enum e_status *status)
{
	int	out;

	out = 0;
	if (status)
	{
		if (*status == Eat)
			out = printf("%s", COLOR_YELLOW);
		if (*status == Sleep)
			out = printf("%s", COLOR_PINK);
		if (*status == Think)
			out = printf("%s", COLOR_CYAN);
		if (*status == Death)
			out = printf("%s", COLOR_RED);
		if (*status == Fork)
			out = printf("%s", COLOR_GREEN);
	}
	else
		out = printf("%s\n", COLOR_NONE);
	return (out == -1);
}

static int	print_time(t_millis log_ms)
{
	if (printf("🕒 [%llu]\t", log_ms) == -1)
		return (1);
	if (log_ms < 100)
		if (printf("\t") == -1)
			return (1);
	return (0);
}

static int	print_action(size_t n, enum e_status status)
{
	if (status == Eat)
		return (printf("%zu is eating\t\t[🍝]", n) == -1);
	if (status == Sleep)
		return (printf("%zu is sleeping\t\t[😴]", n) == -1);
	if (status == Think)
		return (printf("%zu is thinking\t\t[💭]", n) == -1);
	if (status == Death)
	{
		if (printf("%zu died\t\t", n) == -1)
			return (1);
		if (n < 100 && printf("\t") == -1)
			return (1);
		return (printf("[💀]") == -1);
	}
	return (printf("%zu has taken a fork\t[🍴]", n) == -1);
}

static int	death_check(t_philo *philo, int set_flag)
{
	int	death_flag;

	if (lock_mutex(philo->death_lock, &philo->err_flag))
		return (-1);
	death_flag = *philo->death_flag;
	if (set_flag)
		*philo->death_flag = 1;
	if (unlock_mutex(philo->death_lock, &philo->err_flag))
		return (-1);
	return (death_flag);
}
