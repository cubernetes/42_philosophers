/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_dead_philosophers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 02:41:02 by tischmid          #+#    #+#             */
/*   Updated: 2024/07/20 00:14:21 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define PHILO_ERROR -1
#define NOT_DONE -1

/* Determine if a philosopher is done with eating or starved/dead
 * by testing the following 2 conditions:
 * 1. Was the START time of the last meal longer (>=) ago than time to die?
 * 2. Has the philosopher eaten min_eat meals or more?
 * If either condition is true, we are done and it must be indirectly signaled
 * to all other threads so they don't print any diagnostic logs anymore.
 */
static
int	_philo_done(t_philo *philo)
{
	int	done;
	int	now;

	done = FALSE;
	if (pthread_mutex_lock(&philo->last_meal_mtx) != 0)
		return (PHILO_ERROR);
	now = (int)get_mtime();
	if (now == ERR_GETTIMEOFDAY)
	{
		(void)pthread_mutex_unlock(&philo->last_meal_mtx);
		return (PHILO_ERROR);
	}
	done |= now - (int)philo->last_meal >= philo->params->time_to_die;
	if (pthread_mutex_unlock(&philo->last_meal_mtx) != 0)
		return (PHILO_ERROR);
	return (done);
}
/* TODO: Implement min_eat feature */

/* Safely check if the simulation has ended, by reading the global stop flag
 * that indicates that, protected by a mutex. If the mutex (un)locking fails,
 * forcefully change the global stop flag to 0 and return -1, indicating that
 * the simulation has ended and forcing it to be reported as a system error
 * to the main thread. Thereforce, a caller of this function must check for
 * `!= 0' instead of `== 1' to check for errors.
 */
extern
int	sim_has_ended(t_params *params)
{
	int	simulation_has_ended;

	if (pthread_mutex_lock(&params->stop_mtx) != 0)
	{
		params->stop = FALSE;
		return (-1);
	}
	simulation_has_ended = params->stop;
	if (pthread_mutex_unlock(&params->stop_mtx) != 0)
	{
		params->stop = FALSE;
		return (-1);
	}
	else
		return (simulation_has_ended);
}

static
int	signal_end_of_sim(t_params *params)
{
	if (pthread_mutex_lock(&params->stop_mtx) != 0)
		return (EXIT_FAILURE);
	params->stop = TRUE;
	if (pthread_mutex_unlock(&params->stop_mtx) != 0)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

static
int	_check_all_philosophers(
	t_params *params,
	t_philo **philos
)
{
	int	idx;
	int	done;

	idx = 0;
	while (idx < params->num_philos)
	{
		done = _philo_done(philos[idx]);
		if (done == PHILO_ERROR)
			return (EXIT_FAILURE);
		if (done)
		{
			if (signal_end_of_sim(params) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			else
				return (EXIT_SUCCESS);
		}
		++idx;
	}
	return (NOT_DONE);
}

/* Run forever until a philosopher is deemed done by the logic implemented
 * in _philo_done, or until an error occures.
 */
extern
int	_detect_dead_philosophers(
	t_philo **philos,
	t_params *params
)
{
	int	ret;

	if (philos == NULL || params == NULL)
		return (EXIT_FAILURE);
	while (TRUE)
	{
		ret = _check_all_philosophers(params, philos);
		if (ret != NOT_DONE)
			return (ret);
		if (ft_msleep(10) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
