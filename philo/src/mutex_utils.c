/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:00:09 by pfontenl          #+#    #+#             */
/*   Updated: 2024/04/30 12:48:57 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_error(int err)
{
	if (err == EINVAL)
		write(STDERR_FILENO, "Mutex error: EINVAL\n", 21);
	else if (err == EPERM)
		write(STDERR_FILENO, "Mutex error: EPERM\n", 20);
	else if (err == EDEADLK)
		write(STDERR_FILENO, "Mutex error: EDEADLK\n", 22);
	else if (err == EBUSY)
		write(STDERR_FILENO, "Mutex error: EBUSY\n", 20);
	else
		write(STDERR_FILENO, "Mutex error: ???\n", 18);
}

int	init_mutex(t_mutex *mutex, int *err)
{
	int	out;

	out = pthread_mutex_init(mutex, NULL);
	if (out)
	{
		if (err)
			*err = 1;
		print_error(out);
	}
	return (out);
}

int	lock_mutex(t_mutex *mutex, int *err)
{
	int	out;

	out = pthread_mutex_lock(mutex);
	if (out)
	{
		if (err)
			*err = 1;
		print_error(out);
	}
	return (out);
}

int	unlock_mutex(t_mutex *mutex, int *err)
{
	int	out;

	out = pthread_mutex_unlock(mutex);
	if (out)
	{
		if (err)
			*err = 1;
		print_error(out);
	}
	return (out);
}

int	destroy_mutex(t_mutex *mutex, int *err)
{
	int	out;

	out = pthread_mutex_destroy(mutex);
	if (out)
	{
		if (err)
			*err = 1;
		print_error(out);
	}
	return (out);
}
