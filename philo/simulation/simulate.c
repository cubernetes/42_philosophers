/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:32:26 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/19 23:58:19 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

#include <stdlib.h>
#include <pthread.h>

/* Join the philosophers threads (so their memory can be cleaned up properly).
 *
 * Every thread either returns NULL (indicating error) or the void-ptr which
 * has been passed to them (indicating success). If they return NULL
 * and the simulation has been stopped due to a dead philosopher or due to
 * all philosophers having eating their min_eat meals, then this is considered
 * a success instead ("success" as in there was no runtime error, the program
 * behaved as expected, no failed mallocs, etc.).
 */
static int	_wait_for_philos(pthread_t *philo_threads, t_params *params)
{
	int		idx;
	int		err;
	void	*ret;

	if (philo_threads == NULL || params == NULL)
	{
		return (EXIT_FAILURE);
	}
	idx = 0;
	err = FALSE;
	while (idx < params->num_philos)
	{
		err |= pthread_join(philo_threads[idx], &ret) != 0;
		err |= ret != NULL && params->stop == FALSE;
		++idx;
	}
	if (err)
	{
		return (EXIT_FAILURE);
	}
	else
	{
		return (EXIT_SUCCESS);
	}
}

/* Unlock the synchronization mutex, which should start all the philosopher
 * threads simultaneously.
 */
static int	_unlock_philosophers(t_params *params)
{
	int			exit_status;

	exit_status = EXIT_SUCCESS;
	params->start_time = get_mtime();
	if (params->start_time == 0)
	{
		params->stop = TRUE;
		exit_status = EXIT_FAILURE;
	}
	if (pthread_mutex_unlock(&params->sync_mtx) != 0)
	{
		exit_status = EXIT_FAILURE;
	}
	return (exit_status);
}

/* - Unlock mutexes (to start philosopher threads synchronized)
 * - Check indefinitely for dead or finished philosophers
 * - Await (join) threads to get their return values
 * - Clean up allocated memory
 * - Set exit statuses accordingly
 */
static int	_simulation_epilogue(t_philo **philos, t_params *params,
	pthread_t *philo_threads)
{
	int			exit_status;

	exit_status = EXIT_SUCCESS;
	if (_unlock_philosophers(params) == EXIT_FAILURE)
	{
		exit_status = EXIT_FAILURE;
	}
	if (_detect_dead_philosophers(philos, params) == EXIT_FAILURE)
	{
		exit_status = EXIT_FAILURE;
	}
	if (_wait_for_philos(philo_threads, params) == EXIT_FAILURE)
	{
		exit_status = EXIT_FAILURE;
	}
	if (_cleanup_simulation(philos, params, philo_threads) == EXIT_FAILURE)
	{
		exit_status = EXIT_FAILURE;
	}
	return (exit_status);
}

/* Allocate the thread array for the threads can be awaited.
 * Also lock the synchronization mutex, so the threads can all be
 * started at the same time later.
 */
static int	_prepare_simulation(t_params *params, pthread_t **threads)
{
	if (params == NULL)
		return (EXIT_FAILURE);
	*threads = malloc(sizeof(**threads) * (size_t)params->num_philos);
	if (*threads == NULL)
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(&params->sync_mtx))
	{
		safe_free(*threads);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/* Birds-eye simulation logic:
 * - Lock the synchronization mutex
 * - Spawn philosopher threads (which wait for the sync-mtx to be unlocked)
 * - Unlock the synchronization mutex
 * - Wait for philosopher threads to finish
 * - Cleanup everything (also in case of error in between)
 */
int	simulate(t_params *params)
{
	pthread_t	*philo_threads;
	t_philo		**philos;

	if (_prepare_simulation(params, &philo_threads))
		return (EXIT_FAILURE);
	philos = _spawn_philos(philo_threads, params);
	if (philos == NULL)
	{
		(void)pthread_mutex_unlock(&params->sync_mtx);
		(void)_cleanup_simulation(philos, params, philo_threads);
		return (EXIT_FAILURE);
	}
	if (_simulation_epilogue(philos, params, philo_threads))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
